#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void main() {

	int one;
	int two;

	printf("Enter the first number:");
	scanf("%i", &one);

	printf("Enter the second number:");
	scanf("%i", &two);

	printf("The least common multiple of %i and %i is %i.\n", one, two, lcm(one, two));

}

int lcm(int a, int b) {

	return (a*b)/gcd(a, b);
}

int gcd(int a, int b) {

	if (b ==0) {

		return a;
	}

	else {

		return gcd(b, a%b);
	}
}


//This program may have problems with large numbers since the two numbrs being inputed get multiplied
//together, then get divided by the gcd of the two numbers. I honestly don't think that there should be any
//lagging since the operations being done are rather simple, but I wouldn't be surprised if it did lag with very
//vey large numbers.
