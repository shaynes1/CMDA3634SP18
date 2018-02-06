#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void main() {

	int one;
	int two;

	printf("Enter the frist number:");
	scanf("%i", &one);

	printf("Enter the second number:");
	scanf("%i", &two);

	if (gcd(one,two) == 1) {

		printf("%i and %i are coprime.\n", one, two);
	}

	else {
	
		printf("%i and %i are not coprime.\n", one, two);
	}

}

int gcd(int a, int b) {

	if (b == 0) {

		return a;
	}
	
	else {

		return gcd(b, a%b);
	}
}


//This program shouldn't have a problem with large numbers since all it does is check to see if the gcd of the two
//numers is 1.
