# COSC4310_PROJECT

PROJECT
A C++ performance analysis tool that simulates and compares the three primary CPU cache mapping strategies: Direct Mapping, Fully Associative Mapping, and Set-Associative Mapping.

Overview
This simulator evaluates how different cache architectures handle memory access patterns. By inputting custom latency values for cache hits, memory misses, and comparison cycles, users can see a real-time side-by-side comparison of hits, misses, and total execution time across all three mapping techniques.

Technical Features
Direct Mapping: Implements a modulo-based placement policy (Block Number %  Number of Lines).
Fully Associative Mapping: Simulates a flexible placement strategy with a linear search comparison logic.
N-Way Set Associative Mapping: Partitions the cache into sets to balance the speed of direct mapping with the flexibility of associative mapping.
Performance Metrics: Calculates total latency (in seconds), Hit/Miss counts, and provides a per-call trace of the cache state.

Implementation Details
The simulator manages a simulated 100-block Main Memory and a configurable Cache size. It tracks performance using the following logic:
  Hit Logic: Data found in cache; latency equals timeToReadFromCache.
  Miss Logic: Data fetched from main memory; latency equals timeToReadFromMemory + timeToReadFromCache.
  Comparison Penalty: For associative mappings, the simulator adds timeToCompare for every line checked,     
  simulating real-world hardware gate delays.

Tech Stack
  Language: C++
  Concepts: Computer Architecture, Memory Hierarchy, Cache Tagging, Performance Modeling

Sample Output
The program generates a comparison table after a sequence of memory calls:
Metric        Direct Map  Fully Associative  Set Associative
Total Time      0.045s       0.072s              0.055s
Hits             4            6                    5
Misses           6            4                    5
