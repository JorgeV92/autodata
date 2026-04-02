#include "autodata/core/range_dataset.h"

#include <cstddef>
#include <cstdint>

namespace autodata {

namespace {
std::size_t compute_size(std::int64_t start, std::int64_t stop, std::int64_t step) {
    if (step == 0) {
        throw std::invalid_argument("step must not be zero");
    }

    if ((step > 0 && start >= stop) || (step < 0 && start <= stop)) {
        return 0;
    }

    const std::int64_t distance = stop - start;
    std::int64_t n = distance / step;
    if (distance % step != 0) {
        ++n;
    }
    if (n < 0) {
        return 0;
    }
    return static_cast<std::size_t>(n);
}
}  // namespace

RangeDataset::RangeDataset(std::int64_t start, std::int64_t stop, std::int64_t step)
    : start_(start), stop_(stop), step_(step), size_(compute_size(start, stop, step)) {}

std::size_t RangeDataset::size() const {
    return size_;
}

std::int64_t RangeDataset::get(std::size_t index) const {
    if (index >= size_) {
        throw std::out_of_range("RangeDataset index out of range");
    }
    return start_ + static_cast<std::int64_t>(index) * step_;
}

}  // namespace autodata