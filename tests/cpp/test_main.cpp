#include "autodata/core/fixed_batch_dataset.h"
#include "autodata/core/range_dataset.h"
#include "autodata/core/shuffle_dataset.h"
#include "autodata/core/slice_dataset.h"
#include "autodata/core/vector_dataset.h"

#include <cassert>
#include <cstdint>
#include <iostream>
#include <memory>
#include <set>
#include <vector>

int main() {
    {
        autodata::RangeDataset ds(0, 5);
        assert(ds.size() == 5);
        assert(ds.get(0) == 0);
        assert(ds.get(4) == 4);
    }

    {
        autodata::RangeDataset ds(0, 10, 2);
        assert(ds.size() == 5);
        assert(ds.get(0) == 0);
        assert(ds.get(1) == 2);
        assert(ds.get(4) == 8);
    }

    {
        autodata::VectorDataset ds({10, 20, 30});
        assert(ds.size() == 3);
        assert(ds.get(2) == 30);
    }

    {
        auto base = std::make_shared<autodata::RangeDataset>(0, 8);
        autodata::ShuffleDataset shuffled(base, 7);
        assert(shuffled.size() == 8);
        std::set<std::int64_t> seen;
        for (std::size_t i = 0; i < shuffled.size(); ++i) {
            seen.insert(shuffled.get(i));
        }
        assert(seen.size() == 8);
        assert(*seen.begin() == 0);
        assert(*seen.rbegin() == 7);
    }

    {
        auto base = std::make_shared<autodata::RangeDataset>(0, 10);
        autodata::SliceDataset sliced(base, 2, 9, 3);
        assert(sliced.size() == 3);
        assert(sliced.get(0) == 2);
        assert(sliced.get(1) == 5);
        assert(sliced.get(2) == 8);
    }

    {
        auto base = std::make_shared<autodata::RangeDataset>(0, 10);
        autodata::FixedBatchDataset batches(base, 4, false);
        assert(batches.size() == 3);
        assert((batches.get(0) == std::vector<std::int64_t>{0, 1, 2, 3}));
        assert((batches.get(1) == std::vector<std::int64_t>{4, 5, 6, 7}));
        assert((batches.get(2) == std::vector<std::int64_t>{8, 9}));
    }

    {
        auto base = std::make_shared<autodata::RangeDataset>(0, 10);
        autodata::FixedBatchDataset batches(base, 4, true);
        assert(batches.size() == 2);
        assert((batches.get(0) == std::vector<std::int64_t>{0, 1, 2, 3}));
        assert((batches.get(1) == std::vector<std::int64_t>{4, 5, 6, 7}));
    }

    std::cout << "All autodata C++ tests passed.\n";
    return 0;
}