add(E,[],[E]).

add(E,[H|T],[H|Rez]):-
  add(E,T,Rez).

invers([],[]).

invers([H|T],Rez) :-
  invers(T,L), 
  add(H,L,Rez).
