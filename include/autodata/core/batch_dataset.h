#ifndef AUTODATA_CORE_BATCH_DATASET_H
#define AUTODATA_CORE_BATCH_DATASET_H

#include <cstddef>
#include <cstdint>
#include <memory>
#include <vector>

namespace autodata {

class BatchDatasetI64 {
public:
    virtual ~BatchDatasetI64() = default;
    virtual std::size_t size() const = 0;
    virtual std::vector<std::int64_t> get(std::size_t index) const = 0;
};

using BatchDatasetI64Ptr = std::shared_ptr<BatchDatasetI64>;

}  // namespace autodata

#endif
