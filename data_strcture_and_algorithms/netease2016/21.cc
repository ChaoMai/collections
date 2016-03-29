#include <algorithm>
#include <climits>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

using std::cout;
using std::endl;
using std::fstream;
using std::max;
using std::string;
using std::vector;

int DFSUtil(int x, int y, const vector<vector<int>>& m,
            vector<vector<int>>& dp);

int main() {
  fstream fs;
  fs.open("22_test.txt", fstream::in);

  int n;
  fs >> n;

  for (int i = 0; i < n; ++i) {
    int r, c;
    fs >> r >> c;
    vector<vector<int>> m(r, vector<int>(c, 0));

    // read each map
    for (int j = 0; j < r; ++j) {
      for (int k = 0; k < c; ++k) {
        fs >> m[j][k];
      }
    }

    // process each map
    vector<vector<int>> dp(r, vector<int>(c, 0));

    int maxSteps = INT_MIN;

    for (int j = 0; j < r; ++j) {
      for (int k = 0; k < c; ++k) {
        dp[j][k] = DFSUtil(j, k, m, dp);
        if (dp[j][k] > maxSteps) {
          maxSteps = dp[j][k];
        }
      }
    }

    cout << maxSteps << endl;
  }
  return 0;
}

int DFSUtil(int x, int y, const vector<vector<int>>& m,
            vector<vector<int>>& dp) {
  if (dp[x][y] != 0) {
    return dp[x][y];
  }

  dp[x][y] = 1;
  // check and move to four directions
  vector<vector<int>> direct{{0, 1}, {0, -1}, {-1, 0}, {1, 0}};
  for (int i = 0; i < 4; ++i) {
    int nx = x + direct[i][0];
    int ny = y + direct[i][1];

    if (nx >= 0 && nx < dp.size() && ny >= 0 && ny < dp.size() &&
        m[nx][ny] < m[x][y]) {
      dp[x][y] = max(DFSUtil(nx, ny, m, dp) + 1, dp[x][y]);
    }
  }

  return dp[x][y];
}
