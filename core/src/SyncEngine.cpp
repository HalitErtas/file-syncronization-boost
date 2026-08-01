#include "SyncEngine.hpp"
#include "ComparisonEntry.hpp"
#include "ComparisonStatus.hpp"
#include "FileInfo.hpp"
#include "FileSynchronizer.hpp"
#include "FileType.hpp"

#include <algorithm>
#include <cassert>
#include <filesystem>
#include <iterator>
#include <vector>

namespace file_sync_app::core {
    void core::SyncEngine::sync(
    const std::filesystem::path& sourceRoot, 
    const std::filesystem::path& targetRoot, 
    const std::vector<common::ComparisonEntry>& entries){
        
        auto is_dir = [](const common::ComparisonEntry& entry) { return entry.info.isDirectory;};
        auto is_file = [](const common::ComparisonEntry& entry) { return !entry.info.isDirectory;};


        std::vector<common::ComparisonEntry> directories;
        directories.reserve(entries.size());
        std::copy_if(entries.begin(), entries.end(), std::back_inserter(directories), is_dir);

        std::vector<common::ComparisonEntry> files;
        files.reserve(entries.size());
        std::copy_if(entries.begin(), entries.end(), std::back_inserter(files), is_file);

        processRemovedFiles(targetRoot, files);
        processRemovedDirectories(targetRoot, directories);

        processAddedDirectories(targetRoot, directories);
        processAddedFiles(sourceRoot, targetRoot, files);

        processModifiedFiles(sourceRoot, targetRoot, files);
    }

    std::vector<common::ComparisonEntry> core::SyncEngine::compare(
            const std::filesystem::path& sourceRoot, 
            const std::filesystem::path& targetRoot,
            std::function<void(int)> progress){
        auto sourceFiles = fileScanner.scan(sourceRoot, common::FileType::ALL);
        auto targetFiles = fileScanner.scan(targetRoot, common::FileType::ALL);

        const auto compareResult = directoryComparer.compare(sourceFiles, targetFiles, progress);
        return compareResult;
    }


    void core::SyncEngine::processAddedDirectories(const std::filesystem::path& targetRoot, std::vector<common::ComparisonEntry>& dirEntries){
        for(const auto& dirEntry : dirEntries){
            if(dirEntry.status == common::ComparisonStatus::Added){
                fileSynchronizer.createDirectory(targetRoot / dirEntry.info.path);
            }
        }
    }

    void core::SyncEngine::processAddedFiles(const std::filesystem::path& sourceRoot, const std::filesystem::path& targetRoot, std::vector<common::ComparisonEntry>& fileEntries){
        for(const auto& fileEntry : fileEntries){
            if(fileEntry.status == common::ComparisonStatus::Added){
                fileSynchronizer.copyFile(sourceRoot / fileEntry.info.path, targetRoot / fileEntry.info.path);
            }
        }
    }

    void core::SyncEngine::processModifiedFiles(const std::filesystem::path& sourceRoot, const std::filesystem::path& targetRoot, std::vector<common::ComparisonEntry>& fileEntries){
        for(const auto& fileEntry : fileEntries){
            if(fileEntry.status == common::ComparisonStatus::Modified){
                fileSynchronizer.overwriteFile(sourceRoot / fileEntry.info.path, targetRoot / fileEntry.info.path);
            }
        }
    }

    void core::SyncEngine::processRemovedFiles(const std::filesystem::path& targetRoot, std::vector<common::ComparisonEntry>& fileEntries){
        for(const auto& fileEntry : fileEntries){
            if(fileEntry.status == common::ComparisonStatus::Removed){
                fileSynchronizer.deleteFile(targetRoot / fileEntry.info.path);
            }
        }
    }
    
    void core::SyncEngine::processRemovedDirectories(const std::filesystem::path& targetRoot , std::vector<common::ComparisonEntry>& dirEntries){
        for(const auto& dirEntry : dirEntries){
            if(dirEntry.status == common::ComparisonStatus::Removed){
                fileSynchronizer.deleteDirectory(targetRoot / dirEntry.info.path);
            }
        }
    }
}