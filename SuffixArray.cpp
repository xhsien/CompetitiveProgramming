#include <bits/stdc++.h>
using namespace std;

const int _MAXN = 100000;

/*
 * t : string input
 * n : length of string t
 * 
 * t must be appended with '$' or ' '
 */
char T[_MAXN]; int _N;

/*
 * ra : rank array
 * sa : suffix array
 */
int RA[_MAXN], SA[_MAXN];

/*
 * helper arrays
 */
int tempRA[_MAXN], tempSA[_MAXN],  c[_MAXN];

bool cmp(int i, int j) { 
	return strcmp(T + i, T + j) < 0; 
}

void countingSort(int k) {
  int maxChar = max(300, _N);
  memset(c, 0, sizeof c);
  for (int i = 0; i < _N; i++)
  	c[i + k < _N ? RA[i + k] : 0]++;
  for (int i = 0, sum = 0; i < maxChar; i++)
    sum += c[i], c[i] = sum - c[i];
  for (int i = 0; i < _N; i++)
    tempSA[c[SA[i]+k < _N ? RA[SA[i]+k] : 0]++] = SA[i];
  for (int i = 0; i < _N; i++)
    SA[i] = tempSA[i];
}

void constructSA() {
  for (int i = 0; i < _N; i++)
  	RA[i] = T[i];
  for (int i = 0; i < _N; i++)
  	SA[i] = i;
  for (int k = 1, r; k < _N; k <<= 1) {
    countingSort(k);
    countingSort(0);
    tempRA[SA[0]] = r = 0;
    for (int i = 1; i < _N; i++)
      tempRA[SA[i]] = (RA[SA[i]] == RA[SA[i-1]] && RA[SA[i]+k] == RA[SA[i-1]+k]) ? r : ++r;
    for (int i = 0; i < _N; i++)
      RA[i] = tempRA[i];
    if (RA[SA[_N-1]] == _N - 1)
    	break;
  }
}

int main() {

	return 0;
}
