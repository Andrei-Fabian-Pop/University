% 11
%
% b. For a heterogeneous list, formed from integer numbers and list of numbers, define a predicateto determine the maximum number of the list, 
% and then to replace this value in sublists with the maximum value of sublist.Eg.: 
% [1, [2, 5, 7], 4, 5, [1, 4], 3, [1, 3, 5, 8, 5, 4], 5, [5, 9, 1], 2] =>[1, [2, 7, 7], 4, 5, [1, 4], 3, [1, 3, 8, 8, 8, 4], 5, [9, 9, 1], 2]
%
% mainHetero([1, [2, 5, 7], 4, 5, [1, 4], 3, [1, 3, 5, 8, 5, 4], 5, [5, 9, 1], 2], Res) ; true.
%
% heterList(l1...ln, m) = 
% 	[], n = 0
% 	replaceEl(l1, m, maxim_list(l1)) + heterList(l2...ln, m), not number(l1) = True
% 	l1 + heterList(l2...ln, m), otherwise

% from prev ex
replaceElem([], _, _, []) :- !.
replaceElem([H|T], E1, E2, [E2|R]) :-
	H =:= E1, 
	!,
	replaceElem(T, E1, E2, R), !.
replaceElem([H|T], E1, E2, [H|R]) :-
	replaceElem(T, E1, E2, R).

% (i,i,o)
maxNum(A, B, A) :- A >= B.
maxNum(A, B, B) :- A < B.

% (i,i,o)
minNum(A,B,A) :- A =< B.
minNum(A,B,B) :- A > B.

% (i, o)
maxList([H], H) :- !.
maxList([H|T], R) :-
	number(H),
	!,
	maxList(T, RM),
	maxNum(H, RM, R).
maxList([_|T], R) :-
	maxList(T, R), !.

% (i,o)
minList([H], H) :- !.
minList([H|T], R) :-
    number(H),
    !,  
    minList(T, RM),
    minNum(H, RM, R). 
minList([_|T], R) :-
    minList(T, R), !.

% (i, o)
straightList([], _, []) :- !.
straightList([H|T], M, [HR|TR]) :- 
	\+number(H),
	!,
	maxList(H, RM),
	replaceElem(H, M, RM, HR),
	straightList(T, M, TR).
straightList([H|T], M, [H|R]) :-
	straightList(T, M, R), !.

% bonus
% (i, o)
straightListb([], _, []) :- !.
straightListb([H|T], M, [HR|TR]) :-
    \+number(H),
    !,
    minList(H, RMIN),
	maxList(H, RMAX),
	replaceElem(H, M, RMAX, HRA),
    replaceElem(HRA, RMIN, M, HR),
    straightListb(T, M, TR).
straightListb([H|T], M, [H|R]) :-
    straightListb(T, M, R), !.


% (i, o)
mainHetero(L, R) :- 
	maxList(L, RM),
	straightList(L, RM, R).

mainBonus(L, R) :-
	maxList(L, RM),
	straightListb(L, RM, R).

testH() :-
	mainHetero([1, [2, 5, 7], 4, 5, [1, 4], 3, [1, 3, 5, 8, 5, 4], 5, [5, 9, 1], 2], 
			   [1, [2, 7, 7], 4, 5, [1, 4], 3, [1, 3, 8, 8, 8, 4], 5, [9, 9, 1], 2]),
	mainHetero([10, [10, 19, 10], 4, 10, [10, 199], 3, [1, 3, 5, 8, 5, 4], 5, [5, 10, 11], 2], 
			   [10, [19, 19, 19], 4, 10, [199, 199], 3, [1, 3, 5, 8, 5, 4], 5, [5, 11, 11], 2]),
	\+mainHetero([7, [2, 5, 7], 4, 5, [5, 4], 3, [1, 3, 5, 8, 5, 4], 5, [5, 9, 1], 2], 
				 [1, [2, 7, 7], 4, 5, [1, 4], 3, [1, 3, 8, 8, 8, 4], 5, [9, 9, 1], 2]).

% min = M
% M = max
testB() :-
    mainBonus([1, [2, 5, 7], 4, 5, [1, 4], 3, [1, 3, 5, 8, 5, 4], 5, [5, 9, 1], 2], 
			  [1, [5, 5, 7], 4, 5, [5, 4], 3, [5, 3, 5, 8, 5, 4], 5, [5, 9, 5], 2]),
    mainBonus([0, [2, 5, 7], 4, 5, [4, 4], 3, [1, 3, 5, 8, 5, 4], 5, [5, 9, 1], 2], 
			  [0, [5, 5, 7], 4, 5, [5, 5], 3, [5, 3, 5, 8, 5, 4], 5, [5, 9, 5], 2]),
    \+mainBonus([7, [2, 5, 7], 4, 5, [5, 4], 3, [1, 3, 5, 8, 5, 4], 5, [5, 9, 1], 2], 
				[1, [5, 5, 7], 4, 5, [5, 4], 3, [5, 3, 5, 8, 5, 4], 5, [5, 9, 5], 2]),
	mainBonus([10, [1, 19, 1], 4, 10, [10, 199], 3, [1, 3, 5, 8, 5, 4], 5, [5, 10, 11], 2],
              [10, [10, 19, 10], 4, 10, [10, 199], 3, [10, 3, 5, 8, 5, 4], 5, [10, 10, 11], 2]).

