# Shortest path problem (Algorithms Comparison) 
## By: Almog Geva & Matan Breizman



> In graph theory, the shortest path problem is the problem of finding a path between two vertices (or nodes) in a graph such that the sum of the weights of its constituent edges is minimized.

Solving the stated problem using:
* **Dijkstra's algorithm** (Using Min-heap)
* **Dijkstra's algorithm** (Using Unsorted array)
* **Bellman–Ford algorithm**

### Data Structures

Comparing all three methods using 
* **Adjacency List**
* **Adjacency Matrix**

### Comparison
The Timing results will be written to the <Output file>

```
Adjacency Dijkstra heap  0.000033 sec
Adjacency Dijkstra array 0.000024600 sec
Adjacency Bellman Ford   0.000087600 sec
Matrix Dijkstra heap     0.000044100 sec
Matrix Dijkstra array    0.000025400 sec
Matrix Bellman Ford      0.000048300 sec
```

## Usage

```python
main.cpp <Source File> <Output File>
```



### Syntax for source file Example
- Vertex Amount
- Main Source Vertex
- Main Destination Vertex

For each Edge **(u,v)**:
- <**u**><**v**> <**Weight**> 

### Example
```
6
1
6
1 2 16
1 3 13
2 3 10
```

For the Example given, the result printed will be the minimum weight between 1 to 6.
