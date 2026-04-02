#ifndef AUTODATA_CORE_RANGE_DATASET_H
#define AUTODATA_CORE_RANGE_DATASET_H

#include "autodata/core/map_dataset.h"

#include <cstddef>
#include <cstdint>
#include <stdexcept>

namespace autodata {

class RangeDataset : public MapDatasetI64 {
public:
    RangeDataset(std::int64_t start, std::int64_t stop, std::int64_t step = 1);

    std::size_t size() const override;
    std::int64_t get(std::size_t index) const override;
private:
    std::int64_t start_;
    std::int64_t stop_;
    std::int64_t step_;
    std::int16_t size_;
};

} // namespace autodata

#endif