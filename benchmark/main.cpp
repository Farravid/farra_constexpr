#include <benchmark/benchmark.h>
#include <map>
#include "interval_map.hpp"
#include <boost/icl/interval_map.hpp>

static void BM_boost_assing(benchmark::State& state)
{
    using namespace boost::icl;
    interval_map<int, int> my_map;

    for(auto _ : state)
    {
        for(int i = 0; i < 1000; ++i)
            my_map += std::make_pair(boost::icl::interval<int>::closed(1, 5), 10);
    }
}
BENCHMARK(BM_boost_assing)->Iterations(1000);

static void BM_farra_assing(benchmark::State& state)
{
    farra::flat_interval_map<int, int, 10> my_map{-1};

    for(auto _ : state)
    {
        for(int i = 0; i < 1000; ++i)
            my_map.assign(1,5, 10);
    }
}
BENCHMARK(BM_farra_assing)->Iterations(1000);

BENCHMARK_MAIN();
