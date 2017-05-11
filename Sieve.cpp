#include <vector>
using namespace std;

/*
 * @param upperBound: upper bound of prime
 *
 * @return prime[i] = i-th prime (0-indexed)
 * @return isPrime[i] check if i is a prime 
 */
void sieve(vector<int>& prime, vector<int>& isPrime, int upperBound) {
  isPrime.assign(upperBound + 1, 1);
  isPrime[0] = isPrime[1] = 0;
  for (int num = 2; num <= upperBound; num++) {
    if (isPrime[num]) {
      prime.push_back(num);
      for (int j = 2 * num; j <= upperBound; j += num) {
        isPrime[j] = 0;
      }
    }
  }
}

int main() {

  return 0;
}