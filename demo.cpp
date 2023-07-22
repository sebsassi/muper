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