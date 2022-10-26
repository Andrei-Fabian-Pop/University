%n = input("nr of tries: ")
%p = input("probabilities: ")
x = 0:n
yp = binopdf(x,n,p)
%plot(y, "*")
%hold on
xx = 0:0.01:n
yy = binocdf(xx,n,p)
%plot(yy)

% exercice 2 a

coinToss = 3
p = .5
x3 = 0:coinToss
X3 = binopdf(x3, coinToss, p)
plot(X3, "*")

% 2b todo
binocdf(0, 3, .5)

% 2c P(X=0)
binopdf(0,3,.5)
1-binopdf(0,3,0.5)

% 2d
binocdf(2,3,.5)
binocdf(1,3,.5)

% 2e
1-binocdf(0,3,.5)
1-binocdf(1,2,.5)

% 2f
