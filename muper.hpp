#pragma once

#include <vector>
#include <array>
#include <iterator>
#include <concepts>
#include <type_traits>

namespace muper
{

template <typename T>
concept sized_random_accessible
    = std::random_access_iterator<typename T::iterator>
    && requires (T a) { a.size(); };

template <typename T>
concept tuple_like = requires { std::tuple_size<T>::value; };

template <tuple_like Container, typename IndexContainer>
constexpr Container permutation_to(
    const Container& multiset, const IndexContainer& permutation,
    std::size_t head)
{
    Container res{};
    std::size_t ind = head;
    for (std::size_t i = 0; i < multiset.size(); ++i)
    {
        res[i] = multiset[ind];
        ind = permutation[ind];
    }
    return res;
}

template <typename Container, typename IndexContainer>
constexpr Container permutation_to(
    const Container& multiset, const IndexContainer& permutation,
    std::size_t head)
{
    auto res = Container(multiset.size(), 0);
    std::size_t ind = head;
    for (std::size_t i = 0; i < multiset.size(); ++i)
    {
        res[i] = multiset[ind];
        ind = permutation[ind];
    }
    return res;
}

template <tuple_like C>
std::array<std::size_t, std::tuple_size<C>::value> init(const C& multiset)
{
    std::array<std::size_t, std::tuple_size<C>::value> permutation{};
    for (std::size_t i = 0; i < multiset.size(); ++i)
        permutation[i] = i + 1;
    return permutation;
}

template <typename C>
std::vector<std::size_t> init(const C& multiset)
{
    auto permutation = std::vector<std::size_t>(multiset.size());
    for (std::size_t i = 0; i < multiset.size(); ++i)
        permutation[i] = i + 1;
    return permutation;
}

template <sized_random_accessible Container, typename FuncType>
constexpr void multipermute(Container& multiset, FuncType f)
{
    if (multiset.size() == 0) return;

    std::sort(
        multiset.begin(), multiset.end(),
        std::greater<typename Container::value_type>());
    auto permutation = init(multiset);
    
    std::size_t head = 0;
    f(permutation_to(multiset, permutation, 0));

    std::size_t i = std::max(multiset.size(), 2UL) - 2UL;
    std::size_t j = multiset.size() - 1UL;
    while (permutation[j] != multiset.size() || multiset[j] < multiset[head])
    {
        std::size_t s = i;
        if (permutation[j] != multiset.size())
            if (multiset[i] >= multiset[permutation[j]])
                s = j;
        const std::size_t temp = permutation[s];
        permutation[s] = permutation[temp];
        permutation[temp] = head;
        if (multiset[temp] < multiset[head])
            i = temp;
        j = permutation[i];
        head = temp;
        f(permutation_to(multiset, permutation, head));
    } 
}

}

