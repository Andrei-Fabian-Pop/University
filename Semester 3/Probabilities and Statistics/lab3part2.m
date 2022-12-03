n = input("n: ")
p = input("p: ")
lambda = n * p
%x = 0:n
%plot(x, binopdf(x,n,p), 'g')
%hold on
%plot(x, poisspdf(x,lambda))

for n=1:10:1000
  x = 0:n
  plot(x, binopdf(x,n,p))  
  pause(0.5)
endfor