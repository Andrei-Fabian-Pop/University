##To reach the maximum efficiency in performing an assembling operation in a 
##manufacturing plant, new employees are required to take a 1-month training course.
##A new method was suggested, and the manager wants to compare the new method 
##with the standard one, by looking at the lengths of the time required 
##for employees to assemple a certain device. They are given below (and assume 
##appoximatively normally distributed):
##  standard = [46 37 39 48 47 44 35 31 44 37];
##  new = [35 33 31 35 34 30 27 32 31 31];
##a.) At 5% significance level, do the poulation variances seem to differ?
##b.) Find a 95% confidence interval for the difference of average assembling times

% Load the statistics package
pkg load statistics;

standard = [46 37 39 48 47 44 35 31 44 37];
new = [35 33 31 35 34 30 27 32 31 31];

% Set the significance level
alpha = 0.05;

% Test the hypothesis that the variances are equal
[h, p] = vartest2(standard, new, "alpha", alpha);

% Print the results
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

% Calculate the mean difference and standard error
mean_diff = mean(standard) - mean(new);
n = length(standard);
se = sqrt((std(standard)^2 + std(new)^2) / n);

% Calculate the critical value for the t-test
t_crit = tinv(1 - alpha/2, n - 1);

% Calculate the confidence interval
ci = [mean_diff - t_crit * se, mean_diff + t_crit * se];

% Print the confidence interval
printf("95%% confidence interval for the difference of average assembling times: (%g, %g)\n", ci);
