% 7. A player wants to choose the predictions for 4 games. 
% The predictions can be 1, X, 2. 
% Write a predicate to generate all possible variants considering that: 
% last prediction can’t be 2 and no more than two possible predictions X.
%

prediction(1).
prediction(2).
prediction(3). % X = 3

% allP(n, c, p) =
% 	c, n = 4
% 	allP(n + 1, prediction(x) + c, p * x), p*x % 27 = 0

% allP(i,i,o,i)
% allP(i,i,i,i)
allP(1, R, R, _) :- !.
allP(I, C, R, P) :- 
	prediction(X),
	I1 is I-1,
	P1 is P*X,
	P1 mod 27 =\= 0,
	allP(I1, [X|C], R, P1).

% res(o)
res(R) :- allP(4,[1],R,1).
res(R) :- allP(4,[3],R,3).

res(R, N) :- allP(N,[1],R,1).
res(R, N) :- allP(N,[3],R,1).

% allSol(o)
allSol(R) :-
	%res(R).
	findall(RP, res(RP), R).

allSol(N, R) :-
	findall(RP, res(RP, N), R).

tests() :-
	allSol(1, [[1], [3]]),
	allSol(2, [[1, 1], [2, 1], [3, 1], [1, 3], [2, 3], [3, 3]]),
	allSol(3, [[1, 1, 1], [2, 1, 1], [3, 1, 1], [1, 2, 1], [2, 2, 1], [3, 2, 1], [1, 3, 1], [2, 3, 1], [3, 3, 1], 
			   [1, 1, 3], [2, 1, 3], [3, 1, 3], [1, 2, 3], [2, 2, 3], [3, 2, 3], [1, 3, 3], [2, 3, 3], [3, 3, 3]]).

