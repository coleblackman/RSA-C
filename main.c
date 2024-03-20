#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <sys/types.h>
#include <netdb.h>
#include <string.h>
#include <inttypes.h>
#include <time.h>
#include <math.h>

#define MAX_RAND 78498 //maximum random number 

#include "main.h"

// Cole Blackman programming assignment #2 Intro to Cybersecurity
// Reference: https://en.wikipedia.org/wiki/RSA_(cryptosystem)

int main() {

    // Request user input the value of M
    printf("Enter message: ");

    char m[38];
    if (fgets(m, sizeof(m), stdin) == NULL) {
        printf("Invalid input");
        return 0; 
    }

    // Generate and print the values of p and q

    srand(time(NULL)); // initalize

    // These need to be primes
    uint32_t p_index = rand() % MAX_RAND; 
    uint32_t q_index = rand() % MAX_RAND;
    printf("p_index: %d\n", p_index);
    printf("q_index: %d\n", q_index);

    uint32_t p = getPrime(p_index);
    uint32_t q = getPrime(q_index);

    printf("p = %d\n", p);
    printf("q = %d\n", q);

    // Generate the value of e
    uint32_t e = 3;
    printf("e = %d\n", e);
    // Generate the modulus n
    uint32_t n = p * q; 
    // Generate λ() = lcm(p-1,q-1) = |(p-1)(q-1)|/gcd((p-1)(q-1))
    uint32_t lambdaN = (p-1)*(q-1) / gcd(p-1, q-1);
    // Generate the value of d
    uint32_t d = mul_inv(e, lambdaN);
    printf("d = %d\n", d);
    // Encrypt using RSA
    int* encrypted = encrypt(n, e, m);
    // Print the ciphertext C
    for (int i = 0; i < sizeof(encrypted)/sizeof(int); i++) {
        printf("[%d]", encrypted[i]);
    }
    puts("");
    // Decrypt ciphertext C using RSA and print M'
    decrypt(encrypted, n, d);
    free(encrypted);
    return 0;
}
int gcd(int a, int b) {
    int rem = a % b;

    if (rem == 0)
        return b;

    return gcd(b, rem);
}
int mul_inv(int a, int b)
{
    //https://rosettacode.org/wiki/Modular_inverse
	int b0 = b, t, q;
	int x0 = 0, x1 = 1;
	if (b == 1) return 1;
	while (a > 1) {
		q = a / b;
		t = b, b = a % b, a = t;
		t = x0, x0 = x1 - q * x0, x1 = t;
	}
	if (x1 < 0) x1 += b0;
	return x1;
}
uint32_t getPrime (uint32_t index) {
    // I generated a list of all primes below 10^6 in R
    // K&R C page 162

    char prime_list [] = "primes";
    FILE *fp;
    if ((fp = fopen(prime_list, "r")) == NULL) {
        printf("Cannot open primes");
        return 1;
    }
    char line[32];
    int iter = 0;
    while (fgets(line, sizeof(line), fp) != NULL) {
        iter++;
        if (iter == index)
            return atoi(line);
    }
    fclose(fp);
}

int* encrypt(uint32_t n, uint32_t e, char* m) {
    printf("Call to encrypt with m[0] = %d, m[1] = %d\n", m[0], m[1]);
    int * encrypted = (int*)malloc(strlen(m)*sizeof(int)); // allocate memory so it doesn't go out of scope
    for (int i = 0; i < strlen(m); i++) {
        printf("First element: m[i] = %d, m[i]^e = %d\n", m[i], (int)pow((int)m[i], e));
        encrypted[i] = (int)pow((int)m[i], e) % n;
    }
    return encrypted;
}
void decrypt(int* encrypted, uint32_t n, uint32_t d) {
    // TODO decrypt
    // TODO print out decrypted message with printf
}
