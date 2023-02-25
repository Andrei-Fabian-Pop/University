
% miaw

% f([], -1):-!.
% f([_|T], Y):- f(T,S), S<1, !, Y is S+2.
% f([H|T], Y):- f(T,S), S<0, !, Y is S+H.
% f([_|T], Y):- f(T,S), Y is S.

% no f(T,S)

f([], -1) :- !.
f([_|T], Y) :- f(T,S), aux(_, S, Y).

aux(_, S, R) :- S < 1, !, R is S+2.
aux(H, S, R) :- S < 0, !, R is S+H.
aux(_, S, S).
