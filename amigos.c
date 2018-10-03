// Program to print all prime factors 
#include <stdio.h> 
#include <math.h> 
#include <stdlib.h>
#include <unistd.h>
#include <sys/time.h>
  
#define LIMIT 20000

int primeFactorsArray[LIMIT][200];
int allFactorsArray[LIMIT][200];
int allFactorsArrayLength[LIMIT];
int sumOfFactorsArray[LIMIT];

/**
* Elimina los primos repetidos
*/
int removeDuplicates(int n, int *allFactorsBranch) {
    int i, j;
    int newLength = 1;
    for (i = 1; allFactorsBranch[i] != 0; i++) {
        for(j= 0; j< newLength ; j++) {
            if(allFactorsBranch[i] == allFactorsBranch[j]) {
                break;
            }
        }
        if(j==newLength) {
            allFactorsBranch[newLength++] = allFactorsBranch[i];
        }
    }

    return newLength;
}

int getSumOfArray(int* allFactorsBranch, int size) {
    int i;
    int total = 0;
    for(i = 0; i < size; i++) {
        total += allFactorsBranch[i]; 
    }

    return total;
}

void allFactors(int n, int* primeFactorsBranch, int* allFactorsBranch) {
    int currentAllFactor = 0;
    int tempAllFactor = 1;
    int i, j, k, z = 0;

    
    for(i = 0; primeFactorsBranch[i] > 0 && primeFactorsBranch[i] != n; i++) {
            allFactorsBranch[currentAllFactor] = primeFactorsBranch[i];
            currentAllFactor++;
    }

    int totalPrimes = currentAllFactor;

    for(i = 1; primeFactorsBranch[i] > 0; i++) {
        for(k = 1; k < 100; k++) {
            tempAllFactor = primeFactorsBranch[i];
            for(j = k; primeFactorsBranch[j] > 0; j++) {
                if(i!=j) {
                    tempAllFactor = tempAllFactor * primeFactorsBranch[j];
                    if(tempAllFactor!=n) {
                        allFactorsBranch[currentAllFactor] = tempAllFactor;
                        currentAllFactor++;
                    }
                }
            }
        }
    }
}

void printIfFriends(int* sumoOfFactors) {
    int i, j;
    for(i = 0; i < LIMIT; i++) {
        for(j = i+1; j < LIMIT; j++) {
            if(sumoOfFactors[i]==j && sumoOfFactors[j]==i && i!=j) {
                printf("%d y %d son numeros amigos\n",i,j);
            }
        }
    }
}

void primeFactors(int n, int* primeFactorsBranch) {
    int currentPrimeFactor = 1;
    primeFactorsBranch[0] = 1;
    while (n%2 == 0) {
        primeFactorsBranch[currentPrimeFactor] = 2;
        currentPrimeFactor+= 1;
        n = n/2;
    }

    for (int i = 3; i <= sqrt(n); i = i+2) {
        while (n%i == 0) {
            primeFactorsBranch[currentPrimeFactor] = i;
            currentPrimeFactor+= 1;
            n = n/i;
        }
    }

    if (n > 2) {
        primeFactorsBranch[currentPrimeFactor] = n;
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

    for(int i = 1; i< LIMIT; i++) {
        sumOfFactorsArray[i] = getSumOfArray(allFactorsArray[i],allFactorsArrayLength[i]);
    }

    printIfFriends(sumOfFactorsArray);

	gettimeofday(&ts, NULL);
	stop_ts = ts.tv_sec * 1000000 + ts.tv_usec; // Tiempo final

	elapsed_time = (float) (stop_ts - start_ts)/1000000.0;
 
    printf("Encontré los numeros amigos que existen hasta %d en %1.2f segundos\n",LIMIT,elapsed_time);
    return 0;
}
