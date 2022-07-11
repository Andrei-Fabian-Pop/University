//
// Created by AndreiFabianPop on 24/02/2022.
//
// 2.
// a. Generate the first n prime numbers (n is a given natural number).
// b. Given a vector of numbers, find the longest contiguous subsequence such that any two consecutive elements are relatively prime.

#include <stdio.h>
#include <stdlib.h>

int prime(int x) {
    if (x < 2) {
        return 0;
    } else if (x == 2) {
        return 1;
    } else if (x % 2 == 0) {
        return 0;
    } else {
        int d = 3;
        while (d * d <= x) {
            if (x % d == 0) {
                return 0;
            }
            d += 2;
        }
    }
    return 1;
}

void print_menu() {
    printf("1. Read a vector of numbers.\n");
    printf("2. Solve functionality 1.\n");
    printf("3. Solve functionality 2.\n");
    printf("4. Exit the program.\n");
}

int get_user_command() {
    int x;
    printf("Enter functionality number:");
    scanf("%d", &x);
    return x;
}

int *read_vector(int len) {
    printf("Enter vector values:");
    int *v = malloc(len * (int) sizeof(int));
    for (size_t i = 0; i < len; ++i) {
        scanf("%d", &v[i]);
    }

    return v;
}

int GCD(int a, int b) {
    int d = 1, gcd = 0;
    while (d <= a && d <= b) {
        if (a%d==0 && b%d==0) {
            gcd = d;
        }
        ++d;
    }
    return gcd;
}

void solve1(int x) {
    int n = 2;
    while (x > 0) {
        if (prime(n) == 1) {
            printf("%d ", n);
            x -= 1;
        }
        n += 1;
    }
    printf("\n");
}

void solve2(const int *v, int len) {
    int max_st = 0, max_en = 0, current_st, current_en;
    for (int i = 0; i < len; ++i) {
        current_st = i;
        current_en = i;
        for (int j = i + 1; j < len; ++j) {
            if (GCD(v[j-1], v[j]) == 1) {
                current_en++;
            } else {
                i = j-1;
                break;
            }
        }
        if (current_en - current_st > max_en - max_st) {
            max_st = current_st;
            max_en = current_en;
        }
    }

    for (int i = max_st; i <= max_en; ++i) {
        printf("%d ", v[i]);
    }
    printf("\n");
}

int main() {
    int *v, len = 0;

    print_menu();
    int command = get_user_command();
    while (command != 4) {
        if (command == 1) {
            printf("Enter vector length:");
            scanf("%d", &len);
            v = read_vector(len);
        } else if (command == 2) {
            int x;
            printf("Enter length:");
            scanf("%d", &x);
            solve1(x);
        } else if (command == 3) {
            if (len == 0) {
                printf("Use functionality 1 to read the vector first.\n");
            } else {
                solve2(v, len);
            }
        } else {
            printf("Unknown.");
        }

        command = get_user_command();
    }

    return 0;
}
