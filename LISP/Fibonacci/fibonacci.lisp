;Jiss Xavier


(defun nth-fib (n)
	(if (<= n 1)
		n
		(+ (nth-fib (- n 1)) (nth-fib (- n 2)))))



(defun fib (n)
	(let ((x1 1))
	(let ((x2 1))
	(let ((next 0))
	(let ((counter 1))
	(let ((lis1 (list 0)))
	(if (< n 1)
		NIL
		(if (= n 1)
			lis1
			(fib-helper (- n 1) x1 x2 next counter lis1))))))))
)

(defun fib-helper (n x1 x2 next counter lis1)
	;https://stackoverflow.com/questions/13359025/adding-to-the-end-of-list-in-lisp
	(push x1 (cdr (last lis1)))
	(let ((next (+ x1 x2)))
	(let ((x1 x2))
	(let ((x2 next))
	(let ((counter (+ counter 1)))
	(if (> counter n)
		lis1
        (fib-helper n x1 x2 next counter lis1))
	))))
)

(defun fib-lt (n)
	(let ((x1 1))
	(let ((x2 1))
	(let ((next 0))
	(let ((counter 1))
	(let ((lis1 (list 0)))
	(if (< n 1)
		NIL
		(if (= n 1)
			lis1
			(fib-lt-helper n x1 x2 next counter lis1))))))))
)


(defun fib-lt-helper (n x1 x2 next counter lis1)
	;https://stackoverflow.com/questions/13359025/adding-to-the-end-of-list-in-lisp
	(push x1 (cdr (last lis1)))
	(let ((next (+ x1 x2)))
	(let ((x1 x2))
	(let ((x2 next))
	(let ((counter (+ counter 1)))
	(if (>= x1 n)
		lis1
        (fib-lt-helper n x1 x2 next counter lis1))
	))))
)

;Provided Test Cases
(print(nth-fib 9))
(print(fib 9))
(print(fib-lt 100))























