#include <stdio.h>

long long calls = 0; /* number of recursive calls made */

/* Linear recursion: base^exp = base * base^(exp-1) */
long long power_linear(long long base, int exp)
{
    calls++;
    if (exp == 0) return 1;
    return base * power_linear(base, exp - 1);
}

/* Divide-and-conquer recursion: compute base^(exp/2) once and square it */
long long power_fast(long long base, int exp)
{
    calls++;
    /* TODO 1: Write the base case for exp == 0; otherwise compute half =
       power_fast(base, exp / 2) ONCE and return half * half, multiplied by base when
       exp is odd */
    if (exp == 0) return 1;

    long long half = power_fast(base, exp / 2);
    if (exp % 2 == 0) {
        return half * half;
    } else {
        return base * half * half;
    }
}

/* Digital root computation for check digits */
int digital_root(long long n) {
    if (n < 10) return (int)n;
    long long sum = 0;
    while (n > 0) {
        sum += (n % 10);
        n /= 10;
    }
    return digital_root(sum);
}

int main(void)
{
    printf("=== Blood Bank Exponentiation Benchmark ===\n");
    calls = 0;
    long long a = power_linear(2, 30);
    printf("linear: %lld in %lld calls\n", a, calls);

    calls = 0;
    long long b = power_fast(2, 30);
    printf("fast  : %lld in %lld calls\n", b, calls);

    printf("\n=== Check Digit Verification ===\n");
    long long donor_id = 987543;
    printf("Donor ID %lld -> Digital Root Check Digit: %d\n", donor_id, digital_root(donor_id));

    return 0;
}