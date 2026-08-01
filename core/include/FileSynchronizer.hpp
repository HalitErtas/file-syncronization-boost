#ifndef FILESYNCHRONIZER_H_
#define FILESYNCHRONIZER_H_

#include <filesystem>
namespace file_sync_app::core {

class FileSynchronizer{
    public:
        bool copyFile(const std::filesystem::path& from, const std::filesystem::path& to);
        void copyDirectory(const std::filesystem::path& from, const std::filesystem::path& to, std::filesystem::copy_options options = std::filesystem::copy_options::recursive);
        void deleteFile(const std::filesystem::path& path);
        void deleteDirectory(const std::filesystem::path& path);
        void overwriteFile(const std::filesystem::path& from, const std::filesystem::path& to);
        void createDirectory(const std::filesystem::path& path);
    private:
        bool exists(const std::filesystem::path& path);
        bool isDirectory(const std::filesystem::path& path);
        bool isEmpty(const std::filesystem::path& path);
};

} // namespace file_sync_app::core

#endif  