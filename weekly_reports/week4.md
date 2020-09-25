# Weekly report for week 4
## This week's progress
Approx. time spent: 15h

This week was almost entirely dedicated to finishing up the triangulation algorithm. I did have some time to refine data structures and make them easier to use, though. I also added some new data structures in preparation for a minimum spanning tree algorithm.

## What I learned this week
This week I learned one possible approach to turning a set of vertices into a nice looking triangulated mesh. Even though in this project the triangulation is just a checkpoint, but I can see the same algorithm being very useful in the future.

Another thing I learned this week was something that had been bugging me for a while. Many programming languages (especially dynamically typed ones) have a way of iterating through the member variables of an object. In C++ this is not possible out of the box (to my knowledge). This week I found a way of iterating through a subset of member variables or "emergent" member variables (I'm using "emergent" to refer to situations like dynamically building edges from a set of points during iteration, the edges don't exist as variables themselves but it is very easy to build them out of the vertices of a triangle). Although the implementation is limited to member variables of the same type per iterator, it is still extremely useful. The code looks a lot simpler and cleaner. Figuring out how to make that happen taught me a lot about how C++ handles for-each iteration and how iterators work under the hood.

## Problems?
I ran into a problem with the original algorithm I was planning on implementing, Delaunay triangulation using flips. I was unable to get it working for one reason or another. Either way, I found out about Bowyer-Watson algorithm which was much more straight forward to implement. One drawback to my naive implementation of Bowyer-Watson is the increased time complexity, from O(n log n) to O(n^2). This can apparently be lowered to O(n log n) with some clever use of triangle connectivity, but I haven't looked into that yet. I might do that if I have some spare time later on in the course.

## Next up?
Next week I'll try to finish the basic generation if possible. Gotta hope I won't run into many problems implementing a minimum spanning tree algorithm and doing the last finishing touches of the generation (selecting rooms and filling blank space).
