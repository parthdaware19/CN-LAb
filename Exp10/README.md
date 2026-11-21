# Experiment 10: Distance Vector Routing Algorithm

## C Code (`exp10_230.c`)

```c
#include <stdio.h>

#define MAX_NODES 10
#define INF 999

struct Node {
    int dist[MAX_NODES];
    int from[MAX_NODES];
} rt[MAX_NODES];

int main() {
    int cost[MAX_NODES][MAX_NODES];
    int nodes, i, j, k;
    int updated, iteration;

    printf("Enter number of nodes: ");
    scanf("%d", &nodes);

    if (nodes <= 0 || nodes > MAX_NODES) {
        printf("Invalid number of nodes.\n");
        return 0;
    }

    printf("Enter cost matrix row by row (use 999 for INF/no connection):\n");

    for (i = 0; i < nodes; i++) {
        for (j = 0; j < nodes; j++) {
            scanf("%d", &cost[i][j]);

            if (i == j) {
                cost[i][j] = 0;
            }
        }
    }

    for (i = 0; i < nodes; i++) {
        for (j = 0; j < nodes; j++) {
            rt[i].dist[j] = cost[i][j];

            if (cost[i][j] < INF && i != j) {
                rt[i].from[j] = j;
            } else {
                rt[i].from[j] = -1;
            }
        }
    }

    iteration = 0;

    do {
        updated = 0;
        iteration++;

        for (i = 0; i < nodes; i++) {
            for (j = 0; j < nodes; j++) {
                for (k = 0; k < nodes; k++) {

                    if (cost[i][k] == INF || rt[k].dist[j] == INF) {
                        continue;
                    }

                    if (rt[i].dist[j] >
                        cost[i][k] + rt[k].dist[j]) {

                        rt[i].dist[j] =
                            cost[i][k] + rt[k].dist[j];

                        rt[i].from[j] = k;
                        updated = 1;
                    }
                }
            }
        }

    } while (updated);

    for (i = 0; i < nodes; i++) {
        printf("\nRouting table for Node %d:\n", i);
        printf("Destination\tNext Hop\tDistance\n");

        for (j = 0; j < nodes; j++) {
            if (rt[i].dist[j] == INF) {
                printf("%d\t\t-\t\tINF\n", j);
            } else {
                printf("%d\t\t%d\t\t%d\n",
                       j, rt[i].from[j], rt[i].dist[j]);
            }
        }
    }

    return 0;
}
```

---

## Objective
To simulate the **Distance Vector Routing (DVR)** algorithm using the **Bellman-Ford equation** in C, establishing the shortest path and next-hop forwarding table for each node in a network topology.

---

## Theory

Distance Vector Routing is a dynamic routing algorithm in which each router maintains a vector (table) of minimum distances to every destination node in the network and the next hop to reach it. Routers iteratively exchange routing tables with directly connected neighbors until convergence is reached.

### Bellman-Ford Equation
$$D_x(y) = \min_v \{ c(x,v) + D_v(y) \}$$

Where:
- $D_x(y)$ is the estimated minimum cost from node $x$ to node $y$.
- $c(x,v)$ is the link cost from node $x$ to immediate neighbor $v$.
- $D_v(y)$ is the reported distance from neighbor $v$ to destination $y$.
- The minimum is taken over all neighbors $v$ of node $x$.

---

## Data Structure

```c
#define MAX_NODES 10
#define INF 999

struct Node {
    int dist[MAX_NODES];
    int from[MAX_NODES];
} rt[MAX_NODES];
```

---

## Compilation & Execution

```bash
# Navigate to directory
cd Exp-10-Distance-Vector-Routing

# Compile
gcc exp10_230.c -o exp10_230

# Run
./exp10_230
```

---

## Sample Input

```text
3
0 2 7
2 0 1
7 1 0
```
*(3 nodes. Cost matrix: Node 0 connected to 1 with weight 2, to 2 with weight 7. Node 1 connected to 2 with weight 1)*

### Network Graph
```
 (0) ─────── 2 ─────── (1)
  │                     │
  └────────── 7 ────────┘
              │
             (2)
  (Path 0 -> 1 -> 2 has cost 2 + 1 = 3, which is shorter than direct link 7)
```

---

## Expected Routing Tables

```text
Routing table for Node 0:
Destination    Next Hop    Distance
0              -1          0
1               1          2
2               1          3

Routing table for Node 1:
Destination    Next Hop    Distance
0               0          2
1              -1          0
2               2          1

Routing table for Node 2:
Destination    Next Hop    Distance
0               1          3
1               1          1
2              -1          0
```
