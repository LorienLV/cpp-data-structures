#include <iostream>

#include "../data_structures/segmented_vector.h"

int main(int argc, char const *argv[]) {
    {
        constexpr std::size_t segment_size = 16;
        constexpr bool avoid_init = true;

        SegmentedVector<int, segment_size, avoid_init> vec1;
        vec1.realloc(20);

        for (int i = 0; i < 20; ++i) {
            vec1.push_back(i);
        }

        vec1.resize(0);

        // Since avoid_init is true and the vector type is standard layout and
        // trivial, the vector will not initialize the elements to maximize
        // performance.
        vec1.resize(20);

        if (vec1[1] != 1) {
            std::cerr << "vec1[1] != 1 after resize with avoid_init\n";
            return EXIT_FAILURE;
        }

        auto prev_addr = &vec1[0];

        // We can realloc without changing the memory location of the elements.
        vec1.realloc(40);

        if (&vec1[0] != prev_addr) {
            std::cerr << "&vec1[0] changed after realloc\n";
            return EXIT_FAILURE;
        }
    }

    return 0;
}
