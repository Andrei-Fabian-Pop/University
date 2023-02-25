
n = [1001.7 975.0 987.3 978.7 988.9 1000.3 979.2 968.9 983.5 999.2 985.6];
nlen = columns(n);

# aplha is the significance level
alpha = 0.05;

# calculate the mean of n
m = mean(n);

# compute the standard deviation
nstd = std(n);

# compute the quantile (cdf inverse because it says is faster than 995m/s) of the student T distribution
# 1st part from the first confidence interval
studdist = tinv(1-alpha/2, nlen);

# For normal underlying population and σ known
# 1st part from the first confidence interval
bound = [(m - nstd*studdist/(sqrt(nlen))), m + nstd*studdist/(sqrt(nlen))];

printf("The mean of the muzzle velocities is %g.\n", m);
printf("At a 5 percent significance level the muzzle velocities have the range (%g - %g).\n", bound);
printf("Since the bound range is (%g - %g) and the upper limit is lower then 995 m/s, the hypothesis is incorrect, the muzzles are slower, on average than 995 m/s.\n\n", bound);


# b

# confidence level = 1 - significance level
alpha = 0.01;

# std computes the standard deviation
nstd = std(n);
printf("The standard devioation when the significance level is 1 percent is %g\n", nstd);

