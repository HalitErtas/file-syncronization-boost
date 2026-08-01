#ifndef FILESCANNER_H_
#define FILESCANNER_H_

#include <vector>
#include "FileInfo.hpp"
#include "FileType.hpp"

namespace file_sync_app::core {

class FileScanner{
    private:
        bool shouldAdd(const common::FileInfo& info, common::FileType type);
    public:
        std::vector<common::FileInfo> scan(const std::filesystem::path& path, common::FileType type);
};

} // namespace file_sync_app

#endif  