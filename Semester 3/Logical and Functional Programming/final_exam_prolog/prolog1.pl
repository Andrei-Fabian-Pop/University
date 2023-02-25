
valley([_], 0) :- !.
valley([H1,H2|T], _) :- H1 < H2, !, valley([H2|T], 0), !.
valley([_,H2|T], 1) :- valley([H2|T], 1), !.


altern([], 0) :- !.
altern([H1,H2|T], S) :- altern(T, S1), S is S1+H1-H2, !.
altern([H], H) :- !.
