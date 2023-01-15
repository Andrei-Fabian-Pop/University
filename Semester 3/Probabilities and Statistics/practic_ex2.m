
np = [3.26 1.89 2.42 2.03 3.07 2.95 1.39 3.06 2.46 3.35 1.56 1.79 1.76 3.82 2.42 2.96];
n = columns(np);

alpha = 0.05;

npmean = mean(np);
npstd = std(np);
studdist = tinv(1-alpha/2, n-1);

bound = [(npmean - npstd*studdist/(sqrt(n))), npmean + npstd*studdist/(sqrt(n))];
printf("%g - %g\n", bound)

##### bbbb
alpha = 0.01;
mu = 3;

[h, p, ci, stats] = ttest(np, mu, "alpha", alpha, "tail", "left");
rr = [-inf, tinv(alpha, n-1)];

if h == 1
  printf("Reject the null hypothesis\n");
  printf("Data suggests that the nickel particles do NOT seem to be smaller than 3\n");
else
  printf("Fail to reject the null hypothesis\n");
  printf("Data suggests that the nickel particles seem to be smaller than 3\n");
endif
printf("rr: (%g, %g)\n", rr)
printf("p-value: %g\n", p)
printf("test statistics stats: %g\n", stats.tstat)
