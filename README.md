# Overview

This is a library for generating the full set of permutations of a multiset using the algorithm from ["Loopless Generation of Multiset Permutations using a Constant Number of Variables by Prefix Shifts"](https://dl.acm.org/doi/10.5555/1496770.1496877) by Aaron Williams. The implementation has been optmized by replacing the linked list with a list of indices encoding the permutation, essentially making the linked list contiguous. This has the benefit of improving locality, and in the case of a container whose size is known at compile time, completely getting rid of heap allocations.

The library consists of  single header file `muper.hpp` containing the template function `multipermute` that takes any random access container that implements a `size()` method. It also accepts a callable object that does something with the permutation.

Note that due to the requirements of the algorithm, `multipermute` sorts the input multiset into nonincreasing order.

This library uses concepts, a C++20 feature, to constrain the types, but with trivial modifications should be useable with older C++ compilers.

# Demo

```cpp
#include "muper.hpp"

#include <vector>
#include <string>
#include <array>
#include <iostream>

template <typename T>
std::vector<T> permutations(T& multiset)
{
    std::vector<T> perms{};
    auto visitor = [&perms](const T& perm){ perms.push_back(perm); };
    muper::multipermute(multiset, visitor);
    return perms;
}

int main()
{
    std::array<int, 4> array_multiset = {4, 2, 1, 1};
    std::vector<int> vector_multiset = {3, 2, 1};
    std::string string_multiset = "eels";
    
    auto array_perms = permutations(array_multiset);
    auto vector_perms = permutations(vector_multiset);
    auto string_perms = permutations(string_multiset);

    for (const auto& perm : array_perms)
        std::cout << '[' << perm[0] << ", " << perm[1] << ", " << perm[2] << ", " << perm[3] << "] ";
    
    std::cout << '\n';

    for (const auto& perm : vector_perms)
        std::cout << '[' << perm[0] << ", " << perm[1] << ", " << perm[2] << "] ";
    
    std::cout << '\n';

    for (const auto& perm : string_perms)
        std::cout << perm << ' ';

    std::cout << '\n';
}
```
Output:
```
[4, 2, 1, 1] [1, 4, 2, 1] [4, 1, 2, 1] [1, 4, 1, 2] [1, 1, 4, 2] [4, 1, 1, 2] [2, 4, 1, 1] [1, 2, 4, 1] [2, 1, 4, 1] [1, 2, 1, 4] [1, 1, 2, 4] [2, 1, 1, 4]
[3, 2, 1] [1, 3, 2] [3, 1, 2] [2, 3, 1] [1, 2, 3] [2, 1, 3]
slee esle sele esel eesl seel lsee else lese eles eels lees
```