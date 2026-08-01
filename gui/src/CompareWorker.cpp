#include "CompareWorker.hpp"

namespace file_sync_app::gui {
    CompareWorker::CompareWorker(
        core::SyncEngine& syncEngine,
        const QString& sourcePath,
        const QString& targetPath
    ) : syncEngine(syncEngine), sourcePath(sourcePath), targetPath(targetPath){}

    void CompareWorker::process(){
        auto compareResult = syncEngine.compare(sourcePath.toStdString(), targetPath.toStdString(),
        [this](int value){
            emit progressChanged(value);
        });
        emit finished(compareResult);
    }
}