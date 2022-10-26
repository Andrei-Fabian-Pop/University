% ex 14.
% a. Write a predicate to test equality of two sets without using the set difference.
% sameset([1,5,2,3,3],[3,1,2,3,5]).

% sameset(a1..an, b1...bk) = { true, a=b=null
% 							 { sameset(a2...an, b/{a1}), a1 included in b

remover(_, [], []) :- !.
remover(R, [R|T], T) :- !.
remover(R, [H|T], [H|T2]) :- H \= R, remover(R, T, T2).

mem(H, [H|_]) :- !.
mem(E, [_|T]) :- mem(E, T).

% (i,i)
% (i,o)
sameset([], []) :- !.
sameset([H|T], L) :- 
    mem(H, L),
    remover(H, [H|T], HN),
    remover(H, L, LN),
    sameset(HN, LN).

test_sameset() :- 
	sameset([1,2], [2,1]),
	sameset([1,5,2,3,3],[3,1,2,3,5]),
	\+sameset([1,2,3], [1,2,4]).
