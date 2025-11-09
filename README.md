# C++ Data Structures

This repository contains custom C++ implementations of data structures and allocators.

## Contents

- `allocators/`
  - `growing_mem_pool.h`: A pool that allocates new memory chunks as needed and does not free individual allocations. It reuses leftover space from the most recently allocated chunk before allocating another. This strategy is useful when you can estimate an upper bound on required memory and do not need per-object reclamation, for example, it can speed up filling a `std::list`.
  - `growing_allocator.h`: An STL-compatible allocator wrapper around `GrowingMemPool`. It is similar in intent to `std::pmr::polymorphic_allocator` and `std::pmr::monotonic_buffer_resource`, but `GrowingMemPool` operates in terms of element counts rather than bytes, which makes it easier to pre-allocate an exact number of elements.

- `data_structures/`
  - `vector.h`: A custom implementation of `std::vector`. It provides a template parameter `AvoidInitIfPossible` which, when set to `true`, avoids default-initializing elements if the stored type is trivial and standard-layout. This can avoid unnecessary initialization when resizing the vector.
  - `segmented_vector.h`: A segmented (chunked) vector that stores elements in fixed-size segments instead of a single contiguous buffer. This reduces the cost of reallocations and preserves stable memory locations for elements. Like the `vector` implementation, it supports `AvoidInitIfPossible`.

- `examples/`: Small test programs demonstrating usage:
  - `test_vector.cpp`
  - `test_segmented_vector.cpp`
  - `test_growing_allocator.cpp`

## Running examples

Build the examples using the repository `Makefile` (from the project root):

```bash
make
```

Then run the example binaries:

```bash
./build/test_vector
./build/test_segmented_vector
./build/test_growing_allocator
```
