#pragma once

#include <list>
#include <iostream>

#define DEBUG 1

/**
 * A memory pull that only creates new chunks, it does not allow deallocation.
 *
 */

class GrowingMemPool {
public:
    /**
     * Construct an empty memory pool. When requested, the pool will
     * allocated at least min_chunk_elements elements.
     *
     * @param min_chunk_elements The minimum number of elements that
     * the pool will allocate when requested.
     */
    GrowingMemPool(std::size_t min_chunk_elements) noexcept
        : min_chunk_elements_(min_chunk_elements){};

    /**
     * Deallocate all the memory allocated.
     *
     */
    ~GrowingMemPool() noexcept {
        for (auto &chunk : chunks_) {
            ::operator delete(static_cast<void *>(chunk.data));
        }
    };

    // Do not allow copy.
    GrowingMemPool(const GrowingMemPool &) = delete;
    GrowingMemPool &operator=(const GrowingMemPool &) = delete;

    /**
     * Allocate memory for num_elements elements of size element_bytes.
     * Use previously allocated unused bytes if possible.
     *
     * @param num_elements The number of elements to allocate.
     * @param element_bytes The size of each element.
     * @return void* A pointer to the allocated memory.
     */
    void *allocate(std::size_t num_elements, std::size_t element_bytes) {
        const std::size_t new_bytes = num_elements * element_bytes;

        const bool new_chunk = chunks_.empty() || chunks_.back().total_bytes -
                                                         chunks_.back().used_bytes <
                                                     new_bytes;

        void *ret = nullptr;

        if (new_chunk) {
            const std::size_t min_chunk_bytes = min_chunk_elements_ * element_bytes;
            const std::size_t chunk_bytes = std::max(min_chunk_bytes, new_bytes);
            ret = ::operator new(chunk_bytes);
#if DEBUG
            std::cerr << "Allocated " << chunk_bytes << " bytes\n";
#endif
            chunks_.push_back({chunk_bytes, new_bytes, static_cast<std::byte *>(ret)});
        }
        else {
            ret = static_cast<void *>(chunks_.back().data + chunks_.back().used_bytes);
            std::cerr << "Using " << new_bytes << " bytes in chunk " << chunks_.size() - 1 << "\n";
            chunks_.back().used_bytes += new_bytes;
        }

        return ret;
    }

private:
    struct Chunk {
        std::size_t total_bytes;
        std::size_t used_bytes;
        std::byte *data;
    };
    std::list<Chunk> chunks_;

    std::size_t min_chunk_elements_;
};