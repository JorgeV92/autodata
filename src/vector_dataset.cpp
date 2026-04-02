#include "autodata/core/vector_dataset.h"

#include <stdexcept>

namespace autodata {

VectorDataset::VectorDataset(std::vector<std::int64_t> data) : data_(std::move(data)) {}

std::size_t VectorDataset::size() const {
    return data_.size();
}

std::int64_t VectorDataset::get(std::size_t index) const {
    if (index >= data_.size()) {
        throw std::out_of_range("VectorDataset index out of range");
    }
    return data_[index];
}

}  // namespace autodata
