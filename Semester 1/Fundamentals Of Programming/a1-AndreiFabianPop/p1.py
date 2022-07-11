# 1st set, problem 1

def read():
    # the function reads a natural number and returns it
    # INPUT: none
    # OUTPUT: n - natural number
    n = int(input("Enter a natural number: "))
    return n

def prime(n):
    # the function checks weather the natural number n is a prime number
    # INPUT: n - natural number that will be checked
    # OUTPUT: boolean value that represents weather n is a prime number
    if n < 2:
        return False
    if n == 2:
        return True
    if n % 2 == 0:
        return False
    else:
        d = 3
        while d*d <= n:
            if n % d == 0:
                return False
            d += 2
    return True

def next_prime_number(n):
    # generate odd numbers greater than the natural number n and checks weather they are prime
    # INPUT: n - natural number
    # OUTPUT: x - first prime number greater than n
    x = n+1 if n % 2 == 0 else n+2
    while True:
        if prime(x):
            return x
        else:
            x += 2

if __name__ == '__main__':
    n = read()
    print(next_prime_number(n))
