// Program to print all prime factors 
#include <stdio.h> 
#include <math.h> 
#include <stdlib.h>
#include <unistd.h>
#include <sys/time.h>
#include <stdbool.h>
  
#define LIMIT 20000
#define LIMITPRIME 20000

int numberOfPrimes[LIMIT];
int primeFactorsArray[LIMIT][200];
bool allFactorsArray[LIMIT][LIMITPRIME];
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

int getSumOfArray(bool* allFactorsBranch, int size) {
    int i;
    int total = 0;
    for(i = 0; i < size; i++) {
	if(allFactorsBranch[i])
        	total += i; 
    }
    return total;
}

void allFactors(int n, int* primeFactorsBranch, bool* allFactorsBranch) {
    for(int i=0; i<LIMITPRIME; i++)
	allFactorsBranch[i]=false;
    int numberOfPrimeF = numberOfPrimes[n];
    int factorIndex=0;
    int pow2 = (1<<numberOfPrimeF)-1;
    int factor=1;
    for(int i=1; i<=pow2;i++)
    {
        factor=1;
        for(int j=1;j<numberOfPrimeF; j++)
        {
            //si el j-esimo bit de i esta prendido, multiplicar el j-esimo elemento por factor
            if(i&(1<<j)){
                factor*=primeFactorsBranch[j];
            }
        }
        allFactorsBranch[factor] = true;
        factorIndex++;
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

int primeFactors(int n, int* primeFactorsBranch) {
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
    return currentPrimeFactor;
}
  
void info(int n)
{
    printf("\n---------------------------------------------------\n");
    printf("printing all factors of %d, it has %d prime factors: ",n , numberOfPrimes[n]);
    for(int i = 1; i< n; i++) {
        if(allFactorsArray[n][i])
	    printf("%d ", i);
    }
    printf("\n The sum of the factos of n is %d",  sumOfFactorsArray[n]);
    printf("\n---------------------------------------------------\n");
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
	numberOfPrimes[i] = primeFactors(i,primeFactorsArray[i]);
    }

    for(int i = 1; i < LIMIT; i++) {
        allFactors(i,primeFactorsArray[i],allFactorsArray[i]);
    }

    for(int i = 1; i< LIMIT; i++) {
        sumOfFactorsArray[i] = getSumOfArray(allFactorsArray[i], i);
    }

 //   info(17296);
 //   info(18416);

    printIfFriends(sumOfFactorsArray);

	gettimeofday(&ts, NULL);
	stop_ts = ts.tv_sec * 1000000 + ts.tv_usec; // Tiempo final

	elapsed_time = (float) (stop_ts - start_ts)/1000000.0;
 
    printf("Encontré los numeros amigos que existen hasta %d en %1.2f segundos\n",LIMIT,elapsed_time);
    return 0;
}
