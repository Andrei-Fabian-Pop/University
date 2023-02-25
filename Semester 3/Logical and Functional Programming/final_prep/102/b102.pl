
% arr

generate(T, H, [H|T]).
generate([H|T], E, [H|R]) :- generate(T, E, R).


arr([H|_], 1, [H]).
arr([_|T], K, R) :- arr(T, K, R).
arr([H|T], K, R1) :- K > 1, K1 is K-1, arr(T, K1, R), generate(R, H, R1).

sum([], 0).
sum([H|T], R) :- sum(T, R1), R is R1+H.

% checksum(L, S, 1) :- sum(L, R1), S =:= R1, !.
% checksum(L, S, 0) :- sum(L, R1), S =\= R1, !.

% list, k, s, res
sol(L, K, S, R) :- arr(L, K, R), sum(R, RS), RS =:= S.

allSols(L, K, S, Res) :- findall(Part, sol(L, K, S, Part), Res).

