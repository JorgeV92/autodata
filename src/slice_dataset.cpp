#include "autodata/core/slice_dataset.h"

#include <stdexcept>

namespace autodata {

SliceDataset::SliceDataset(MapDatasetI64Ptr parent, std::size_t start, std::size_t stop, std::size_t step)
    : parent_(std::move(parent)) {
    if (!parent_) {
        throw std::invalid_argument("SliceDataset requires a non-null parent dataset");
    }
    if (step == 0) {
        throw std::invalid_argument("SliceDataset step must not be zero");
    }

    const std::size_t n = parent_->size();
    const std::size_t clamped_start = start > n ? n : start;
    const std::size_t clamped_stop = stop > n ? n : stop;

    for (std::size_t i = clamped_start; i < clamped_stop; i += step) {
        indices_.push_back(i);
    }
}

std::size_t SliceDataset::size() const {
    return indices_.size();
}

std::int64_t SliceDataset::get(std::size_t index) const {
    if (index >= indices_.size()) {
        throw std::out_of_range("SliceDataset index out of range");
    }
    return parent_->get(indices_[index]);
}

}  // namespace autodata