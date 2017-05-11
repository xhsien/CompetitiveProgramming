#include <cstdio>
using namespace std;

/*
 * @param  f: pointer to function
 * @param x0: initial value for f
 *
 * @return 		 mu: first index for tortoise
 * @return	 lambda: length of cycle
 * @return tortoise: first number found to be within a cycle
 */
int floydCycleFinding(int (*f)(int), int x0) {
  int tortoise = f(x0), hare = f(f(x0));
  while (tortoise != hare)
  	tortoise = f(tortoise), hare = f(f(hare));

  int mu = 0; hare = x0;
  while (tortoise != hare)
  	tortoise = f(tortoise), hare = f(hare), mu++;
  
  int lambda = 1; hare = f(tortoise);
  while (tortoise != hare) 
  	hare = f(hare), lambda++; 
  
  return tortoise;
}

int main() {

	return 0;
}