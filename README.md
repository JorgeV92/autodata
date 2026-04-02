## autodata

`autodata` is a C++-first library for reading and processing machine learning and deep learning data. It is intended to support the data pipeline side of training and evaluation workloads, including dataset reading, transformation, shuffling, batching, and iteration.

The goal of the project is to provide a fast, extensible backend for building data pipelines used to train and evaluate models, with Python bindings for integration into ML workflows.

C++ for backend to make it *fast* at least I hope.

## C++ example

```cpp
#include "autodata/core/range_dataset.h"
#include <iostream>

int main() {
    autodata::RangeDataset ds(0, 5);
    for (std::size_t i = 0; i < ds.size(); ++i) {
        std::cout << ds.get(i) << "\n";
    }
}
```

## Design notes

### 1. Immutable dataset nodes
Every transform creates a new dataset node that wraps a parent dataset through `std::shared_ptr`.
This makes pipelines easy to compose and safe to share.

### 2. Keep random-access simple first
The Grain-style split between random-access datasets and iterable datasets is important, but the best first milestone is a correct random-access core.
This repo is set up so you can add:
- `IterDataset<T>`
- `MapToIterDataset`
- `PrefetchIterDataset`

without rewriting the existing random-access nodes.