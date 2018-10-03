// Program to print all prime factors 
#include <stdio.h> 
#include <math.h> 
#include <stdlib.h>
#include <unistd.h>
#include <sys/time.h>
  
#define LIMIT 222

int primeFactorsArray[LIMIT][200];
int allFactorsArray[LIMIT][200];
int allFactorsArrayLength[LIMIT];

int removeDuplicates(int n, int *allFactorsTemp) {
    int i, j;
    int newLength = 1;
    for (i = 1; allFactorsTemp[i] != 0; i++) {
        for(j= 0; j< newLength ; j++) {
            if(allFactorsTemp[i] == allFactorsTemp[j]) {
                break;
            }
        }
    
        if(j==newLength) {
            allFactorsTemp[newLength++] = allFactorsTemp[i];
        }
    }

    return newLength;
}

void allFactors(int n, int* primeFactorsTemp, int* allFactorsTemp) {
    int currentAllFactor = 0;
    int tempAllFactor = 1;
    int i, j = 0;
    for(i = 0; primeFactorsTemp[i] > 0 && primeFactorsTemp[i] != n; i++){
            allFactorsTemp[currentAllFactor] = primeFactorsTemp[i];
            currentAllFactor++;
    }

    for(i = 1; primeFactorsTemp[i] > 0 && primeFactorsTemp[i] != n; i++){
        tempAllFactor = primeFactorsTemp[i];
        for(j = i+1; primeFactorsTemp[j] > 0 && tempAllFactor != n; j++) {
            tempAllFactor = tempAllFactor * primeFactorsTemp[j];
            if(tempAllFactor!=n) {
                allFactorsTemp[currentAllFactor] = tempAllFactor;
                currentAllFactor++;
            }
        }
    }

    for(i = 50; i > 0 ; i--){
        tempAllFactor = primeFactorsTemp[i];
        
        for(j = 0; j < i && allFactorsTemp[i] > 0; j++) {
            tempAllFactor = tempAllFactor * primeFactorsTemp[j];
            if(tempAllFactor!=n && tempAllFactor!= 0) {
                allFactorsTemp[currentAllFactor] = tempAllFactor;
                currentAllFactor++;
            }
        }
    }
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

    for(int i = 1; i < LIMIT; i++) {
        allFactors(i,primeFactorsArray[i],allFactorsArray[i]);
    }

    for(int i = 1; i< LIMIT; i++) {
        allFactorsArrayLength[i] = removeDuplicates(i,allFactorsArray[i]);
    }

    for(int i = 0; i<LIMIT; i++){
        printf("Los divisores propios de %d son\n", i);
        for(int j = 0; j < allFactorsArrayLength[i];j++) {
            printf("%d ",allFactorsArray[i][j]);
        }
        printf("\n");
    }

	gettimeofday(&ts, NULL);
	stop_ts = ts.tv_sec * 1000000 + ts.tv_usec; // Tiempo final

	elapsed_time = (float) (stop_ts - start_ts)/1000000.0;
 
    printf("Encontré los numeros amigos que existen hasta %d en %1.2f segundos\n",LIMIT,elapsed_time);
    return 0;
}
