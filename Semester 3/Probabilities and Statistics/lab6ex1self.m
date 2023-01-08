% Load the statistics package
pkg load statistics

% Set the significance level
alpha = 0.05;

% Input the data
x = [7 7 4 5 9 9 4 12 8 1 8 7 3 13 2 1 17 7 12 5 6 2 1 13 14 10 2 4 9 11 3 5 12 6 10 7];
n = length(x);

% Test the hypothesis that the mean is at least 9, with known variance
mu = 9;
sigma = 5;
[h, p, ci, z, zcrit] = ztest(x, mu, sigma, "alpha", alpha, "tail", "left");

% Calculate the critical value for the z-test
z_crit = norminv(1 - alpha, 0, 1);

% Define the rejection region
rej_region = [-inf, z_crit];

% Print the results
printf("Test for mean >= 9 with known variance\n");
printf("Significance level: %g\n", alpha);
printf("P-value: %g\n", p);
printf("Rejection region: (%g, %g)\n", rej_region);

% Print the results
printf("Test for mean >= 9 with known variance\n");
printf("Significance level: %g\n", alpha);
printf("P-value: %g\n", p);
if h == 1
  printf("Reject the null hypothesis\n");
  printf("Data suggests that the standard is not met\n");
else
  printf("Fail to reject the null hypothesis\n");
  printf("Data suggests that the standard is met\n");
endif

% Test the hypothesis that the mean is at least 9, with unknown variance
[h, p, ci, stats] = ttest(x, mu, "alpha", alpha, "tail", "left");

% Print the results
printf("\nTest for mean >= 9 with unknown variance\n");
printf("Significance level: %g\n", alpha);
printf("P-value: %g\n", p);
if h == 1
  printf("Reject the null hypothesis\n");
  printf("Data suggests that the standard is not met\n");
else
  printf("Fail to reject the null hypothesis\n");
  printf("Data suggests that the standard is met\n");
endif

% Test the hypothesis that the mean is greater than 5.5, with unknown variance
mu = 5.5;
[h, p, ci, stats] = ttest(x, mu, "alpha", alpha, "tail", "right");

% Print the results
printf("\nTest for mean > 5.5 with unknown variance\n");
printf("Significance level: %g\n", alpha);
printf("P-value: %g\n", p);
if h == 1
  printf("Reject the null hypothesis\n");
  printf("Data suggests that the mean is greater than 5.5\n");
else
  printf("Fail to reject the null hypothesis\n");
  printf("Data suggests that the mean is not greater than 5.5\n");
endif
