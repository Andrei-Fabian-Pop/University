; 3.
; a) Write a function that inserts in a linear list a given atom A after the 2nd, 4th, 6th, ... element.
; b) Write a function to get from a given list the list of all atoms, on any level, but reverse order. Example:(((A B) C) (D E)) ==> (E D C B A)
; c) Write a function that returns the greatest common divisor of all numbers in a nonlinear list.
; d) Write a function that determines the number of occurrences of a given atom in a nonlinear list.


; a)
; l = list; e = elem to replace; i = index
; insertElem(l1..ln, e, i) = {
; 	nil, l = null
; 	e + insertElem(l2..ln, e, i+1), i % 2 = 0
; 	insertElem(l2..ln, e, i+1), otherwise
; }
(defun insertElem (l e i)
    (cond
        ((null l) nil)
        ((equal (mod i 2) 0) (cons (car l) (cons e (insertElem (cdr l) e (+ i 1)))))
        (T (cons (car l) (insertElem (cdr l) e (+ i 1))))
    )
)

(defun solve (l e)
    (insertElem l e 1)
)

(defun ins (l e i pow)
	(cond
        ((null l) nil)
        ((equal i pow) (cons (car l) (cons e (ins (cdr l) e (+ i 1) (* pow 2)))))
        (T (cons (car l) (ins (cdr l) e (+ i 1) pow)))
    ) 
)

(defun solve_e (l e)
	(ins l e 1 2)
)

; puteri de al lui 2
(print (solve '(1 2 3 4 5 6 7 8) 78))
(print (solve_e '(1 2 3 4 5 6 7 8) 78))
; res = (1 2 78 3 4 78 5 6 78 7 8 78) 

(defun test_a()
	(assert
		(equal '(1 2 78 3 4 78 5 6 78 7 8 78) (solve '(1 2 3 4 5 6 7 8) 78))
	)
)

; b)
; l = list, e = elem to append
(defun myAppend (l e)
	(if (null l)
	  	e
	  	(cons (car l) (myAppend (cdr l) e))
	)
)

; l = list
; allAtoms(l1..ln) = {
; 	nil, l = null
; 	allAtoms(l2..ln) + allAtoms(l1), l1 is list
; 	allAtoms(l2..ln) + l1, otherwise
; }
(defun allAtoms (l)
	(cond
		((null l) nil)
		((listp (car l)) (myAppend (allAtoms (cdr l)) (allAtoms (car l))))
		(T (myAppend (allAtoms (cdr l)) (list (car l))))
	)
)

(print (allAtoms '(((A B) C) (D E))))

(defun test_b()
	(assert
		(equal '(E D C B A) (allAtoms '(((A B) C) (D E))))
	)
)



; c)
; myGcd(a, b) = {
; 	nil, a not number and b not number
; 	b, a not number
; 	a, b not number
; 	a, b = 0
; 	myGcd(b, a%b), otherwise
; }
(defun myGcd (a b)
	(cond
		((and (not (numberp a)) (not (numberp b))) nil)
		((not (numberp a)) b)
		((not (numberp b)) a)
		((equal b 0) a)
		(T (myGcd b (mod a b)))
	)
)

; listGcd(l1..ln) = {
; 	l1, l1 is atom and (l2..ln) is null
; 	myGcd(listGcd(l1), listGcd(l2..ln)), l1 is list
;	myGcd(l1, listGcd(l2..ln)), otherwise
; }
(defun listGcd (l)
	(cond
		((and (atom (car l)) (null (cdr l))) (car l))
		((listp (car l)) (myGcd (listGcd (car l)) (listGcd (cdr l))))
		(T (myGcd (car l) (listGcd (cdr l))))
	)
)

(print (listGcd '(24 ( 16 (12 A B)) 72)))
; res = 4

(defun test_c ()
	(assert
		(equal 4 (listGcd '(24 ( 16 (12 A B)) 72)))
	)
)

; d)
; l = list/atom; e = elem to count
; ???
(defun occ (l e)
	(cond
		; ((and (atom l) (equal l e)) 1)
		; ((atom l) 0)
		; (T (apply '+ (mapcar #'(lambda (a) (occ a e)) l)))
		((null l) 0)
		((listp (car l)) (+ (occ (car l) e) (occ (cdr l) e)))
		((and (numberp (car l)) (= (car l) e)) (+ 1 (occ (cdr l) e)))
		(T (occ (cdr l) e))
	)
)

(print (occ '(1 (3 (5 4 3) (5 3)) 3 3) 3))
; 5

(defun test_d ()
	(assert
		(equal 5 (occ '(1 (3 (5 4 3) (5 3)) 3 3) 3))
	)
)

(terpri)
(print (test_a))
(print (test_b))
(print (test_c))
(print (test_d))






