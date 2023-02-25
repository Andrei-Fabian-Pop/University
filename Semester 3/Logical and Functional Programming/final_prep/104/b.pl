
% pl

insert(E, T, [E|T]).
insert(E, [H|T], [H|R]) :- insert(E, T, R).

perm([], []).
perm([H|T], R) :- perm(T, R1), insert(H, R1, R).

arr([H|T], 1, [H]).
arr([_|T], K, R) :- arr(T, K, R).
arr([H|T], K, R) :- K > 1, K1 is K-1, arr(T, K1, R1), insert(H, R1, R).

comb([H|T], 1, [H]).
comb([_|T], K, R) :- comb(T, K, R).
comb([H|T], K, [H|R]) :- K > 1, K1 is K-1, comb(T, K1, R).

sets([], []).
sets([H|T], [H|R]) :- sets(T, R).
sets([_|T], R) :- sets(T, R).


