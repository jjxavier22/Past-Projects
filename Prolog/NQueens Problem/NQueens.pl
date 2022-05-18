/* Jiss Xavier */

n_queens(N, Qs) :-
    length(Qs, N),
    numlist(1,N,DefaultList),
    N >= 4,
    permutation_list(DefaultList, ListOfAllPermutations),
    valid_queen(ListOfAllPermutations, Qs, []),
    !.
    /* Remove line number 10 to print all solutions for a variable such as X rather than just 1 */
    /* Even with the ! in line 10, the program finds all solutions for a board of size N */

valid_queen(_, L, L) :- !.

valid_queen([Qs|_], Qs, _) :-
    next_valid_queen(Qs, Qs, []).

valid_queen([_|Tail], Qs, _) :-
    valid_queen(Tail, Qs, []).

next_valid_queen([], L, L) :- !.
next_valid_queen([Head|Rest], Qs, ResultingList) :-
    final_valid_queen(Rest, Head, 1),
    append([ResultingList,[Head]], List),
    next_valid_queen(Rest, Qs, List).

final_valid_queen([], _, _) :- !.
final_valid_queen([NextElement|Remaining], ElementOne, DiagCount) :-
    ElementOne \= NextElement,
    abs(ElementOne - NextElement) =\= DiagCount,
    X1 is DiagCount+1,
    final_valid_queen(Remaining, ElementOne, X1).

/* https://stackoverflow.com/questions/8385423/permute-into-a-list-swi-prolog/8394843#8394843  */
permutation_list(L, ListOfAllPermutations) :-
    bagof(P, permutation(L,P), ListOfAllPermutations).

foo(L, L, []). 
foo([X | L1], L2, [X | L3])  :- foo(L1, L2, L3).
