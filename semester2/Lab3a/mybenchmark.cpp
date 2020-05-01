#include "3rdparty/benchmark/include/benchmark/benchmark.h"

#include "include/Graph.hpp"
#include "include/GraphAlgorithms.hpp"

#include<random>
#include<map>
#include<vector>

using namespace graph;
class MapOfGraphs {
protected:
    static MapOfGraphs* map;

    std::map<int, Graph<int>> generated;

    MapOfGraphs() {
        std::random_device rd;
        std::mt19937 gen(rd());

        for (int i = 100; i <= 1000; i += 100) {
            Graph<int> currGraph(std::vector(i, 1));
            std::uniform_int_distribution<> verticesDist(0, i - 1);
            std::uniform_int_distribution<> weightDist(1, 100);
            for (int j = 0; j < i; j++) {
                currGraph.addEdge(verticesDist(gen), verticesDist(gen), weightDist(gen));
            }
            generated.emplace(i, currGraph);
        }
    }

public:

    static MapOfGraphs* getInstance() {
        if (map == nullptr) {
            map = new MapOfGraphs();
        }
        return map;
    }

    Graph<int> getByKey(int key) {
        return generated.find(key)->second;
    }
};

MapOfGraphs* MapOfGraphs::map = nullptr;

static void BENCHMARK_Johnson(benchmark::State& state) {
    Graph<int> graph = MapOfGraphs::getInstance()->getByKey(state.range(0));
    for (auto _ : state) {
        algorithm::Johnson(graph);
    }
}

static void BENCHMARK_JohnsonParallel(benchmark::State& state) {
    Graph<int> graph = MapOfGraphs::getInstance()->getByKey(state.range(0));
    for (auto _ : state) {
        algorithm::Johnson(graph, true);
    }
}

BENCHMARK(BENCHMARK_Johnson)->DenseRange(100, 1000, 100)->Unit(benchmark::kMillisecond);
BENCHMARK(BENCHMARK_JohnsonParallel)->DenseRange(100, 1000, 100)->Unit(benchmark::kMillisecond);

BENCHMARK_MAIN();