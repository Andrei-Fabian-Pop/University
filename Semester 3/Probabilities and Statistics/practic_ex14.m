% A study is conducted to compare the heat loss in glass pipes, versus steel pipes 
% of the same size. Various liquids at identical starting temperatures are run through 
% segments of each type and the heat loss (in celsius) is measured. These are the
% data results (normality of the 2 populations is assumed):
%   steel = [4.6 0.7 4.2 1.9 4.8 6.1 4.7 5.5 5.4]
%   glass = [2.5 1.3 2.0 1.8 2.7 3.2 3.0 3.5 3.4]
% a) at 5% significance level, do the population variances seem to differ?
% b) at the same significance level, does it seem that on average, steel pipes lose more heat than glass pipes?

% Load the statistics package
pkg load statistics;

% Set the significance level
alpha = 0.05;

steel = [4.6 0.7 4.2 1.9 4.8 6.1 4.7 5.5 5.4];
glass = [2.5 1.3 2.0 1.8 2.7 3.2 3.0 3.5 3.4];

% Test the hypothesis that the variances are equal
[h, p] = vartest2(steel, glass, "alpha", alpha);

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

% Test the hypothesis that the mean heat loss of steel pipes is greater than that of glass pipes
[h, p] = ttest2(steel, glass, "alpha", alpha, "tail", "right");

% Print the results
printf("Test for mean heat loss of steel pipes > mean heat loss of glass pipes\n");
printf("Significance level: %g\n", alpha);
printf("P-value: %g\n", p);
if h == 1
  printf("Reject the null hypothesis\n");
  printf("Data suggests that the mean heat loss of steel pipes is greater than that of glass pipes\n");
else
  printf("Fail to reject the null hypothesis\n");
  printf("Data suggests that the mean heat loss of steel pipes is not greater than that of glass pipes\n");
endif
