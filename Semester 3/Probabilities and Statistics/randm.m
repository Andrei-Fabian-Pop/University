% random.org

n = input("Enter nr of simulations: ")
c = rand(3,n)
y = c < .5
x = sum(y)
hist(x)