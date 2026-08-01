#include "FileSynchronizer.hpp"
#include <filesystem>

namespace file_sync_app::core {
    bool FileSynchronizer::copyFile(const std::filesystem::path& from, const std::filesystem::path& to){
        createDirectory(to.parent_path());    
        return std::filesystem::copy_file(from, to);
    }

    void FileSynchronizer::copyDirectory(const std::filesystem::path& from, 
        const std::filesystem::path& to, 
        std::filesystem::copy_options options){
        std::filesystem::copy(from, to, options);
    }

    void FileSynchronizer::deleteFile(const std::filesystem::path& path){
        if(exists(path)){
            std::filesystem::remove(path);    
        }
    }

    void FileSynchronizer::deleteDirectory(const std::filesystem::path& path){
        std::filesystem::remove_all(path);
        
    }
    
    // Precondition:
    // 'to' already exists because this method is only used
    // for ComparisonStatus::Modified.
    void FileSynchronizer::overwriteFile(const std::filesystem::path& from, const std::filesystem::path& to){
        std::filesystem::copy_file(from, to, std::filesystem::copy_options::overwrite_existing);
    }
    
    void FileSynchronizer::createDirectory(const std::filesystem::path& path){
        std::filesystem::create_directories(path);
    }
    
    bool FileSynchronizer::exists(const std::filesystem::path& path){
        return std::filesystem::exists(path);
    }

    bool FileSynchronizer::isDirectory(const std::filesystem::path& path){
        return std::filesystem::is_directory(path);
    }

    bool FileSynchronizer::isEmpty(const std::filesystem::path& path){
        if (!std::filesystem::exists(path))
            return true;

        return std::filesystem::is_empty(path);
    }
}