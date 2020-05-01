Lab 3a (Multithreading on example of Johnson algorithm)

Johnson algorithm for sparse graphs calculating all-pair shortest distances using Bellman-Ford algorithm to detect negative cycles and reweight negative edges and Johnson algorithm for fast distances calculating for all vertices.


In parallel version after graph's reweight we devide all vertices on intervals and calculate distances for each vertex of interval in different threads (amount of threads depends on hardware concurrency).


Benchmark results, run on (4 X 2400 MHz CPU s)
![](https://ibb.co/JBCcpWT)
