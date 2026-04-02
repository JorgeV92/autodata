#include "autodata/core/shuffle_dataset.h"

#include <algorithm>
#include <numeric>
#include <random>
#include <stdexcept>

namespace autodata {

ShuffleDataset::ShuffleDataset(MapDatasetI64Ptr parent, std::uint64_t seed)
    : parent_(std::move(parent)), permutation_(parent_ ? parent_->size() : 0) {
    if (!parent_) {
        throw std::invalid_argument("ShuffleDataset requires a non-null parent dataset");
    }

    std::iota(permutation_.begin(), permutation_.end(), static_cast<std::size_t>(0));
    std::mt19937_64 rng(seed);
    std::shuffle(permutation_.begin(), permutation_.end(), rng);
}

std::size_t ShuffleDataset::size() const {
    return permutation_.size();
}

std::int64_t ShuffleDataset::get(std::size_t index) const {
    if (index >= permutation_.size()) {
        throw std::out_of_range("ShuffleDataset index out of range");
    }
    return parent_->get(permutation_[index]);
}

}  // namespace autodata
