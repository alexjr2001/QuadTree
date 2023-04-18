# QuadTree
Quadtree implementation in C++, we will get a space and a depth desired where we will be able to enter new points, the tree will be initialized with those values and we will create all the children nodes needed for that depth. In order to see the density of every quadrant (this is applied in heat maps). Every time we add a point, we'll see how it works. Firstly, it searches for the right quadrant where the new points belongs when we find the children node or quadrant we add a new point to increase the density. At the end of this recurring process, we can print it out with a function which performs a DFS. Here we have an image to see how it would work in a real heat map:
<p align="center"><img width="200" alt="heatMap" src="https://user-images.githubusercontent.com/63054183/232639312-3124303f-bbf1-47e9-a222-41a6898a7124.png"></p>

## QuadTree code
Now let's deep into the code and how it works:

### Libraries used

```
#include <iostream>
#include <vector>
#include <cmath>
#include <math.h>
```
### Running the project
Firstly, we compile it in the path where is stored [quadtree.cpp](https://github.com/alexjr2001/QuadTree/blob/main/quadtree.cpp):

```
$ g++ quadtree.cpp -o quad.exe 
```
Secondly, we run it:
```
$ ./quad
```

Afterwards we'll find the example already written en in the 'main' function where we add points and then print it out to understand how the quadrants work in this case, let's see the size of the space as input:

<p align="center"><img width="506" alt="image" src="https://user-images.githubusercontent.com/63054183/232635357-8f7c3afc-3eb4-4f33-94b7-b79d6e736f39.png"></p>

Furthermore, in the console we will be able to see the DFS working. The pattern used translated to English is "Node Level (Level) Quantity (num) points Begin (Begin of quadrant x-y) End (End of quadrant x-y)".
<p align="center"><img width="461" alt="image" src="https://user-images.githubusercontent.com/63054183/232640733-d49b72a3-4d29-46f2-be19-430ce45a6ae1.png"></p>
