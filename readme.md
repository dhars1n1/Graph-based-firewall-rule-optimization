# Network Firewall Rule Optimization System

This system implements a graph-based approach to optimize firewall rules and analyze network connectivity in a multi-subnet environment with varying security levels.

## Components

- `graph.h`: Core data structures and function declarations
- `graph_al.c`: Adjacency list implementation
- `graph_am.c`: Adjacency matrix implementation
- `dfs.c`: Depth-First Search implementation
- `bfs.c`: Breadth-First Search implementation
- `dijkstra.c`: Dijkstra's shortest path algorithm
- `prim.c`: Prim's minimum spanning tree algorithm
- `main.c`: Main program file
- `input.ip`: Input file containing network configuration
- `output.op`: Output file for analysis results

## Compilation

```bash
gcc -o network_analyzer main.c graph_al.c graph_am.c dfs.c bfs.c dijkstra.c prim.c
```

## Input File Format

The input file (`input.ip`) should follow this format:
```
num_vertices num_edges
src dest bandwidth latency source_ip dest_ip allow security_level
```

Where:
- `num_vertices`: Total number of network devices
- `num_edges`: Total number of connections
- `src`, `dest`: Source and destination vertex indices
- `bandwidth`: Connection bandwidth
- `latency`: Connection latency
- `source_ip`, `dest_ip`: IP addresses
- `allow`: 1 for allow, 0 for deny
- `security_level`: 0 (LOW), 1 (MEDIUM), 2 (HIGH)

## Output

The program generates an `output.op` file containing:
- Results of DFS traversal
- Results of BFS traversal
- Shortest paths (Dijkstra's algorithm)
- Minimum spanning tree (Prim's algorithm)
- Firewall rule violations and optimizations

## Security Levels

The system supports three security levels:
- LOW: General office devices
- MEDIUM: Workstations with security protocols
- HIGH: Sensitive devices with strict access controls

## Features

1. Graph representation using both adjacency list and matrix
2. Firewall rule enforcement during graph traversal
3. Path optimization considering:
   - Bandwidth
   - Latency
   - Security levels
   - Firewall rules
4. Comprehensive output logging

## Error Handling

The system includes error handling for:
- File I/O operations
- Memory allocation
- Invalid input data
- Firewall rule violations

## Performance Considerations

- Adjacency List: O(V + E) space complexity
- Adjacency Matrix: O(V²) space complexity
- DFS/BFS: O(V + E) time complexity
- Dijkstra's Algorithm: O(V² + E) time complexity
- Prim's Algorithm: O(V² + E) time complexity

Where V is the number of vertices and E is the number of edges.