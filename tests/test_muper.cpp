#include "muper.hpp"

#include <array>
#include <vector>
#include <string>
#include <cassert>

bool multipermute_passes_empty_container()
{
    std::array<int, 0> multiset{};
    std::vector<std::array<int, 0>> permutations{};
    auto f = [&permutations](const std::array<int, 0>& perm)
    {
        permutations.push_back(perm);
    };
    muper::multipermute(multiset, f);
    return permutations.size() == 0;
}

bool multipermute_generates_length_1_sequence_for_1_element()
{
    std::array<int, 1> multiset = {1};
    std::vector<std::array<int, 1>> permutations{};
    auto f = [&permutations](const std::array<int, 1>& perm)
    {
        permutations.push_back(perm);
    };
    muper::multipermute(multiset, f);
    return permutations.size() == 1 && permutations[0] == std::array<int, 1>{1};
}

bool multipermute_array_generates_correct_sequence()
{
    std::array<int, 4> multiset = {4, 2, 1, 1};
    std::vector<std::array<int, 4>> permutations{};
    auto f = [&permutations](const std::array<int, 4>& perm)
    {
        permutations.push_back(perm);
    };
    muper::multipermute(multiset, f);
    std::vector<std::array<int, 4>> correct_permutations = {
        std::array<int, 4>{4, 2, 1, 1},
        std::array<int, 4>{1, 4, 2, 1},
        std::array<int, 4>{4, 1, 2, 1},
        std::array<int, 4>{1, 4, 1, 2},
        std::array<int, 4>{1, 1, 4, 2},
        std::array<int, 4>{4, 1, 1, 2},
        std::array<int, 4>{2, 4, 1, 1},
        std::array<int, 4>{1, 2, 4, 1},
        std::array<int, 4>{2, 1, 4, 1},
        std::array<int, 4>{1, 2, 1, 4},
        std::array<int, 4>{1, 1, 2, 4},
        std::array<int, 4>{2, 1, 1, 4}
    };
    return permutations == correct_permutations;
}

bool multipermute_vector_generates_correct_sequence()
{
    std::vector<int> multiset = {4, 2, 1, 1};
    std::vector<std::vector<int>> permutations{};
    auto f = [&permutations](const std::vector<int>& perm)
    {
        permutations.push_back(perm);
    };
    muper::multipermute(multiset, f);
    std::vector<std::vector<int>> correct_permutations = {
        std::vector<int>{4, 2, 1, 1},
        std::vector<int>{1, 4, 2, 1},
        std::vector<int>{4, 1, 2, 1},
        std::vector<int>{1, 4, 1, 2},
        std::vector<int>{1, 1, 4, 2},
        std::vector<int>{4, 1, 1, 2},
        std::vector<int>{2, 4, 1, 1},
        std::vector<int>{1, 2, 4, 1},
        std::vector<int>{2, 1, 4, 1},
        std::vector<int>{1, 2, 1, 4},
        std::vector<int>{1, 1, 2, 4},
        std::vector<int>{2, 1, 1, 4}
    };
    return permutations == correct_permutations;
}

bool multipermute_string_generates_correct_sequence()
{
    std::string multiset = "dbaa";
    std::vector<std::string> permutations{};
    auto f = [&permutations](const std::string& perm)
    {
        permutations.push_back(perm);
    };
    muper::multipermute(multiset, f);
    std::vector<std::string> correct_permutations = {
        "dbaa",
        "adba",
        "daba",
        "adab",
        "aadb",
        "daab",
        "bdaa",
        "abda",
        "bada",
        "abad",
        "aabd",
        "baad"
    };
    return permutations == correct_permutations;
}

int main()
{
    assert(multipermute_passes_empty_container());
    assert(multipermute_generates_length_1_sequence_for_1_element());
    assert(multipermute_array_generates_correct_sequence());
    assert(multipermute_vector_generates_correct_sequence());
    assert(multipermute_string_generates_correct_sequence());
}