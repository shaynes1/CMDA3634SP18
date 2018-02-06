#include <stdio.h>
#include <stdlib.h>
#include <math.h>




void main() {

	int one;
	int count = 0;

	printf("Enter a prime number:");
	scanf("%i", &one);

	for (int i = 2; i <= (one-1); i++) {

		for (int j = 2; j <= (one-1); j++) {

			//int power = (int) pow(i,j);
			if ((int)pow(i,j)%one == 1 && j != (one-1)) {
				//printf("%i is a generator of Z_%i\n", i, one);
				count++;
				break;
			}
			
		}

		if (count == 0) {

			printf("%i is a generator of Z_%i\n", i, one);
			
		}
		count = 0;
	}
}


//This program might start to lag the higher the numbers get, because the intial number in the first for loop
//is taken to the power of the number of the second for loop. This migbht cause an overflow causing the program
// to not return every generator for the prime number chosen.
