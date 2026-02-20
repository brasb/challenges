#include <limits.h>
#include <stdbool.h>
#include <stdio.h>

// 1) Multiply two natural numbers (a, b), a, b ∈ ℕ
// 2) Return the biggest element in a list
// 3) Return if a given element is part of a list
// 4) Return if a number is prime
// 5) Return the GCD of a and b; a, b ∈ ℕ
// Hard mode: use tail-cail recursion for all of them
// 1 --------------------------------------------------------------
// Assumes a, b > 0
int aux_mult(int a, int b, int acc)
{
    if (b == 1) {
        return acc;
    }

    return aux_mult(a, b - 1, acc + a);
}

int mult(int a, int b)
{
    if (a == 0 || b == 0) {
        return 0;
    }

    return aux_mult(a, b, a);
}

// 2 -------------------------------------
int aux_return_biggest_elem(int *list, int len, int max)
{
    if (len == 0) {
        return max;
    }

    return aux_return_biggest_elem(
        list + 1, len - 1, *list > max ? *list : max);
}

int return_biggest_elem(int *list, int len)
{
    return aux_return_biggest_elem(list + 1, len - 1, list[0]);
}

// 3 --------------------------------------------------------------
bool is_part_of_list(int *list, int len, int n)
{
    if (len == 0) {
        return false;
    }

    return *list == n ? true : is_part_of_list(list + 1, len - 1, n);
}

bool aux_is_prime(int x, int i)
{
    if (i == 1) {
        return true;
    }

    if (x % i == 0) {
        return false;
    }

    return aux_is_prime(x, i - 1);
}

bool is_prime(int x)
{
    if (x <= 1) {
        return false;
    }

    return aux_is_prime(x, x - 1);
}

// --------------------------------------------------
// 4. Binary GCD Algorithm (Stein's Algorithm)
// Divides x by 2 until it's odd
int find_odd(int x) { return x % 2 != 0 ? x : find_odd(x >> 1); }

// 1. If both are 0, return 0
// 2. If one is 0, return the non-zero
// 3. If both are even, divide both by 2
// 4. If one number is even and the other is odd, divide the even one by 2
// 5. If both are odd, substract the small one from the larger one
// Repeat 3-5 until one is 0, the non-zero is the GCD
int get_gcd(int a, int b)
{
    if (a == 0 && b == 0) {
        return 0;
    }

    if (a == 0 && b != 0) {
        return b;
    }

    if (b == 0 && a != 0) {
        return a;
    }

    a = find_odd(a);
    b = find_odd(b);

    if (a > b) {
        a -= b;
    } else {
        b -= a;
    }

    return get_gcd(a, b);
}

int main()
{
#define NUMBER_COUNT 7
    int numbers[] = { 0, 25, 1, 8, 24, 1, 4 };

    printf("1) 5 * 4 = %d\n", mult(5, 4));
    printf("1) 0 * 4 = %d\n", mult(0, 4));
    printf("1) 5 * 0 = %d\n", mult(5, 0));
    printf("1) 1 * 4 = %d\n", mult(1, 4));
    printf("1) 5 * 1 = %d\n", mult(5, 1));

    printf("2) %d\n", return_biggest_elem(numbers, NUMBER_COUNT));
    printf("2) %d\n", return_biggest_elem(numbers, NUMBER_COUNT));

    printf("3) 0? %d\n", is_part_of_list(numbers, NUMBER_COUNT, 0));
    printf("3) 4? %d\n", is_part_of_list(numbers, NUMBER_COUNT, 4));
    printf("3) 24? %d\n", is_part_of_list(numbers, NUMBER_COUNT, 24));
    printf("3) 99? %d\n", is_part_of_list(numbers, NUMBER_COUNT, 99));

    printf("4) 1? %d\n", is_prime(1));
    printf("4) 2? %d\n", is_prime(2));
    printf("4) 3? %d\n", is_prime(3));
    printf("4) 5? %d\n", is_prime(5));
    printf("4) 12? %d\n", is_prime(12));
    printf("4) 27? %d\n", is_prime(27));
    printf("4) 7? %d\n", is_prime(7));

    printf("5) 12, 36? %d\n", get_gcd(12, 36));
    printf("5) 10, 45? %d\n", get_gcd(10, 45));

    return 0;
}
