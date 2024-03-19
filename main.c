#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <sys/types.h>
#include <netdb.h>
#include <string.h>
#include <inttypes.h>
#include <time.h>

#define MAX_RAND 1000000 //maximum random number 1,000,000

// Cole Blackman programming assignment #2 Intro to Cybersecurity

int main() {

    // Request user input the value of M

    printf("Enter message: ");

    char M[38];
    if (fgets(M, sizeof(M), stdin) == NULL) {
        printf("Invalid input");
        return 0; 
    }

    // Generate and print the values of p and q

    srand(time(NULL));
    // 
    uint32_t p = rand() % MAX_RAND;
    uint32_t q = rand() % MAX_RAND;

    printf("p = %d\n", p);
    printf("p = %d\n", q);

    // Generate the value of e
    uint32_t e = 65537;
    printf("e = %d\n", e);

    // Generate the value of d


    // Encrypt using RSA

    // Print the ciphertext C

    // Decrypt ciphertext C using RSA and print M'

    return 0;
}