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

	printf("The greatest common divisor of %i and %i is %i.\n", one, two, gcd(one, two));
	
}

int gcd(int a, int b) {

	if (b == 0) {

		return a;
	}

	else {

		return gcd(b, a%b);
	}


}


//This program shouldn't lag with very large numbers since the mod operator is used. By using the mod
//operator only the numbers 0 through 9 will be left after the first recursive call. This limits the amount
//of work that the computer needs to do.
