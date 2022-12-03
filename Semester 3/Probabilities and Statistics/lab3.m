% to solve normal law, 3rd lab ex 1 for student, fisher, and chi(pronunciation: kai).. - only the prefix changes, and params a bit
% student prefix -> t
% fisher prefix -> f
% chi prefix -> chi2

% 2 radom variables are the same if they have the same pdf (x=y iff fx == fy)

% at the exam: COMMENTS EXPLAINING CODE

miu = input("miu: ")
sigma = input("sigma: ")

% a
%xless = normcdf(0,miu,sigma) % a1
%xmore = 1 - normcdf(0,miu,sigma) % a2

% b
%b1 = normcdf(1,miu,sigma) - normcdf(-1,miu,sigma)
%b2 = 1 - ( normcdf(1,miu,sigma) - normcdf(-1,miu,sigma) )

% c

%alpha = input("Alpha (0-1): ")
%c = norminv(alpha, miu, sigma)

% d
%beta = input("Beta (0-1): ")
%d = norminv(1 - beta, miu, sigma)

