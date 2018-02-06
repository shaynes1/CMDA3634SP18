#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void main() {

	int one;
	int count = 0;

	printf("Enter a number:");
	scanf("%i", &one);

	if (one == 0) {

		printf("%i is not prime.\n");
	}

	for (int i = 1; i <= one; i++) {

		if ( one%i == 0) {

			if (i != 1 &&  i != one) {

				count++;
				break;
			}
			
		}	
	}

	if (count > 0) {

		printf("%i is not prime.\n", one);
	}

	else {

		printf("%i is prime.\n", one);
	}
}

// When using very large itegers this code will work fine, since there is a break in the second if
// statment in the for loop. By having this break there, the for loop won't have to iterate all the way
// through the large number. It will end once it finds a factor that isn't 1 or the number being inputed.
// Thus, preventing the code from lagging.

