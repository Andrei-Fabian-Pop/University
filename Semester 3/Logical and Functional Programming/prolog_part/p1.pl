% (A, B, Res)
% cmmdc

gcd(A, 0, A) :- !.
gcd(0, B, B) :- !.
gcd(A, B, R) :- 
	A >= B,
	A1 is A mod B,
	gcd(A1, B, R),
	!.
gcd(A, B, R) :-
	A < B,
	B1 is B mod A,
	gcd(A, B1, R),
	!.

% cmmmc
lcm(A, B, R) :-
	gcd(A, B, Res),
	R is A * B / Res.

% remove occurences
remoc([], _, []) :- !.
remoc([H|T], E, R) :-
	H =:= E,
	remoc(T, E, R), !.
remoc([H|T], E, [H|R]) :-
	H =\= E,
	remoc(T, E, R), !.

% bubble sort
bubblesort(List, SortedList) :-
    swap(List, List1), !,
    bubblesort(List1, SortedList).
bubblesort(List, List).

swap([X,Y|Rest], [Y,X|Rest]) :-
    X > Y, !.
swap([Z|Rest], [Z|Rest1]) :-
    swap(Rest, Rest1).

% append
% single elem
appnd([], E, [E]).
% list
% appnd([], E, E).
appnd([H|T], E, [H|R]) :-
	appnd(T,E,R).



% % 12.
% a. Define a predicate to add after every element from a list, the divisors of that number.
% b. For a heterogeneous list, formed from integer numbers and list of numbers, 
% define a predicate to add in every sublist the divisors of every element.
% Eg.: [1, [2, 5, 7], 4, 5, [1, 4], 3, 2, [6, 2, 1], 4, [7, 2, 8, 1], 2] =>
% [1, [2, 5, 7], 4, 5, [1, 4, 2], 3, 2, [6, 2, 3, 2, 1], 4, [7, 2, 8, 2, 4, 1], 2]


% divs(Elem, Div(2), ListRes)
divs(_, _, []) :- !.
divs(E, D, R) :-
	E =\= 1,
	E mod D =:= 0,
	D1 is D+1,
	E1 is E / D,
	divs(E1, D1, [D|R]).
divs(E, D, R) :-
	E =\= 1,
	E mod D =\= 0,
	D1 is D+1,
	divs(E, D1, R).

divisors(N, Divisors) :-
    findall(X, ( between(2, N, X), N rem X =:= 0 ), Divisors).

subl([H|_], R) :-
	divisors(H, Res),
	appnd(R, Res).

heter([], []) :- !.	
heter([H|T], R) :-
	is_list(H), !,
	subl(H, Res),
	heter(T, [Res|R]).


% 7.
% a. Determine the position of the maximal element of a linear list.
% Eg.: maxpos([10,14,12,13,14], L) produces L = [2,5].
% b. For a heterogeneous list, formed from integer numbers and list of numbers,
% replace every sublist with the position of the maximum element from that sublist.
% [1, [2, 3], [4, 1, 4], 3, 6, [7, 10, 1, 3, 9], 5, [1, 1, 1], 7] =>
% [1, [2], [1, 3], 3, 6, [2], 5, [1, 2, 3], 7]


maxn(A, B, A) :- A >= B, !.
maxn(A, B, B) :- A < B, !.

maxList([H], H) :- !.
maxList([H|T], Res) :-
	maxList(T, R),
	maxn(H, R, Res).

%posList([], _, L, L) :- !.
%posList([H|T], P, [P|R], L) :-
%	posList(T, P, R),
idk([], _, _, []) :- !.
idk([H|T], M, C, [R|RT]) :-
	H =:= M, !,
	RT is C,
	C1 is C+1,
	idk(T, M, C1, R).


replace_pos([], _, _, []) :- !.
replace_pos([H|T], H, Pos, [Pos|R]) :-
    NPos is Pos + 1,
    replace_pos(T, H, NPos, R), !.
replace_pos([_|T], E, Pos, R) :-
    NPos is Pos + 1,
    replace_pos(T, E, NPos, R), !.


insert_list([], _, _, []) :- !.
insert_list([H|T], E, Pos, [H,E|R]) :- Pos mod 2 =:= 1, !,
    NPos is Pos + 1,
    insert_list(T, E, NPos, R).
insert_list([H|T], E, Pos, [H|R]) :-
    NPos is Pos + 1,
    insert_list(T, E, NPos, R).

% l1, l2, carry, result
carr(N1, N2, 0, R) :-
	N1 >= N2,
	R is N1 - N2, !.
carr(N1, N2, 1, R) :-
	N1 < N2,
	R is 10 + N1 - N2, !.

pred(L, [], 0, L) :- !.
pred([H1|T1], [H2|T2], C, [R|RT]) :- 
	pred(T1, T2, C, RT),
	H11 is H1 - C,
	carr(H11, H2, C, R).	

leadingZ([], []) :- !.
leadingZ([H|T], [H|T]) :-
	H =\= 0, !.
leadingZ([H|T], Res) :-
	H =:= 0,
	leadingZ(T,Res), !.

doPred(N1, N2, Res) :-
	pred(N1, N2, 0, R),
	leadingZ(R, Res).




