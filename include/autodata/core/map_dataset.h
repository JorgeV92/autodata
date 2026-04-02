#ifndef AUTODATA_CORE_MAP_DATASET_H
#define AUTODATA_CORE_MAP_DATASET_H

#include <cstddef>
#include <cstdint>
#include <memory>

namespace autodata {

class MapDatasetI64 {
public:
    virtual ~MapDatasetI64() = default;
    virtual std::size_t size() const = 0;
    virtual std::int64_t get(std::size_t index) const = 0;
};

using MapDatasetI64Ptr = std::shared_ptr<MapDatasetI64>;

}  // namespace autodata

#endif
