#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <time.h>

#include "cuda.h"
#include "functions.c"

__device__ unsigned int CUDAmodProd(unsigned int a, unsigned int b, unsigned int p) {
  unsigned int za = a;
  unsigned int ab = 0;
  while(b > 0) {
    if (b%2 == 1) ab = (ab+za)%p;
    za = (2*za)%p;
    b /= 2;
  }
  return ab;
}

__device__ unsigned int CUDAmodExp(unsigned int a, unsigned int b, unsigned int p) {
  unsigned int z = a;
  unsigned int aExpb = 1;
  while(b > 0) {
    if (b%2==1) aExpb = CUDAmodProd(aExpb, z, p);
    z = CUDAmodProd(z, z, p);
    b /= 2;
  }
  return aExpb;
}

__global__ kernelFindKey(volatile unsigned int *secretKey, unsigned int p, unsigned int g, unsigned int h){
  
  int threadID = threadIdx.x;
  int blockID = blockIdx.x
  int Nblock = blockDim.x;

  unsigned int ID = threadID + blockID*Nblock;
  secretKey[ID+1] = 0;

  if ((ID < p) && CUDAmodExp(g, ID+1, p) == h) {
    
    secretKey[ID+1] = ID+1;
    printf("Secret Key Found %d %d %d\n", ID+1, secretKey[ID+1], secretKey[ID]);
  }

}

int main (int argc, char **argv) {

  /* Part 2. Start this program by first copying the contents of the main function from 
     your completed decrypt.c main function. */

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
  

  double start = clock();
  unsigned int *secretKey;
  cudaMalloc(&secretKey, (p-1)*sizeof(unsigned int));
  int Nthreads = 128;
  int Nblocks = (p+Nthreads-1)/Nthreads;
  kernelFindKey <<<Nblocks, Nthreads>>> (secretKey, p, g, h);
  cudaDeviceSynchronize();
  unsigned int *final = (unsigned int*) malloc((p-1)*sizeof(unsigned int));
  cudaMemcpy(final, secretKey, (p-1)*sizeof(unsigned int), cudaMemcpyDeviceToHost);
  
  int w = 0;
  while (w < p) {
    if (final[w] != 0) {
      x = final[w];
      break;
    }
    w++;
  }

  printf("The secret key is %d\n", x);
  double end = clock();
  double total = (end-start)/CLOCKS_PER_SEC;
  double cudawork = (double) p;
  double cudathroughput = cudawork/total;

  printf("Searching all keys with cuda took %g seconds, throughput was %g values tested per second.\n", total, cudathroughput);

  /* Q3 After finding the secret key, decrypt the message */

  ElGamalDecrypt(m, a, Nints, p, x);

  int bufferSize = 1024;
  unsigned char *message = (unsigned char *) malloc(bufferSize*sizeof(unsigned char));
  unsigned int charsPerInt = (int) ((n-1)/8);
  unsigned int Nchars = (Nints * charsPerInt);

  convertZToString(m, Nints, message, Nchars);
  printf("Decrypted Message = \"%s\"\n", message);
  

  /* Q4 Make the search for the secret key parallel on the GPU using CUDA. */
  
  return 0;
} 
