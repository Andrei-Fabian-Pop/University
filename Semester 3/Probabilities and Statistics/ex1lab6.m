# 1) a) H0: mean = 9, H1: mean < 9
# this is a left-tailed test for the mean when sigma is known (cheat sheet a-1)

# alpha = 
alpha = input("give the significance level:")
x = [7 7 4 5 9 9 4 12 8 1 8 7 3 13 2 1 17 7 12 5 6 2 1 13 14 10 2 4 9 11 3 5 12 6 10 7]
n = length(x)
# the null hyp is H0: miu = 9
# the alt hyp is H1: miu < 9
# left-tailed test for the mean, when sigma known
printf("solving 1a\n")
printf("left-tailed test for miu, when sigma known\n")

m0 = 9
sigma = 5

[h, p, ci, z, zcrit] = ztest(x, m0, sigma, "alpha", alpha, "tail", "left")

z2 = norminv(alpha)
RR = [-inf, z2]

printf("The value of h is %d\n", h)
if (h == 1) 
    printf("The null hyp H0 is rejected\n")
    printf("The data suggests that the stancdard is not met\n")
else
    printf("The null hyp H0 is not rejected\n")
    printf("The data suggests that the stancdard is met\n")
endif

printf("The observerd value of the test statistic is %4.4f\n", z)
printf("RR = (%4.4f, %4.4f)\n", RR)
printf("The p value of the test is %4.4f\n", p)

# 1. b)

# H0: miu = 5.5
# H1: miu > 5.5

# right-tail test for miu, sigma unknown
# a-1

m0 = 5.5

[h, p, ci, stats] = ttest(x, m0, "alpha", alpha, "tail", "right")
t2 = tinv(1-alpha, n-1)
RR = [t2, inf]

printf("The value of h is %d\n", h)
if (h == 1) 
    printf("The null hyp H0 is rejected\n")
    printf("The data suggests that the stancdard is not met\n")
else
    printf("The null hyp H0 is not rejected\n")
    printf("The data suggests that the stancdard is met\n")
endif

printf("The observerd value of the test statistic is %4.4f\n", stats.tstat)
printf("RR = (%4.4f, %4.4f)\n", RR)
printf("The p value of the test is %4.4f\n", p)

# sigma^2 = vartest
# 2 populations (x1 = data from first, x2 = data for second)
# sigma1^2/sigma2^2 = vartest2

# miu1 - miu2 = ztest2 or ttest2 or kai


# POSSIBLE BONUS POINTS, ASK COLLEGUES -- ignore if you read this from github :))