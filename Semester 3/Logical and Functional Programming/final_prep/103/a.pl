
% f([],-1).
% f([H|T],S):-f(T,S1), S1<1, S is S1-H, !.
% f([_|T],S):-f(T,S).

% exclude f(T,S)

f([], -1).
f([H|T], S) :- f(T, S1), aux(S1, H, S).

aux(S1, H, S) :- S1 < 1, S is S1-H, !.
aux(_, S, S).

