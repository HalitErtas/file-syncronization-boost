#include "DirectoryComparer.hpp"
#include "FileType.hpp"
#include <FileScanner.hpp>
#include <filesystem>
#include <vector>
#include <stdexcept>

namespace fs = std::filesystem;

namespace file_sync_app::core {
    std::vector<common::FileInfo> core::FileScanner::scan(const fs::path& path, common::FileType type){
        if(!fs::exists(path)){
            throw std::runtime_error("Directory not found.");
        }

        if(!fs::is_directory(path)){
            throw std::runtime_error("is not a directory");
        }

        file_sync_app::core::DirectoryComparer comparer;
        std::vector<common::FileInfo> files{};
        for(const auto& file : fs::recursive_directory_iterator(path)){
            common::FileInfo element;
            const bool isDirectory = file.is_directory();

            element.path = fs::relative(file.path(), path);
            element.name = file.path().filename();
            element.size = isDirectory ? 0 : file.file_size();;
            element.isDirectory = isDirectory;
            element.lastWriteTime = file.last_write_time();
            element.sha256 = comparer.computeSHA256(file.path()); 


            if (shouldAdd(element, type))
            {
                files.push_back(element);
            }
        }

        return files;
    }

    bool core::FileScanner::shouldAdd(const common::FileInfo& info, common::FileType type)
    {
        switch (type)
        {
            case common::FileType::FILE:
                return !info.isDirectory;

            case common::FileType::DIRECTORY:
                return info.isDirectory;

            case common::FileType::ALL:
                return true;
        }

        return false;
    }
}