#ifndef AUTODATA_CORE_VECTOR_DATASET_H
#define AUTODATA_CORE_VECTOR_DATASET_H

#include "autodata/core/map_dataset.h"

#include <cstddef>
#include <cstdint>
#include <vector>

namespace autodata {

class VectorDataset : public MapDatasetI64 {
public:
    explicit VectorDataset(std::vector<std::int64_t> data);

    std::size_t size() const override;
    std::int64_t get(std::size_t index) const override;

private:
    std::vector<std::int64_t> data_;
};

}  // namespace autodata

#endif
