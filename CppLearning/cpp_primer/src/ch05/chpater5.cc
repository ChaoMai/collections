#include <iostream>
#include <vector>

using namespace std;

int main(int argc, char *argv[]) {
  vector<int> ivec(10);

  unsigned index = 0;
  switch (index) {
    case 1:
      // int ix = 1;
      int ix;
      ivec[ix] = index;
      break;
    default:
      ix = ivec.size() - 1;
      ivec[ix] = index;
  }
  return 0;
}
