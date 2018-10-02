
// Program to print all prime factors 
#include <stdio.h> 
#include <math.h> 
#include <stdlib.h>
#include <unistd.h>
#include <sys/time.h>
  
#define LIMIT 50

int primeFactorsArray[LIMIT][100];
int allFactorsArray[LIMIT][100];

void allFactors(int n, int* primeFactorsTemp, int* allFactorsTemp) {
    
}

void primeFactors(int n, int* primeFactorsTemp) {
    int currentPrimeFactor = 1;
    primeFactorsTemp[0] = 1;
    while (n%2 == 0) {
        primeFactorsTemp[currentPrimeFactor] = 2;
        currentPrimeFactor+= 1;
        n = n/2;
    }

    for (int i = 3; i <= sqrt(n); i = i+2) {
        while (n%i == 0) {
            primeFactorsTemp[currentPrimeFactor] = i;
            currentPrimeFactor+= 1;
            n = n/i;
        }
    }

    if (n > 2) {
        primeFactorsTemp[currentPrimeFactor] = n;
        currentPrimeFactor+= 1;
    }
}
  
/* Driver program to test above function */
int main() {
    long long start_ts;
	long long stop_ts;
	float elapsed_time;
	long lElapsedTime;
	struct timeval ts;
	
	gettimeofday(&ts, NULL);
	start_ts = ts.tv_sec * 1000000 + ts.tv_usec; // Tiempo inicial


    for(int i = 1; i< LIMIT; i++) {
        primeFactors(i,primeFactorsArray[i]);
    }

    for(int i = 0; i<LIMIT; i++){
        printf("Los divisores primos de %d son\n", i);
        for(int j = 0; j<20;j++) {
           if(primeFactorsArray[i][j]==0) {
                break;
            }
            printf("%d ",primeFactorsArray[i][j]);
        }
        printf("\n");
    }

    for(int i = 1; i < LIMIT-2; i++) {
        allFactors(i,primeFactorsArray[i],allFactorsArray[i]);
    }

	gettimeofday(&ts, NULL);
	stop_ts = ts.tv_sec * 1000000 + ts.tv_usec; // Tiempo final

	elapsed_time = (float) (stop_ts - start_ts)/1000000.0;
 
    printf("Encontré numeros amigos hasta %d en %1.2f segundos\n",LIMIT,elapsed_time);
    return 0;
}
