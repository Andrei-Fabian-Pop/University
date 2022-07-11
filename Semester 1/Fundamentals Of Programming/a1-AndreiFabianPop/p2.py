# Set 2, problem number 8.

def get_num():
    # The function returns the number that was read from the user
    # INPUT: none
    # OUTPUT: n - natural number greater than 2
    n = int(input("Enter a natural number greater than 2: "))
    return n

def generate_fib(k):
    # The function generates the Fibonacci sequence and returns the first number from the sequence that is
    # greater than the given parameter k
    # INPUT: k - natural number greater than 2
    # OUTPUT: b - smallest number from the Fibonacci sequence greater than k
    a, b = 1, 0
    while k >= b:
        a, b = a+b, a
    return b

if __name__ == '__main__':
    n = get_num()
    m = generate_fib(n)
    print(m)
