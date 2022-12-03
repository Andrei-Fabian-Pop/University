%Lab4

%ex2
clear
p = input('give the probability');
N = input('give the nb of sim');
U = rand(1,N);
X = (U < p);
U_X = unique(X)
n_X = hist(X,length(U_X));
rel_freq = n_X / N

%ex3
clear
p = input('give the probability ');
n = input('give the nb of trials ');
N = input('give the nb of sim ');
for i=1:N
	U = rand(n,1);
	X(i) = sum(U<p);
endfor
k=0:n;
U_X = unique(X);
n_X = hist(X,length(U_X));
rel_freq = n_X / N;
plot(U_X,rel_freq,'*',k,binopdf(k,n,p),'*r')