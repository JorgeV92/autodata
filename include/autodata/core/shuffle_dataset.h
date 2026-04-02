#ifndef AUTODATA_CORE_SHUFFLE_DATASET_H
#define AUTODATA_CORE_SHUFFLE_DATASET_H

#include "autodata/core/map_dataset.h"

#include <cstddef>
#include <cstdint>
#include <vector>

namespace autodata {

class ShuffleDataset : public MapDatasetI64 {
public:
    ShuffleDataset(MapDatasetI64Ptr parent, std::uint64_t seed);

    std::size_t size() const override;
    std::int64_t get(std::size_t index) const override;

private:
    MapDatasetI64Ptr parent_;
    std::vector<std::size_t> permutation_;
};

}  // namespace autodata

#endif
