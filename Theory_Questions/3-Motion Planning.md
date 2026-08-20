# Graph Search Algorithms
Graph searching algorithms are the cornerstone of path planning algorithms, the most popular of which are: BFS, DFS, Dijkstra’s and A\* algorithms
- Briefly describe how each of those algorithms work.  
- Mention the pros and cons of each algorithm.  
BFS:
BFS explores the graph level by level it starts from the initial node then visits all nodes on step away, then all nodes two steps away,and so on.
It uses a queue because nodes that are discovered earlier should be explored earlier. 
This makes BFS good for finding the shortest path in an unweighted graph, because the first time it reaches a goal, it has used the fewest number of edges.

Pros:
- Finds the shortest path in unweighted graphs.
- Guaranteed to find a solution if one exists.
- Never gets stuck in infinite deep loops or blind alleys.
- Finds targets close to the starting point very fast

Cons:
- Not optimal for weighted graphs.
- Requires storing entire levels of nodes in a queue ($O(b^d)$ space complexity), which uses a lot of RAM for wide or deep graphs.
- Takes more time and memory if the target is located far down a deep branch
- Does not use any goal direction information, so it may explore many unnecessary nodes.

DFS:
DFS explores a single path as far as possible until it can't go further before trying other paths. 
It uses a stack because the most recently discovered node quickly only backtracking when it reaches a dead end or any already explored area.
Pros:
- Uses very little memory (O(d) depth-based space) compared to BFS.
- It is highly efficient if there are many solutions along deep branches.
- Useful for backtracking and exhaustive search problems.
Cons:
  Not optimal; it may find a much longer path before a shorter one.
- Not complete in infinite or cyclic graphs unless visited states or depth limits are used.
- Can waste time exploring a poor branch deeply.
- Its performance depends strongly on the order in which neighbors are explored.

Dijkstra:
Dijkstra's algorithm is designed for weighted graphs where moving between nodes has different costs. Instead of exploring based on the number of steps, it explores the node with lowest total cost from the start.
That is why it uses a priority queue: the next node to be explored is the one with the smallest known distance.

Pros:- Works without needing a heuristic.
- Can compute shortest paths from the start node to all other reachable nodes.
- Reliable for weighted maps such as roads, terrain, or cost grids.

Cons:
- Does not work correctly with negative edge weights.
- Can be slow and memory-intensive on large graphs.
- Explores in all directions without considering where the goal is.
- Usually less efficient than A* when a good heuristic is available.
A*:
A* improves on Dijkstra by using a heuristic to guide the search towards the goal.
It still considers the cost already paid to reach a node, but it also estimates how far that node is from the goal.
This means A* tries to balance two questions: “How expensive was it to get here?” and “How promising is this node for reaching the goal?”
f(n) = g(n) + h(n)

g(n) = cost from start to current node
h(n) = estimated cost from current node to goal
f(n) = estimated total path cost through that node


Pros:
- Often faster than Dijkstra because it uses a heuristic to guide the search toward the goal.
- Guarantees the shortest path if the heuristic is admissible and consistent.
- Explores fewer irrelevant nodes when the heuristic is well designed.
- Good for path planning on maps and grids.

Cons:
- Depends heavily on the quality of the heuristic.
- If the heuristic overestimates, A* may lose its shortest-path guarantee.
- If the heuristic is poor, A* can behave almost like Dijkstra.
- Can use a lot of memory because it stores open and closed nodes.
- Designing a good heuristic can be challenging in complex environments.
# Practical Motion Planning
A Vaccum cleaning robot uses A* algorithm to navigate its way through the house, however the paths it navigates are often too rough (Zig-Zag).
- As a motion planning engineer, what could be a solution to this problem in the algorithm?  
- What is the risk of applying such a solution?
The solution would be to modify the cost function to penalize changes in direction/turns, or apply a collision-checked path-smoothing algorithm after A*.
So instead of: Cost = Distance
it could be defined as: Cost = Distance + λ×Turns

The risk would be that adding a turn penalty can cause A* to select a longer path, sacrificing shortest-path optimality. 
Post-processing smoothing can also produce a path that collides with obstacles unless collision checking is performed.