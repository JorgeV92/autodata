#ifndef AUTODATA_CORE_SLICE_DATASET_H
#define AUTODATA_CORE_SLICE_DATASET_H

#include "autodata/core/map_dataset.h"

#include <cstddef>
#include <cstdint>
#include <vector>

namespace autodata {

class SliceDataset : public MapDatasetI64 {
public:
    SliceDataset(MapDatasetI64Ptr parent, std::size_t start, std::size_t stop, std::size_t step);

    std::size_t size() const override;
    std::int64_t get(std::size_t index) const override;

private:
    MapDatasetI64Ptr parent_;
    std::vector<std::size_t> indices_;
};

}  // namespace autodata

#endif
