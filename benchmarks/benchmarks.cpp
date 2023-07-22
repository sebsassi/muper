#include "muper.hpp"
#include "multipermute.h"

#include <chrono>
#include <iostream>

template <typename Container>
std::string container_label()
{
    if constexpr (std::is_same_v<Container, std::vector<typename Container::value_type>>)
        return "vector";
    else if constexpr (std::is_same_v<Container, std::array<typename Container::value_type, std::tuple_size<Container>::value>>)
        return "array";
    else
        return "unkown container";
}

class Timer
{
public:
    void start()
    {
        start_time = std::chrono::high_resolution_clock::now();
    }

    void stop()
    {
        stop_time = std::chrono::high_resolution_clock::now();
    }

    double measure()
    {
        return double(std::chrono::duration_cast<std::chrono::microseconds>
        (stop_time - start_time).count());
    }

private:
    std::chrono::high_resolution_clock::time_point start_time;
    std::chrono::high_resolution_clock::time_point stop_time;
};

template <typename Generator>
struct Benchmark
{
    template <typename Container>
    static void run(Container& multiset, std::size_t count)
    {
        std::sort(multiset.begin(), multiset.end(), std::greater<>());
        const std::string label = container_label<Container>();
        Timer timer{};
        std::vector<Container> permutations{};
        std::size_t num_perms = 0;
        auto collector = [&permutations, &num_perms]([[maybe_unused]] const Container& permutation)
        {
            ++num_perms;
        };

        timer.start();
        for (std::size_t i = 0; i < count; ++i)
        {
            permutations.clear();
            num_perms = 0;
            Generator::permute(multiset, collector);
        }
        timer.stop();
        print_result(multiset.size(), count, timer.measure(), label, num_perms);
    }

    static void print_result(std::size_t size, std::size_t count, double time, const std::string& label, std::size_t num_perms)
    {
        std::cout << Generator::label() << ' ' << label << " size " << size << "\t" << time/double(count*num_perms) << " microseconds/permutation\n";
    }
};

struct MultipermuteGenerator
{
    template <typename Container, typename FuncType>
    static void permute(Container& multiset, FuncType f)
    {
        multipermute(multiset, f);
    }

    static constexpr const char* label() { return "multiper"; }
};

struct MuperGenerator
{
    template <typename Container, typename FuncType>
    static void permute(Container& multiset, FuncType f)
    {
        muper::multipermute(multiset, f);
    }

    static constexpr const char* label() { return "altper"; }
};

int main()
{
    using MultipermuteBenchmark = Benchmark<MultipermuteGenerator>;
    using MuperBenchmark = Benchmark<MuperGenerator>;

    std::cout << "Two unique elements\n";

    std::array<int, 2> multiset_u2 = {2,1};
    MultipermuteBenchmark::run(multiset_u2, 1000000);
    MuperBenchmark::run(multiset_u2, 1000000);
    std::cout << '\n';

    std::array<int, 3> multiset_u3 = {3,1,1};
    MultipermuteBenchmark::run(multiset_u3, 1000000);
    MuperBenchmark::run(multiset_u3, 1000000);
    std::cout << '\n';

    std::array<int, 5> multiset_u5 = {5,1,1,1,1};
    MultipermuteBenchmark::run(multiset_u5, 1000000);
    MuperBenchmark::run(multiset_u5, 1000000);
    std::cout << '\n';

    std::array<int, 8> multiset_u8 = {8,1,1,1,1,1,1,1};
    MultipermuteBenchmark::run(multiset_u8, 1000000);
    MuperBenchmark::run(multiset_u8, 1000000);
    std::cout << '\n';

    std::array<int, 16> multiset_u16 = {16,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1};
    MultipermuteBenchmark::run(multiset_u16, 1000000);
    MuperBenchmark::run(multiset_u16, 1000000);
    std::cout << '\n';

    std::array<int, 32> multiset_u32 = {16,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1};
    MultipermuteBenchmark::run(multiset_u32, 1000000);
    MuperBenchmark::run(multiset_u32, 1000000);

    std::cout << "\nMaximal elements\n";

    std::array<int, 2> multiset_m2 = {2,1};
    MultipermuteBenchmark::run(multiset_m2, 1000000);
    MuperBenchmark::run(multiset_m2, 1000000);
    std::cout << '\n';

    std::array<int, 3> multiset_m3 = {3,2,1};
    MultipermuteBenchmark::run(multiset_m3, 1000000);
    MuperBenchmark::run(multiset_m3, 1000000);
    std::cout << '\n';

    std::array<int, 5> multiset_m5 = {5,4,3,2,1};
    MultipermuteBenchmark::run(multiset_m5, 10000);
    MuperBenchmark::run(multiset_m5, 10000);
    std::cout << '\n';

    std::array<int, 7> multiset_m7 = {7,6,5,4,3,2,1};
    MultipermuteBenchmark::run(multiset_m7, 10000);
    MuperBenchmark::run(multiset_m7, 10000);
    std::cout << '\n';

    std::array<int, 10> multiset_m10 = {10,9,8,7,6,5,4,3,2,1};
    MultipermuteBenchmark::run(multiset_m10, 20);
    MuperBenchmark::run(multiset_m10, 20);
}