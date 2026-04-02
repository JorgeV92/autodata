#ifndef AUTODATA_CORE_FIXED_BATCH_DATASET_H
#define AUTODATA_CORE_FIXED_BATCH_DATASET_H

#include "autodata/core/batch_dataset.h"
#include "autodata/core/map_dataset.h"

#include <cstddef>

namespace autodata {

class FixedBatchDataset : public BatchDatasetI64 {
public:
    FixedBatchDataset(MapDatasetI64Ptr parent, std::size_t batch_size, bool drop_remainder = false);

    std::size_t size() const override;
    std::vector<std::int64_t> get(std::size_t index) const override;

    std::size_t batch_size() const;
    bool drop_remainder() const;

private:
    MapDatasetI64Ptr parent_;
    std::size_t batch_size_;
    bool drop_remainder_;
    std::size_t num_batches_;
};

}  // namespace autodata

#endif
