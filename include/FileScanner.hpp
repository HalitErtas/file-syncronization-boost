#ifndef FILESCANNER_H_
#define FILESCANNER_H_

#include <vector>
#include "structs/FileInfo.hpp"
#include "structs/FileType.hpp"

namespace file_sync_app {

class FileScanner{
    private:
        bool shouldAdd(const structs::FileInfo& info, structs::FileType type);
    public:
        std::vector<structs::FileInfo> scan(const std::filesystem::path& path, structs::FileType type);
};

} // namespace file_sync_app

#endif  