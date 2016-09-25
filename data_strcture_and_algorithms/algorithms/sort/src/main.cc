#include <iostream>
#include <limits>

using namespace std;

template <typename RandomIt>
void print(RandomIt first, RandomIt last) {
  for (auto it = first; it != last; ++it) {
    cout << *it << " ";
  }
  cout << endl;
}

template <unsigned SIZE>
void bubble_sort(int (&arr)[SIZE]) {
  int len = SIZE;

  for (int i = 0; i != len; ++i) {
    for (int j = 0; j + 1 != len - 1; ++j) {
      if (arr[j] > arr[j + 1]) {
        swap(arr[j], arr[j + 1]);
      }
    }
  }
}

template <unsigned SIZE>
void bubble_sort2(int (&arr)[SIZE]) {
  int len = SIZE;

  for (int i = 0; i != len; ++i) {
    bool is_swaped = false;

    for (int j = 0; j != len - i - 1; ++j) {
      if (arr[j] > arr[j + 1]) {
        is_swaped = true;
        swap(arr[j], arr[j + 1]);
      }
    }

    if (!is_swaped) {
      break;
    }
  }
}

template <unsigned SIZE>
void selection_sort(int (&arr)[SIZE]) {
  int len = SIZE;

  for (int i = 0; i != len; ++i) {
    int min_elem_index = i;
    int min_elem = arr[i];

    for (int j = i; j != len; ++j) {
      if (arr[j] < min_elem) {
        min_elem_index = j;
        min_elem = arr[j];
      }
    }

    swap(arr[i], arr[min_elem_index]);
  }
}

template <unsigned SIZE>
void insertion_sort(int (&arr)[SIZE]) {
  int len = SIZE;

  for (int i = 0; i != len; ++i) {
    for (int j = i; j != 0 && arr[j] < arr[j - 1]; --j) {
      swap(arr[j], arr[j - 1]);
    }
  }
}

template <unsigned SIZE>
void insertion_sort2(int (&arr)[SIZE]) {
  int len = SIZE;

  for (int i = 0; i != len; ++i) {
    int tmp = arr[i];
    int j;

    for (j = i; j != 0 && tmp < arr[j - 1]; --j) {
      arr[j] = arr[j - 1];
    }

    arr[j] = tmp;
  }
}

template <unsigned SIZE>
void merge_sort(int (&arr)[SIZE]) {
  int len = SIZE;

  m_sort(arr, 0, len - 1);
}

// [l, m] [m+1, n]
template <unsigned SIZE>
void m_sort(int (&arr)[SIZE], int m, int n) {
  if (n > m) {
    // int mid = (m + n) / 2;
    int mid = m + (n - m) / 2;
    m_sort(arr, m, mid);
    m_sort(arr, mid + 1, n);
    m_merge(arr, m, mid, mid + 1, n);
  }
}

template <unsigned SIZE>
void m_merge(int (&arr)[SIZE], int m, int n, int p, int q) {
  int* n_arr = new int[SIZE];

  int a = m;
  int b = p;
  int i = 0;

  while (a <= m && b <= q) {
    if (arr[a] > arr[b]) {
      n_arr[i] = arr[b];
      ++b;
    } else {
      n_arr[i] = arr[a];
      ++a;
    }

    ++i;
  }

  while (a < m) {
    n_arr[i] = arr[a];
    ++i;
  }

  while (b < q) {
  }
}

int main() {
  int arr[] = {6, 5, 3, 1, 8, 7, 2, 4, 4, 2, 1, 4, 6, 4, 3, 7};
  // int arr[] = {9, 8, 7, 6, 5, 4, 3, 2, 1, 0};

  // bubble_sort(arr);
  // bubble_sort2(arr);
  // selection_sort(arr);
  // insertion_sort(arr);
  insertion_sort2(arr);

  print(begin(arr), end(arr));
  return 0;
}
