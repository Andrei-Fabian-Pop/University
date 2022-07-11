# Set 3, problem 13.

def get_num():
    # function reads a non-null natural number from the user and returns it
    # INPUT: none
    # OUTPUT: n - non-null natural number
    return int(input("Enter a natural non-null number: "))

def decompose(x, n):
    # This function decomposes the input parameter x into the prime divisors and counts them into s
    # until the parameter n is 0, then it prints the last divisor on the console, or x is 1 and returns s
    # INPUT: x - natural number
    #        n - natural non-null number
    # OUTPUT: s - the number of prime divisors of x
    s = 0
    d = 2
    while x != 1:
        if x % d == 0:
            x /= d
            s += 1
            n -= 1
            if n == 1:
                print(d)
                break
        else:
            d += 1
    return s

def generate(n):
    # This function generates the n-ht element from the sequence of natural numbers by replacing
    # composed numbers with their prime divisors
    # INPUT: n - natural non-null number that represents the length of the sequence
    # OUTPUT: the sequence is written on the console
    if n == 1:
        print(1)
    else:
        x = 0
        while n > 0:
            x += 1
            n -= decompose(x, n)


if __name__ == '__main__':
    n = get_num()
    generate(n)
