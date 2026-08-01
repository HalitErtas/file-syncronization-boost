#ifndef SYNCENGINE_H_
#define SYNCENGINE_H_


#include "ComparisonEntry.hpp"
#include "DirectoryComparer.hpp"
#include "FileScanner.hpp"
#include "FileSynchronizer.hpp"
#include <filesystem>
#include <functional>

namespace file_sync_app::core {

class SyncEngine{
    private:
        core::FileScanner fileScanner;
        core::DirectoryComparer directoryComparer;
        core::FileSynchronizer fileSynchronizer;
    public:
        void sync(
            const std::filesystem::path& sourceRoot, 
            const std::filesystem::path& targetRoot, 
            const std::vector<common::ComparisonEntry>& entries);
        std::vector<common::ComparisonEntry> compare(
            const std::filesystem::path& sourceRoot, 
            const std::filesystem::path& targetRoot,
            std::function<void(int)> progress);
    private:
        void processAddedDirectories(const std::filesystem::path& targetRoot, std::vector<common::ComparisonEntry>& dirEntries);
        void processAddedFiles(const std::filesystem::path& sourceRoot, const std::filesystem::path& targetRoot, std::vector<common::ComparisonEntry>& fileEntries);
        void processModifiedFiles(const std::filesystem::path& sourceRoot, const std::filesystem::path& targetRoot, std::vector<common::ComparisonEntry>& fileEntries);
        void processRemovedFiles(const std::filesystem::path& targetRoot, std::vector<common::ComparisonEntry>& fileEntries);
        void processRemovedDirectories(const std::filesystem::path& targetRoot, std::vector<common::ComparisonEntry>& dirEntries);

};

} // namespace file_sync_app

#endif  