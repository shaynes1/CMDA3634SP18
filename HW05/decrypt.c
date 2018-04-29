#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <time.h>

#include "functions.h"


int main (int argc, char **argv) {

  //declare storage for an ElGamal cryptosytem
  unsigned int n, p, g, h, x;
  unsigned int Nints;

  //get the secret key from the user
  printf("Enter the secret key (0 if unknown): "); fflush(stdout);
  char stat = scanf("%u",&x);

  printf("Reading file.\n");

  /* Q3 Complete this function. Read in the public key data from public_key.txt
    and the cyphertexts from messages.txt. */

  FILE *file1;
  if ((file1 = fopen("public_key.txt", "r")) == NULL) {
    printf("Error!\n");
    exit(1);
  }

  fscanf(file1, "%u\n", &n);
  fscanf(file1, "%u\n", &p);
  fscanf(file1, "%u\n", &g);
  fscanf(file1, "%u\n", &h);
  fclose(file1);

  FILE *file2;
  if ((file2 = fopen("message.txt", "r")) == NULL) {
    printf("Error!\n");
    exit(1);
  }

  fscanf(file2, "%u\n", &Nints);
  
  unsigned int count = 0;
  unsigned int *m = (unsigned int *) malloc(Nints*sizeof(unsigned int));
  unsigned int *a = (unsigned int *) malloc(Nints*sizeof(unsigned int));
  while (count < Nints) {
    fscanf(file2, "%u %u\n", &m[count], &a[count]);
    count = count + 1;
  }
  fclose(file2);
  
  // find the secret key
  if (x==0 || modExp(g,x,p)!=h) {
    printf("Finding the secret key...\n");
    double startTime = clock();
    for (unsigned int i=0;i<p-1;i++) {
      if (modExp(g,i+1,p)==h) {
        printf("Secret key found! x = %u \n", i+1);
        x=i+1;
      } 
    }
    double endTime = clock();

    double totalTime = (endTime-startTime)/CLOCKS_PER_SEC;
    double work = (double) p;
    double throughput = work/totalTime;

    printf("Searching all keys took %g seconds, throughput was %g values tested per second.\n", totalTime, throughput);
  }

  /* Q3 After finding the secret key, decrypt the message */
  
  ElGamalDecrypt(m, a, Nints, p, x);
  
  int bufferSize = 1024;
  unsigned char *message = (unsigned char *) malloc(bufferSize*sizeof(unsigned char));
  unsigned int charsPerInt = (int) ((n-1)/8);
  unsigned int Nchars = (Nints * charsPerInt);

  convertZToString(m, Nints, message, Nchars);
  printf("Decrypted Message = \"%s\"\n", message); 

  return 0;
}
