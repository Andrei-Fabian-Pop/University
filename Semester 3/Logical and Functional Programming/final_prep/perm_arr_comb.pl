
% generate will generate all the possible combinations where element e is in list l
% list, elem, res -- (i,i,o)
generate(L, E, [E|L]).
generate([H|T], E, [H|R]) :- generate(T, E, R). 

% -----------------------------------------------------------------------------------------

% permutations 
% list, res -- (i, o)
perm([], []).
perm([H|T], R1) :- perm(T, R), generate(R, H, R1).

% get all permutations (using findall)
permutations(L, Res) :- findall(Part, perm(L, Part), Res).

% -----------------------------------------------------------------------------------------

% arrangements
% list, k, res -- (i, i, o)
arr([H|_], 1, [H]).
arr([_|T], K, R) :- arr(T, K, R).
arr([H|T], K, R1) :- K > 1, K1 is K-1, arr(T, K1, R), generate(R, H, R1).

% get all arrangements (using findall)
arrangements(L, K, Res) :- findall(Part, arr(L, K, Part), Res).

% -----------------------------------------------------------------------------------------

% combinations
% list, k, res -- (i, i, o)
com([H|_], 1, [H]).
com([_|T], K, R) :- com(T, K, R).
com([H|T], K, [H|R]) :- K > 1, K1 is K-1, com(T, K1, R).

% get all combinations (using findall)
combinations(L, K, Res) :- findall(Part, com(L, K, Part), Res).


