/* Jiss Xavier */

/* Concatenation

Base Case: If list1 is empty, then all of list2 will be put into the resulting list
Recursion: When list1 is not empty, the heads of list1 will be added to the resulting list as the recursion returns after the base case is met*/

my_concat([],L,L) :- !.
my_concat([Head|L1],L2,[Head|ResultingList]) :- 
    my_concat(L1,L2,ResultingList).

/* Element At

Base Case: The element you are looking at matches the value at the index and the count and index are equal.
Recursive Case: If count doesn't = index, increment count and run helper_element_at on the Tail.

(T) my_element_at(2, 1, [2, 3, 4]).
(F) my_element_at(2, 1, [3, 2, 4]).
(F) my_element_at(2, 1, [[2], 3, 4]).
(F) my_element_at(5, 2, [3, 2, 4]).
(4) my_element_at(X, 3, [3, 2, 4]).
(1) my_element_at(3, N, [3, 2, 4]).
(F) my_element_at(X, 4, [3, 2, 4]).
(F) my_element_at(2, 1, [1, 2, [3, 4, 5], 6, 7, 8]).
(T) my_element_at(2, 2, [1, 2, [3, 4, 5], 6, 7, 8]).
([3,4,5]) my_element_at(X, 3, [1, 2, [3, 4, 5], 6, 7, 8]).
(T) my_element_at([3, 4, 5], 3, [1, 2, [3, 4, 5], 6, 7, 8]).
(3) my_element_at([3, 4, 5], N, [1, 2, [3, 4, 5], 6, 7, 8]).
(F) my_element_at(3, N, [1, 2, [3, 4, 5], 6, 7, 8]).
*/

my_element_at(X, N, L) :- helper_element_at(X, N, 1, L).
helper_element_at(X, N, N, [X|_]) :- !.
helper_element_at(X, Index, Count, [_|Tail]) :- 
    NextCount is Count + 1,
    helper_element_at(X, Index, NextCount, Tail).

 
/* Reverse

Base Case: Recursion stops when the original list being reversed is empty and L2 and ResultingList match.
Recursive Case: Takes the head of the L1 and prepends into ResultingListing until L1 is empty and L2 and ResultingList match then puts L1 back as it was.
(Works in both directions)

(T) my_reverse([1,2,3], [3,2,1]).
(F) my_reverse([1,2,3], [2,1,3]).
(T) my_reverse([1,[2,3],4,[5]], [[5],4,[2,3],1]).
(F) my_reverse([1,[2,3],4,[5]], [[5],4,[3,2],1]).
(T) my_reverse([], []).
([5], 4, [2, 3], 1) my_reverse([1,[2,3],4,[5]], X).
([5], 4, [2, 3], 1) my_reverse(X, [1,[2,3],4,[5]]).

*/

my_reverse(L1, L2) :- helper_reverse(L1, L2, []).
helper_reverse([], L2, L2) :- !.
helper_reverse([Head|Tail], L2, ResultingList):-
        helper_reverse(Tail, L2, [Head|ResultingList]).


/* Flatten

Base Case: When both lists are empty
Recursive Case: Opens list until elements are no longer nested then appends them together and puts the result in FlattenedList.

(T) my_flatten([1, 2, 3], [1, 2, 3]).
(T) my_flatten([1, [2, 3]], [1, 2, 3]).
(T) my_flatten([1, [2], [3, 4]], [1, 2, 3, 4]).
(T) my_flatten([1, [2, 3, [4, 5], 6]], [1, 2, 3, 4, 5, 6]).
([1, 2, 3, 4, 5, 6]) my_flatten([1, [2, 3, [4, 5], 6]], X).
my_flatten([1, [a, b, c], [2, 3, [4, 5], 6]], X).

*/

my_flatten(L1, L2) :- helper_flatten(L1, L2, 0).
helper_flatten([], [], 0) :- !.
helper_flatten([Head|Tail], FlattenedList, 0) :-
    !,
    helper_flatten(Head, NextFlattenedHead, 0),
    helper_flatten(Tail, NextFlattenedTail, 0),
    append(NextFlattenedHead, NextFlattenedTail, FlattenedList).
helper_flatten(Head, [Head], 0).



/* Compress

Base Case: Recursion stops when the compressed list generated is the same as L2
Recursive Case: Checks if the value at the head of L1 has already been discovered.
    If it hasn't it is appended to the ResultingList
    If it has the element is skipped and the recurrsion continues from the next element.

(T) my_compress([1, 2, 3], [1, 2, 3]).
(T) my_compress([1, 2, 2], [1, 2]).
(F) my_compress([1, 2, [2]], [1, 2]).
(T) my_compress([1, 2, [3, 4], [5], [5], [3]], [1, 2, [3, 4], [5], [3]]).
([1, 2, 3]) my_compress([1, 2, 3, 3, 2, 1], X).
*/

my_compress(L1, L2) :- helper_compress(L1, L2, []).
helper_compress([], L2, L2) :- !.

helper_compress([Head|Tail], L2, ResultingList):-
    not(member(Head, ResultingList)),
    append([ResultingList,[Head]], List),
    !,
    helper_compress(Tail, L2, List). 

helper_compress([Head|Tail], L2, ResultingList):-
    member(Head, ResultingList),
    !,
    helper_compress(Tail, L2, ResultingList). 