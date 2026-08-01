#include "MainWindow.hpp"
#include "widgets/PathSelector.hpp"

namespace file_sync_app::gui {
    MainWindow::MainWindow() {
        createWidgets();
        createLayouts();
        connectSignals();
    }

    void MainWindow::createWidgets(){
        sourceSelector = new PathSelector("Source");
        targetSelector = new PathSelector("Target");


        compareButton = new QPushButton("Compare");
        syncButton = new QPushButton("Sync");
        syncButton->setEnabled(false);

        fileTable = new ComparisonTable();

        progressBar = new QProgressBar();
        progressBar->setRange(0,100);
        progressBar->setValue(0);
        progressBar->setMinimumHeight(25);
    }

    void MainWindow::createLayouts(){
        // main layout
        resize(800, 700);
        setWindowTitle("File Sync App");
        centralWidget = new QWidget(this);
        setCentralWidget(centralWidget);
        mainLayout = new QVBoxLayout(centralWidget);
        mainLayout->setAlignment(Qt::AlignTop);
        mainLayout->setSpacing(0);
        
        buttonLayout = new QHBoxLayout();
        buttonLayout->addWidget(compareButton, 0, Qt::AlignCenter);
        buttonLayout->addWidget(syncButton, 0, Qt::AlignCenter);

        mainLayout->addWidget(sourceSelector);
        mainLayout->addWidget(targetSelector);
        mainLayout->addLayout(buttonLayout);
        mainLayout->addWidget(fileTable);
        mainLayout->addWidget(progressBar);
    }

    void MainWindow::connectSignals(){
        connect(
            compareButton,
            &QPushButton::clicked,
            this,
            [this](){
                if (!sourceSelector->path().isEmpty() && !targetSelector->path().isEmpty()){
                    try
                    {
                        thread = new QThread(this);

                        compareWorker = new CompareWorker(
                            syncEngine,
                            sourceSelector->path(),
                            targetSelector->path()
                        );

                        compareWorker->moveToThread(thread);

                        connect(
                            thread,
                            &QThread::started,
                            compareWorker,
                            &CompareWorker::process
                        );
                        connect(
                            compareWorker,
                            &CompareWorker::progressChanged,
                            progressBar,
                            &QProgressBar::setValue
                        );
                        connect(
                            compareWorker,
                            &CompareWorker::finished,
                            this,
                            [this](const std::vector<common::ComparisonEntry>& result)
                            {
                                comparisonEntries = result;
                                qDebug() << comparisonEntries.size();

                                fileTable->setTableData(comparisonEntries);

                                syncButton->setEnabled(!comparisonEntries.empty());
                                compareButton->setEnabled(true);
                            }
                        );
                        connect(
                            compareWorker,
                            &CompareWorker::finished,
                            thread,
                            &QThread::quit
                        );

                        // Belleği temizle
                        connect(
                            thread,
                            &QThread::finished,
                            compareWorker,
                            &QObject::deleteLater
                        );

                        connect(
                            thread,
                            &QThread::finished,
                            thread,
                            &QObject::deleteLater
                        );

                        thread->start();
                    }
                    catch (const std::exception& e)
                    {
                        qDebug() << e.what();
                    }
                }
            }
        );

        connect(
            syncButton,
            &QPushButton::clicked,
            this,
            [this](){
                if(!comparisonEntries.empty() && comparisonEntries.size() > 0){
                    syncEngine.sync(this->sourceSelector->path().toStdString(), this->targetSelector->path().toStdString(), comparisonEntries);
                    comparisonEntries = comparePaths(sourceSelector->path(), targetSelector->path());
                    fileTable->setTableData(comparisonEntries);
                }
            }
        );
    }

    std::vector<common::ComparisonEntry> MainWindow::comparePaths(const QString &sourcePath, const QString &targetPath){
        return syncEngine.compare(
            sourcePath.toStdString(), 
            targetPath.toStdString(),
            [this](int value)
            {
                progressBar->setValue(value);
            }
        );
    }
}