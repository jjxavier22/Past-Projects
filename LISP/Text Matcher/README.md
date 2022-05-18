We say an assertion is a list of strings such as (apple banana) (no quotations). A pattern is a list of atoms that may contain the special symbols ! and *.

The special symbol ! means matching zero or more atoms.
For example, the pattern (apple ! blueberry) and the assertion (apple banana orange blueberry) match.

The special symbol * means matching zero or more characters inside an atom.
For example, the pattern (apple bl*rry) and the assertion (apple blueberry) match.

It is important to note an assertion cannot contain the special symbols ! and *.

The program match.lisp will evaluate a given pattern and an asseration to see whether they match. The function returns true (t in Lisp) when they match and returns false (nil in Lisp) otherwise.
