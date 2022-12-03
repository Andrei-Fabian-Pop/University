% test time
% Given a numerical linear list, delete all sequences (with at least two elements) of
% consecutive numbers.

% (i,o), (i,i)
remConsecutive([], []) :- !.
remConsecutive([E], [E]) :- !.
remConsecutive([H1, H2], []) :- H2 =:= H1 + 1, !.
remConsecutive([H1, H2], [H1, H2]) :- H2 =\= H1 + 1, !.
remConsecutive([H1, H2, H3|T], R) :- 
    H2 =:= H1 + 1,
    H3 =:= H2 + 1,
    remConsecutive([H2, H3|T], R), !.
remConsecutive([H1, H2, H3|T], R) :- 
    H2 =:= H1 + 1,
    H3 =\= H2 + 1,
    remConsecutive([H3|T], R), !.
remConsecutive([H1, H2, H3|T], [H1|R]) :- 
    H2 =\= H1 + 1,
    remConsecutive([H2,H3|T], R), !.

test() :-
	remConsecutive([1,2,4,6,7,8,10], [4,10]),
	remConsecutive([1,2,3,4,5], []),
	remConsecutive([1,3,5,7], [1,3,5,7]),
	remConsecutive([1,2,5,6,7,8,4,6,7,8,9], [4]).
