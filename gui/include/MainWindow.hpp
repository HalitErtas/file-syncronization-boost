#ifndef MAINWINDOW_H_
#define MAINWINDOW_H_

#include "CompareWorker.hpp"
#include "widgets/PathSelector.hpp"
#include "widgets/ComparisonTable.hpp"
#include "SyncEngine.hpp"
#include "ComparisonEntry.hpp"

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QProgressBar>
#include <QThread>

namespace file_sync_app::gui {
    
class MainWindow : public QMainWindow{
    private:
        std::vector<common::ComparisonEntry> comparisonEntries;
        QWidget* centralWidget;
        QVBoxLayout* mainLayout;
        QHBoxLayout* compareLayout;

        PathSelector* sourceSelector;
        PathSelector* targetSelector;
        
        QHBoxLayout* buttonLayout;
        QPushButton* compareButton;
        QPushButton* syncButton;

        ComparisonTable* fileTable;

        QProgressBar* progressBar;

        core::SyncEngine syncEngine;
        QThread* thread;
        CompareWorker* compareWorker;
        CompareWorker* syncWorker;
    public:
        MainWindow();

    private:
        void createWidgets();
        void createLayouts();
        void connectSignals();

        std::vector<common::ComparisonEntry> comparePaths(const QString &sourcePath, const QString &targetPath);
    };
} // namespace file_sync_app::gui

#endif  