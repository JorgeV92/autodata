#include "autodata/core/fixed_batch_dataset.h"

#include <stdexcept>

namespace autodata {

FixedBatchDataset::FixedBatchDataset(MapDatasetI64Ptr parent, std::size_t batch_size, bool drop_remainder)
    : parent_(std::move(parent)), batch_size_(batch_size), drop_remainder_(drop_remainder), num_batches_(0) {
    if (!parent_) {
        throw std::invalid_argument("FixedBatchDataset requires a non-null parent dataset");
    }
    if (batch_size_ == 0) {
        throw std::invalid_argument("batch_size must be greater than zero");
    }

    const std::size_t n = parent_->size();
    if (n == 0) {
        num_batches_ = 0;
    } else if (drop_remainder_) {
        num_batches_ = n / batch_size_;
    } else {
        num_batches_ = (n + batch_size_ - 1) / batch_size_;
    }
}

std::size_t FixedBatchDataset::size() const {
    return num_batches_;
}

std::vector<std::int64_t> FixedBatchDataset::get(std::size_t index) const {
    if (index >= num_batches_) {
        throw std::out_of_range("FixedBatchDataset index out of range");
    }

    const std::size_t start = index * batch_size_;
    const std::size_t stop = std::min(start + batch_size_, parent_->size());

    std::vector<std::int64_t> batch;
    batch.reserve(stop - start);
    for (std::size_t i = start; i < stop; ++i) {
        batch.push_back(parent_->get(i));
    }
    return batch;
}

std::size_t FixedBatchDataset::batch_size() const {
    return batch_size_;
}

bool FixedBatchDataset::drop_remainder() const {
    return drop_remainder_;
}

}  // namespace autodata