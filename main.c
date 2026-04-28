#include <stdio.h>
#include <limits.h>
#include <stdbool.h>
#include <string.h>

#define MAXN 20
#define INF 1000000000

int n;
int graph[MAXN][MAXN];

// -------------------- DIJKSTRA (GREEDY) --------------------
int minDistance(int dist[], bool visited[]) {
    int min = INF, min_index = -1;
    for (int i = 0; i < n; i++) {
        if (!visited[i] && dist[i] <= min) {
            min = dist[i];
            min_index = i;
        }
    }
    return min_index;
}

void dijkstra(int src) {
    int dist[MAXN];
    bool visited[MAXN];

    for (int i = 0; i < n; i++) {
        dist[i] = INF;
        visited[i] = false;
    }

    dist[src] = 0;

    for (int count = 0; count < n - 1; count++) {
        int u = minDistance(dist, visited);
        if (u == -1) break;
        visited[u] = true;

        for (int v = 0; v < n; v++) {
            if (!visited[v] && graph[u][v] != INF &&
                dist[u] + graph[u][v] < dist[v]) {
                dist[v] = dist[u] + graph[u][v];
            }
        }
    }

    printf("\nShortest distances from city %d:\n", src);
    for (int i = 0; i < n; i++) {
        printf("To city %d = %d\n", i, dist[i]);
    }
}

// -------------------- TSP (DP + BITMASK) --------------------
int dp[1 << MAXN][MAXN];

int tsp(int mask, int pos) {
    if (mask == (1 << n) - 1)
        return graph[pos][0];  // return to start

    if (dp[mask][pos] != -1)
        return dp[mask][pos];

    int ans = INF;

    for (int city = 0; city < n; city++) {
        if ((mask & (1 << city)) == 0 && graph[pos][city] != INF) {
            int newAns = graph[pos][city] +
                         tsp(mask | (1 << city), city);
            if (newAns < ans)
                ans = newAns;
        }
    }

    dp[mask][pos] = ans;
    return ans;
}

// -------------------- MAIN --------------------
int main() {
    int m;
    printf("Enter number of cities: ");
    scanf("%d", &n);

    printf("Enter number of roads: ");
    scanf("%d", &m);

    // Initialize graph
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (i == j) graph[i][j] = 0;
            else graph[i][j] = INF;
        }
    }

    printf("Enter roads (u v weight):\n");
    for (int i = 0; i < m; i++) {
        int u, v, w;
        scanf("%d %d %d", &u, &v, &w);
        graph[u][v] = w;
        graph[v][u] = w;
    }

    int choice;
    while (1) {
        printf("\n1. Shortest Path (Dijkstra)\n");
        printf("2. Traveling Salesman Problem (DP)\n");
        printf("3. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        if (choice == 1) {
            int src;
            printf("Enter source city: ");
            scanf("%d", &src);
            dijkstra(src);
        }
        else if (choice == 2) {
            memset(dp, -1, sizeof(dp));
            int result = tsp(1, 0);
            printf("\nMinimum cost to visit all cities: %d\n", result);
        }
        else {
            break;
        }
    }

    return 0;
}