# Hypotesis testing

# past / previous experiences - H0
# future alternatives - H1

# H0 = the null hypotesis
# H1 = the alternative / research hypotesis

# Usually we have: theta0 given (known)
#            H0: theta = theta0
#            H1: either one of the following: 
#                   theta < theta0 => left-tailed test
#                   theta > theta0 => right-tailed test
#                   theta != theta0 => two-tailed test
# Result: reject H0 or do not reject H0

# Termilology:
#     alpha = significance level (0,1), but in application it will belong in {0.05, 0.01, 0.001}
#     TS = test statistic 
#     TS0 = TS with theta = theta0, observerd value of TS
#     RR = rejection region
#     P-value = minimum threshold of rejection (smallest alpha for which we still reject H0)

# How do we decide if we reject or we do not reject?
# Hypotesis testing:
#     if TS0 in RR then reject H0
#     else TS0 not in RR then do not reject H0
# Significance testing:
#     (...)

# VERY IMPORTANT: Print to the screen TS0, RR, P or points will be lost at the exam

# [H, P, Ci, Z, ZCRIT] = ztest(X, M, SIGMA, NAME, VALUE)
# H = 0 (not rejected) or 1 (rejected)
# P = P-value
# Z = TS0
# Ci, ZCRIT = not important
# X = data
# M = m0 / miu0 (is given)
# SIGMA = sigma
# NAME = {"alpha", "tail"}
# VALUE depends on NAME (parameter of NAME)

# [H, P, Ci, STATS] = ttest(X, M, NAME, VALUE)
# STATS = struct{ tstat=TS0, ... }















