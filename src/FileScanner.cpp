#include "structs/FileType.hpp"
#include <FileScanner.hpp>
#include <filesystem>
#include <vector>
#include <stdexcept>

namespace fs = std::filesystem;

namespace file_sync_app {
    std::vector<structs::FileInfo> FileScanner::scan(const fs::path& path, structs::FileType type){
        if(!fs::exists(path)){
            throw std::runtime_error("Directory not found.");
        }

        if(!fs::is_directory(path)){
            throw std::runtime_error("is not a directory");
        }

        std::vector<structs::FileInfo> files{};
        for(const auto& file : fs::directory_iterator(path)){
            structs::FileInfo element;
            const bool isDirectory = file.is_directory();

            element.path = file.path().filename();
            element.name = file.path().filename();
            element.size = isDirectory ? 0 : file.file_size();;
            element.isDirectory = isDirectory;
            element.lastWriteTime = file.last_write_time();


            if (shouldAdd(element, type))
            {
                files.push_back(element);
            }
        }

        return files;
    }

    bool FileScanner::shouldAdd(const structs::FileInfo& info, structs::FileType type)
    {
        switch (type)
        {
            case structs::FileType::FILE:
                return !info.isDirectory;

            case structs::FileType::DIRECTORY:
                return info.isDirectory;

            case structs::FileType::ALL:
                return true;
        }

        return false;
    }
}