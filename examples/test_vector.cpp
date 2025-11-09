#include <iostream>

#include "../data_structures/vector.h"

int main(int argc, char const *argv[]) {
    {
        constexpr bool avoid_init = true;

        Vector<int, avoid_init> vec1;
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
    }
    return 0;
}
