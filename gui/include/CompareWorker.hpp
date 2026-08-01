#ifndef COMPAREWORKER_H_
#define COMPAREWORKER_H_

#include "ComparisonEntry.hpp"
#include "SyncEngine.hpp"
#include <QObject>
#include <QString>

namespace file_sync_app::gui {
    
class CompareWorker : public QObject{
    Q_OBJECT

    private:
        core::SyncEngine& syncEngine;
        QString sourcePath;
        QString targetPath;

    public:
    CompareWorker(
        core::SyncEngine& syncEngine,
        const QString& sourcePath,
        const QString& targetPath
    );

    public slots:
        void process();

    signals:
        void progressChanged(int value);
        void finished(const std::vector<common::ComparisonEntry>& result);
    };
} // namespace file_sync_app::gui

#endif  