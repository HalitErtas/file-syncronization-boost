#ifndef COMPARISONENTRY_H_
#define COMPARISONENTRY_H_

#include "structs/ComparisonStatus.hpp"
#include "structs/FileInfo.hpp"

namespace file_sync_app::structs {
    
struct ComparisonEntry 
{
    FileInfo info;
    ComparisonStatus status;
};

} // namespace file_sync_app::structs

#endif  