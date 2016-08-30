#include <iostream>
using namespace std;
const int max_n = 65535;

typedef struct graph {
  int vex[3000];
  int weight[3000][3000];
  int cost[3000][3000];
  int numvex, numedge;
} graph;

void create(graph *&g) {
  int n, m;
  cin >> n >> m;

  g->numvex = n * m;
  g->numedge = ((n - 1) * m) + (n * (m - 1));

  for (int i = 0; i < g->numvex; i++) {
    for (int j = 1; j <= g->numvex; j++) {
      g->weight[i][j] = max_n;
      g->cost[i][j] = max_n;
    }
  }

  for (int i = 0; i < n - 1; ++i) {
    int tmp;
    cin >> tmp;

    for (int j = 0; j < m; ++j) {
      g->weight[m * i + j][m * i + m + j] = tmp;
      g->cost[m * i + j][m * i + m + j] = 1;
      g->weight[m * i + m + j][m * i + j] = g->weight[m * i + j][m * i + m + j];
      g->cost[m * i + m + j][m * i + j] = g->cost[m * i + j][m * i + m + j];
    }
  }

  for (int i = 0; i < m - 1; ++i) {
    int tmp;
    cin >> tmp;

    for (int j = 0; j < n; ++j) {
      g->weight[i + m * j][i + m * j + 1] = tmp;
      g->cost[i + m * j][i + m * j + 1] = 1;
      g->weight[i + m * j + 1][i + m * j] = g->weight[i + m * j][i + m * j + 1];
      g->cost[i + m * j + 1][i + m * j] = g->cost[i + m * j][i + m * j + 1];
    }
  }

  int d;
  cin >> d;

  for (int i = 0; i < d; ++i) {
    int a, b;
    cin >> a >> b;

    if (a * b - 1 + 1 >= 0) {
      g->weight[a * b - 1][a * b - 1 + 1] = max_n;
      g->weight[a * b - 1 + 1][a * b - 1] = max_n;
    }

    if (a * b - 1 - 1 >= 0) {
      g->weight[a * b - 1 - 1][a * b - 1] = max_n;
      g->weight[a * b - 1][a * b - 1 - 1] = max_n;
    }

    if (a *)
      if (a * b >= 0) {
        g->weight[a * b - 1][a * b] = max_n;
        g->weight[a * b][a * b - 1] = max_n;
      }
  }
}

void mydijkstra(graph *&g, int start, int end) {
  int mark1[1000], mark2[1000];
  int dist1[1000], dist2[1000];
  int i, j, k1, k2, min1, min2;
  for (i = 1; i <= g->numvex; i++) {
    dist1[i] = max_n;
    dist2[i] = max_n;
  }
  for (i = 1; i <= g->numvex; i++) {
    mark1[i] = 0;
    mark2[i] = 0;
    dist1[i] = g->weight[start][i];
    dist2[i] = g->cost[start][i];
  }
  mark1[start] = 1;
  mark2[start] = 1;
  dist1[start] = max_n;
  dist2[start] = max_n;
  for (i = 1; i < g->numvex; i++) {
    min1 = max_n;
    min2 = max_n;
    j = 1;
    while (j <= g->numvex) {
      if (!mark1[j] && dist1[j] < min1) {
        min1 = dist1[j];
        k1 = j;
      }
      if (!mark2[j] && dist2[j] < min2) {
        min2 = dist2[j];
        k2 = j;
      }
      j++;
    }
    mark1[k1] = 1;
    dist1[k1] = min1;
    mark2[k2] = 1;
    dist2[k2] = min2;
    for (j = 1; j <= g->numvex; j++) {
      if (!mark1[j] && dist1[j] > dist1[k1] + g->weight[k1][j])
        dist1[j] = dist1[k1] + g->weight[k1][j];
      if (!mark2[j] && dist2[j] > dist2[k2] + g->cost[k2][j])
        dist2[j] = dist2[k2] + g->cost[k2][j];
    }
  }
  cout << dist1[end] << endl;
}

int main() {
  graph *g = new graph;
  create(g);

  // int start, end;
  // cin >> start >> end;

  // if (start == 0 & end == 0) return 0;

  // mydijkstra(g, start, end);

  return 0;
}
