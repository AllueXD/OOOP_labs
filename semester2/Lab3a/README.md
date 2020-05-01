# Lab 3a (Multithreading on example of Johnson algorithm)

## Description
Johnson algorithm for sparse graphs calculating all-pair shortest distances using Bellman-Ford algorithm to detect negative cycles and reweight negative edges and Johnson algorithm for fast distances calculating for all vertices.


In parallel version after graph's reweight we devide all vertices on intervals and calculate distances for each vertex of interval in different threads (amount of threads depends on hardware concurrency).


## Benchmark

Benchmark results, run on (4 X 2400 MHz CPU s)
![](https://imgur.com/N7xcGr2.png)


Simple Johnson's algortihm
Amount of vertices | Time
------------ | -------------
100 | 22.9
200 | 165
300 | 570
400 | 1977
500 | 3946
600 | 6989
700 | 8427
800 | 10617
900 | 13325
1000 | 18460


Johnson's algorithm with multitreading
Amount of vertices | Time
------------ | -------------
100 | 16.1
200 | 87.7
300 | 287
400 | 543
500 | 1168
600 | 1760
700 | 2931
800 | 4096
900 | 5102
1000 | 6807
