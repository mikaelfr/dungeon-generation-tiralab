# Project Specification

## Planned data-structures and algorithms

Data-structures:

* Dynamic array
* Graph
* Vector 
* Binary heap

Algorithms:

* Pseudorandom number generation
* Fast 2D AABB test
* Delaunay triangulation
* Minimum spanning tree

## Goal
This project's goal is to be able to generate a randomized dungeon deterministically from a given seed. Using these algorithms and data-structures produces a dungeon with straight hallways and corridors, giving it a man-made feel.

## Estimated time and space complexities
### Pseudorandom number generation
Time: Mersenne twister `O(1)`

Space: Mersenne twister `O(1)`


### Fast 2D AABB test
`n` refers to the number of potential rooms generated

Time: Stable merge sort `O(n log n)`

Space: Stable merge sort `O(n)`


### Delaunay triangulation
`n` refers to the number of selected rooms

Time: Using an incremental flip `O(n log n)`

Space: Using an incremental flip `O(n)`


### Minimum spanning tree
`e` refers to the number of edges in the graph generated by Delaunay triangulation

`v` refers to the number of vertices in the graph generated by Delaunay triangulation

Time: Prim's algorithm `O(e log v)`

Space: Prim's algorithm `O(v)`


## Sources

[General rundown of the basic room generation algorithm](https://www.gamasutra.com/blogs/AAdonaac/20150903/252889/Procedural_Dungeon_Generation_Algorithm.php)

[2D AABB test](https://www.gamedev.net/forums/topic/619296-ultra-fast-2d-aabb-overlap-test/)

[Sorting algorithms](https://en.wikipedia.org/wiki/Sorting_algorithm)

[Delaunay triangulation](https://en.wikipedia.org/wiki/Delaunay_triangulation#Algorithms)

[Prim's algorithm](https://en.wikipedia.org/wiki/Prim%27s_algorithm)

[Prim's algorithm space complexity](https://www.quora.com/What-is-the-space-complexity-of-Prims-algorithm)

[Mersenne Twister](https://en.wikipedia.org/wiki/Mersenne_Twister)

[Mersenne Twister time complexity](https://stackoverflow.com/questions/25651532/what-is-the-time-complexity-of-the-mersenne-twister)

## Misc

Degree programme: Bachelor's in Mathematics

Documentation language: English

Programming language: C++