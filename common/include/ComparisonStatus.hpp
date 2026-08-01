#ifndef COMPARISONSTATUS_H_
#define COMPARISONSTATUS_H_


namespace file_sync_app::common {

    enum class ComparisonStatus
    {
        Added,
        Removed,
        Modified,
        Unchanged
    };

} // namespace file_sync_app::common

#endif  