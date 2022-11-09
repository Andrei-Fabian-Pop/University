% 11
%
% a. Replace all occurrences of an element from a list with another element e.
%
% replaceElem([1,2,3,4,3,3],3,0,Res).

% (i,i,i,o)
%
% replaceElem(l1...ln, e1, e2) =
% 	[], n = 0
% 	e2 + replaceElem(l2...ln, e1, e2), l1 = e1
% 	l1 + replaceElem(l2...ln, e1, e2), otherwise
%

replaceElem([], _, _, []).
replaceElem([H|T], E1, E2, [E2|R]) :-
	H =:= E1, 
	!,
	replaceElem(T, E1, E2, R).
replaceElem([H|T], E1, E2, [H|R]) :-
	replaceElem(T, E1, E2, R).

testReplaceElem() :-
	replaceElem([1,2,3,4,3,3],3,0,[1, 2, 0, 4, 0, 0]),
	replaceElem([1,1,1,1],1,99,[99,99,99,99]).
