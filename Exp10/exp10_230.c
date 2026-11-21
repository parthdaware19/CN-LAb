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
