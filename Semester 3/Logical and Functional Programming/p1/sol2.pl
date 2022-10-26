% ex 14 b
% b. Write a predicate to select the n-th element of a given list.
% nth([1,2,34,5,6,7], 2, H).

% nth(l1...ln, i) = { l1, i = 0
% 					{ nth(l2...ln, i-1), n > 0

% (i,i,o,o)
% (i,i,i,o)
% (i,i,o,i)
% (i,i,i,i)
nth([H,H1|_],0,H,H1) :- !.
nth([_|T],N,H,NH) :-
    N > 0, 
    N1 is N-1,
    nth(T,N1,H,NH).

test_nth() :-
	nth([1,2,34,5,6,7], 2, 34),
	\+nth([1,2,3,4], 1, 1).
