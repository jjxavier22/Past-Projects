;Jiss Xavier



(defun match (pattern match)

	;base case to exit for atoms
	(if (= 0 (length match))
		(if (= 0 (length pattern)) 
			(return-from match t)
		)
	)

	;base case to exit for atoms
	(if (= 0 (length pattern))
		(if (= 0 (length match)) 
			(return-from match t)
		)
	)

	;Dealing with '!'
	(if(string= (first pattern) "!")
		(cond 
			((= 1 (length pattern))
				(return-from match t)
			)

			((= 0 (length match))
				(return-from match (match (cdr pattern) match))
			)

			((string= (second pattern) "!")
				(return-from match (match (cdr pattern) match))
			)

			((string= (second pattern) "*")
				(return-from match (match (cdr pattern) match))
			)

			((and (string= (second pattern) (first match)) (string= (second pattern) (second match)))
				(return-from match (match pattern (cdr match)))
			)

			((string/= (second pattern) (first match))
				(return-from match (match pattern (cdr match)))
			)

			(t (or (return-from match (match (cdr pattern) match))
				(return-from match (match pattern (cdr match)))
				))
		)
	)

	;Edge case of * without an atom to consume
	(if (string= (first pattern) "*")
		(if (= 0 (length match))
			(return-from match NIL)
		)
	)

	;Goes through an atom char by char
	(if(char-helper (string (first pattern)) (string (first match)))
		(match (cdr pattern) (cdr match))
		(return-from match NIL)
	) 
)


;function to process individual atoms
(defun char-helper (pattern match)

	;base case to exit
	(if (= 0 (length match))
		(if (= 0 (length pattern)) 
			(return-from char-helper t)
		)
	)

	;base case to exit
	(if (= 0 (length pattern))
		(if (= 0 (length match)) 
			(return-from char-helper t)
		)
	)

	(if (= 0 (length pattern))
		(return-from char-helper NIL)
	)

	(if (char= (char pattern 0) #\!)
		(return-from char-helper NIL)
	)

	;Deals with '*'
	(if (char= (char pattern 0) #\*)

		(cond 
			((= 1 (length pattern))
				(return-from char-helper t)
			)

			((= 0 (length match))
				(return-from char-helper (char-helper (subseq pattern 1) match))
			)

			((char= (char pattern 1) #\* )
				(return-from char-helper (char-helper (subseq pattern 1) match))
			)

			((char= (char pattern 1) #\! )
				(return-from char-helper NIL)
			)

			((char/= (char pattern 1) (char match 0))
				(return-from char-helper (char-helper pattern (subseq match 1)))
			)

			;((and (char= (char pattern 1) (char match 0)) (char= (char pattern 1) (char match 1)))
				;(print "char anamoly")
				;(return-from char-helper (char-helper pattern (subseq match 1)))
			;)

			(t (or (return-from char-helper (char-helper (subseq pattern 1) match))
				(return-from char-helper (char-helper pattern (subseq match 1)))
				))
		)
	)

	(if (= 0 (length match))
		(return-from char-helper NIL)
	)

	;checks char by char for match or no match
	(if (char= (char pattern 0) (char match 0))	
		(char-helper (subseq pattern 1) (subseq match 1))
		(return-from char-helper NIL)
	)
	
)


;Simple Match Sample Test Cases (NIL)
;(print (match '(apple2) '(apple2 banana)))
;(print (match '(apple2 banana) '(apple2)))
;(print (match '(apple2 banana) '(banana apple2)))
;(print (match '(banana apple2) '(apple2 banana)))

;Simple Match Sample Test Cases (T)
;(print (match '(apple2) '(apple2)))
;(print (match '(apple2 banana) '(apple2 banana)))

;* at the end
;(print (match '(color apple *) '(color apple red)))

;Provided Test Cases for Simple Match
(print (match '(color apple red) '(color apple red)))
(print (match '(color apple red) '(color apple green)))

;*Provided Test Cases for !
(print (match '(! table !) '(this table supports a block)))
(print (match '(this table !) '(this table supports a block)))
(print (match '(! brown) '(green red brown yellow)))
(print (match '(! brown) '(green red brown brown)))
(print (match '(red green ! blue) '(red green blue)))

;* Provided Test Cases for *
(print (match '(red gr*n blue) '(red green blue)))
(print (match '(t* table is *n) '(this table is blue)))
(print (match '(color apple *) '(color apple red)))
(print (match '(color * red) '(color apple red)))
(print (match '(color * red) '(color apple green)))
(print (match '(color*red) '(color apple red)))

;Provided test case for combination of '!' and '*'
(print (match '(color ! * red) '(color apple red)))

;(print (match '(! !) '()))
;(print (match '(* *) '()))
;(print (match '(color red *) '(color red)))
;(print (match '(color *! red) '(color red)))
;(print (match '(color !* red) '(color red)))
;(print (match '(apple ! blueberry) '(apple banana orange blueberry)))

