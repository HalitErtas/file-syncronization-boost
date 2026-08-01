#include "widgets/PathSelector.hpp"

namespace file_sync_app::gui {
    PathSelector::PathSelector(const QString& title, const QString& buttonText){
        this->setTitle(title);
        createWidgets(buttonText);
        createLayout();
        connectSignals();
        this->setLayout(h_layout);
    }    
    
    QString PathSelector::path() const{
        return pathEdit->text();
    }

    void PathSelector::openFileDialog(){
        qDebug() << "Browse button clicked!";
        QString dir = "/Users/halitertas/Projects/file-syncronization-boost/test-files";

        const auto existDirectory = QFileDialog::getExistingDirectory(this,
            tr("Select Directory"), dir);
        qDebug() << existDirectory;

        pathEdit->setText(existDirectory);
    }

    void PathSelector::createWidgets(const QString& buttonText){
        browseButton = new QPushButton(buttonText);
        pathEdit = new QLineEdit();
        pathEdit->setReadOnly(true);
    }

    void PathSelector::createLayout(){
        h_layout = new QHBoxLayout();
        h_layout->addWidget(pathEdit);
        h_layout->addWidget(browseButton);
    }

    void PathSelector::connectSignals(){
        connect(browseButton,
                &QPushButton::clicked,
                this,
                &PathSelector::openFileDialog);
    };

}