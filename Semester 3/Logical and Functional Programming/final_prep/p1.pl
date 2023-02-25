% prolog exam prep

gcd(A, 0, A) :- !.
gcd(0, A, A) :- !.
gcd(A, B, R) :- A1 is A mod B, gcd(B, A1, R), !.

lcm(A, B, R) :- gcd(A, B, R1), R is A * B / R1.

% list, e, i, power, res
pw([], _, _, _, []) :- !.
pw([H|T], E, I, P, [H,E|R]) :- I =:= P, P2 is P * 2, I2 is I + 1, pw(T, E, I2, P2, R), !.
pw([H|T], E, I, P, [H|R]) :- I =\= P, I2 is I + 1, pw(T, E, I2, P, R), !.



