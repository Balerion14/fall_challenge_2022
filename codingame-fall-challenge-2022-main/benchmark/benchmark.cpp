/**
 * @authors :
 * - Sorann753 (Arthus Doriath)
 * - Balerion14
 * - Snowsdy
 * @date december 2022
 */

#include <benchmark/benchmark.h>

/**
 * just an example of usage
 */

void BM_empty(benchmark::State& state) {
    for (auto _ : state) {
        benchmark::DoNotOptimize(state.iterations());
    }
}

BENCHMARK(BM_empty);
BENCHMARK(BM_empty)->ThreadPerCpu();