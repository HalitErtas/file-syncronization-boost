#ifndef COMPARISONENTRY_H_
#define COMPARISONENTRY_H_

#include "ComparisonStatus.hpp"
#include "FileInfo.hpp"

namespace file_sync_app::common {
    
struct ComparisonEntry 
{
    FileInfo info;
    ComparisonStatus status;
};

} // namespace file_sync_app::common

#endif  