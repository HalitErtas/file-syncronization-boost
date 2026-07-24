#ifndef DIRECTORYCOMPARER_H_
#define DIRECTORYCOMPARER_H_

#include <vector>
#include "structs/ComparisonEntry.hpp"
#include "structs/FileInfo.hpp"
#include "structs/FileType.hpp"

namespace file_sync_app {

class DirectoryComparer{
    public:
        std::vector<structs::ComparisonEntry> compare(const std::vector<structs::FileInfo>& source, const std::vector<structs::FileInfo>& target);
};

} // namespace file_sync_app

#endif  