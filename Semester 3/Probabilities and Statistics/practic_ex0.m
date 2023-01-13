# ex 10

a = [1021 980 1017 988 1005 998 1014 985 995 1004 1030 1015 995 1023];
b = [1070 970 993 1013 1006 1002 1014 997 1002 1010 975];

lena = columns(a);
lenb = columns(b);

alpha = 0.05;

[h, p, ci, stats] = vartest2(a, b, "alpha", alpha);
rr = [finv(alpha/2, lena-1, lenb-1), finv(1-alpha/2, lena-1, lenb-1)];

printf("Test for equal variances\n");
printf("Significance level: %g\n", alpha);
printf("P-value: %g\n", p);
if h == 1
  printf("Reject the null hypothesis\n");
  printf("Data suggests that the variances are not equal\n");
else
  printf("Fail to reject the null hypothesis\n");
  printf("Data suggests that the variances are equal\n");
endif
printf("test statistic: %f\n", stats.fstat);
printf("rejection region: (-inf, %g) U (%g, inf)\n", rr);

# b)
[h, p, ci, stats] = vartest2(a, b, "tail", "left");
rr = [-inf, finv(alpha, lena-1, lenb-1)];


