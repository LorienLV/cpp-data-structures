#include <vector>
#include <list>

#include "../allocators/growing_mem_pool.h"
#include "../allocators/growing_allocator.h"

int main(int argc, char const *argv[]) {
    // Here we are using the default allocator (it calls new and delete directly).
    {
        std::vector<int> vec1;
        std::list<int> list1;
    }

    // This is equivalent to:
    {
        std::allocator<int> alloc;
        std::vector<int, std::allocator<int>> vec1(alloc);
        std::list<int, std::allocator<int>> list1(alloc);
    }

    // Now we use a custom allocator that will avoid calling new and delete
    // as often.
    // The memory pool will hold chunks of at least 1024 elements.
    GrowingMemPool mem_pool(1024);
    // This is just a pointer to the memory pool. We need both a memory pool and
    // a pointer to it to avoid problems with move/copy shenanigans.
    GrowingAllocator<int> growing_alloc(&mem_pool);

    // The custom allocator can be used with std containers.
    // When using lists, the custom allocator is specially useful since
    // otherwise, the list will call new() for each node.
    std::list<int, GrowingAllocator<int>> list1(growing_alloc);
    list1.push_back(1);
    list1.push_back(2);
    list1.push_back(3);
    list1.push_back(4);
    list1.push_back(5);

    return EXIT_SUCCESS;
}
