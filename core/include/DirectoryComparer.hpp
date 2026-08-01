#ifndef DIRECTORYCOMPARER_H_
#define DIRECTORYCOMPARER_H_


#include "FileInfo.hpp"
#include "ComparisonEntry.hpp"

#include <functional>
#include <filesystem>

namespace file_sync_app::core {

class DirectoryComparer{
    public:
        std::vector<common::ComparisonEntry> compare(
            const std::vector<common::FileInfo>& source, 
            const std::vector<common::FileInfo>& target,
            std::function<void(int)> progress);
        std::string computeSHA256(const std::filesystem::path& filePath);
};

} // namespace file_sync_app

#endif  