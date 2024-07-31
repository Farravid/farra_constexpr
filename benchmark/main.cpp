#include <benchmark/benchmark.h>
#include <map>
#include "interval_map.hpp"
#include "lifeobject.hpp"
#include <boost/icl/interval_map.hpp>

// static void BM_boost_assing(benchmark::State& state)
// {
//     using namespace boost::icl;
//     interval_map<int, int> my_map;

//     for(auto _ : state)
//     {
//         for(int i = 0; i < 1000; ++i)
//             my_map += std::make_pair(boost::icl::interval<int>::closed(1, 5), 10);
//     }
// }
// BENCHMARK(BM_boost_assing)->Iterations(1000);

// static void BM_farra_assing(benchmark::State& state)
// {
//     farra::flat_interval_map<int, int, 10> my_map{-1};

//     for(auto _ : state)
//     {
//         for(int i = 0; i < 1000; ++i)
//             my_map.assign(1,5, 10);
//     }
// }
// BENCHMARK(BM_farra_assing)->Iterations(1000);

// static void initializer_list(benchmark::State& state)
// {
//     for(auto _ : state)
//     {
//         using LO = farra::LifeObject;
//         farra::flat_interval_map<int, LO, 10> my_map
//         {
//             {1, LO{}}, {2, LO{}}, {3, LO{}}, {4, LO{}} ,{5, LO{}},
//             {6, LO{}}, {7, LO{}}, {8, LO{}}, {9, LO{}}, {10, LO{}} 
//         };
//     }
// }
// BENCHMARK(initializer_list)->Iterations(100);

static void parameter_pack(benchmark::State& state)
{
    for(auto _ : state)
    {
        using LO = farra::LifeObject;
        using T = std::pair<int,LO>;
        farra::flat_interval_map<int, LO, 10> my_map
        {
            T{1, LO{}}, T{2, LO{}}, T{3, LO{}}, T{4, LO{}} ,T{5, LO{}},
            T{6, LO{}}, T{7, LO{}}, T{8, LO{}}, T{9, LO{}}, T{10, LO{}} 
        };

        state.SetComplexityN(state.range(0));
    }
}
BENCHMARK(parameter_pack)->Iterations(10000)->Complexity(benchmark::oN);

BENCHMARK_MAIN();
