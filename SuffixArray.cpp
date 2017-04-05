#include <bits/stdc++.h>
using namespace std;

void countingSort(int len, int ra[], int sa[], vector<int>& tsa, int k) {
  vector<int> c; c.assign(len, 0);
  int maxChar = max(300, len);
  for (int i = 0; i < len; i++)
    c[i + k < len ? ra[i + k] : 0]++;
  for (int i = 0, sum = 0; i < maxChar; i++)
    sum += c[i], c[i] = sum - c[i];
  for (int i = 0; i < len; i++)
    tsa[c[sa[i] + k < len ? ra[sa[i] + k] : 0]++] = sa[i];
  for (int i = 0; i < len; i++)
    sa[i] = tsa[i];
}

void SuffixArray(char str[], int len, int ra[], int sa[]) {
  vector<int> tra; tra.assign(len, 0);
  vector<int> tsa; tsa.assign(len, 0);
  for (int i = 0; i < len; i++)
    ra[i] = str[i], sa[i] = i;
  for (int k = 1, r; k < len; k <<= 1) {
    countingSort(len, ra, sa, tsa, k);
    countingSort(len, ra, sa, tsa, 0);
    tra[sa[0]] = r = 0;
    for (int i = 1; i < len; i++)
      tra[sa[i]] = (ra[sa[i]] == ra[sa[i-1]] && ra[sa[i] + k] == ra[sa[i-1] + k]) ? r : ++r;
    for (int i = 0; i < len; i++)
      ra[i] = tra[i];
    if (ra[sa[len - 1]] == len - 1)
      break;
  }
}

int main() {

  return 0;
}
