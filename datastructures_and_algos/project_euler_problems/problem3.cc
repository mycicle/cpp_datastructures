// The prime factors of 13195 are 5, 7, 13 and 29.

// What is the largest prime factor of the number 600851475143 ?

#include <cmath>
#include <vector>
#include <iostream>
#include <memory.h>
using namespace std;

vector<long long int> eratosthenes(long long int length) {
    //use this to memoize the first million or so prime numbers 
    bool *primes = new bool[length];
    memset(primes, true, length*sizeof(bool));

    vector<long long int> primeVec;

    for (long long int i = 2; i < sqrt(length); i++) {
        if (primes[i]) {
            for (long long int j = pow(i, 2); j <= length; j+=i) {
                primes[j] = false;
            }
        }
    }

    for (long long int i = 0; i < length; i++) {
        if (primes[i]) {
            primeVec.push_back(i);
        }
    }

    return primeVec;
}

long long int largestPrimeFactor(long long int n, vector<long long int>& primes) {
    long long int largest = 1;
    while (n%2 == 0) {
        n = n / 2;
        largest = 2;
    }

    for (long long int i = 0; i < primes.size(); i++) {
        if (primes[i] > 2) {
            while((n%primes[i]) == 0) {
                n = n/primes[i];
                largest = primes[i];
            }
        } 
        // optimization to stop the loop when you reach the largest prime factor
        if (n < primes[i])
            break;    
    }

    if (largest == 1)
        largest = n;

    return largest;
}

int main() {
    long long int length = 1e4;
    long long int n = 600851475143;
    vector<long long int> primes = eratosthenes(length);
    long long int lpf = largestPrimeFactor(n, primes);
    cout << "The largest prime factor of " << n << " is " << lpf << endl;
}