#include <climits>
#include <iostream>
#include <vector>

using namespace std;

vector<bool> flag(200);

int min(int a, int b) {
  if (a < b) {
    return a;
  } else {
    return b;
  }
}

void FixedSum(vector<int>& a, int t, int sum, int& cur_max) {
  if (sum <= 0) {
    int tmp = 0;

    for (int i = 0; i < a.size(); ++i) {
      if (flag[i]) {
        tmp += a[i];
      }
    }

    if (tmp >= sum) {
      cur_max = min(cur_max, tmp);
    }
  } else {
    if (t == a.size()) {
      return;
    } else {
      flag[t] = true;
      FixedSum(a, t + 1, sum - a[t], cur_max);

      flag[t] = false;
      FixedSum(a, t + 1, sum, cur_max);
    }
  }
}

int main() {
  int n, x;
  cin >> n >> x;

  vector<int> a;
  int check_sum = 0;

  for (int i = 0; i < n; ++i) {
    int tmp;
    cin >> tmp;
    a.push_back(tmp);

    check_sum += tmp;
  }

  if (check_sum < x) {
    cout << -1 << endl;
  } else {
    int cur_max = INT_MAX;
    FixedSum(a, 0, x, cur_max);
    cout << cur_max << endl;
  }
}
