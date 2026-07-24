#ifndef COMPARISONSTATUS_H_
#define COMPARISONSTATUS_H_

namespace file_sync_app::structs {

    enum class ComparisonStatus
    {
        Added,
        Removed,
        Unchanged
    };

} // namespace file_sync_app::structs

#endif  