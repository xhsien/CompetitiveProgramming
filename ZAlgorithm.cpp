#include <iostream>
using namespace std;

/*
 * @param str[]: string to be analyzed
 * @param   len: length of string
 * @param   z[]: storage for z-values of each index
 *
 * @return z[i] now stores the longest prefix of str starting from str[i]
 */
void ZAlgorithm(char str[], int len, int z[]) {
  for (int i = 0; i < len; i++)
    z[i] = 0;

  int L = 0, R = 1; z[0] = len;
  for (int idx = 1; idx < len; idx++) {
    if (idx < R) {
      int est = z[idx - L];
      if (idx + est < R) {
        z[idx] = est;
      } else {
        z[L = idx] = min(est, R - idx);
        while (str[R] == str[R - idx])
          z[idx]++, R++;
      }
    } else {
      L = R = idx;
      while (str[R] == str[R - idx])
        z[idx]++, R++;
    }
  }
}

int main() {

	return 0;
}
