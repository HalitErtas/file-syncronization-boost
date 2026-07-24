#ifndef FILEINFO_H_
#define FILEINFO_H_

#include <cstdint>
#include <filesystem>

namespace file_sync_app::structs {

struct FileInfo
{
    std::filesystem::path path;
    std::string name;
    uintmax_t size;
    std::filesystem::file_time_type lastWriteTime;
    bool isDirectory;
};

} // namespace file_sync_app::structs

#endif  