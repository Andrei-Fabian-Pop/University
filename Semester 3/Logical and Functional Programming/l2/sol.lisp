; Solve the following problems using MAP functions.
;
; 16.Write a function that produces the linear list of all atoms of a given list, from all levels, and written in the same order.
; Eg.: (((A B) C) (D E)) --> (A B C D E)

(defun myAppend (l p)
  (cond
    ((null l) p)
    (t (cons (car l) (myAppend (cdr l) p)))
  )
)

(defun myAppendList(l)
  (cond
    ((null l) nil)
    (t (myAppend (car l) (myAppendList (cdr l))))
  )
)

(defun reverseAppend (l p)
  	(cond
	  	((null p) l)
		(T (cons p l))
	)
)

(defun reverseAppendList(l)
  (cond
    ((null l) nil)
    (t (reverseAppend (car l) (reverseAppendList (cdr l))))
  )
)

(defun extra(l)
  (cond
    ((atom l) (list l))
    (t (apply #'reverseAppendList (list (mapcar #'extra l))))
  )
)

(defun bonus(l)
	(lin (extra l))
)

; (print (reverseAppend '(1 2 3 4) 0))
;(defun reverseAppendList (l)
;)

; (print (myAppendList '((A C) (B D))))
; myLinearize(l) = 
; = (list l), if l is an atom
; = myAppendList(myLinearize(l1), myLinearize(l2), ..., myLinearize(ln)), otherwise where l is a list of the type l = l1l2...ln
(defun lin(l)
  (cond 
    ((atom l) (list l))
    (t (apply #'myAppendList (list (mapcar #'lin l))))
  )
)

; (print (bonus '(1 2 3 (4 5 (6) 7) 8)))

(defun test()
    (assert
        (and
            (equal '(nil) (lin '()))
            (equal '(1 2 3 4 5 6 7 8) (lin '(1 2 3 (4 5 (6) 7) 8)))
            (equal '(1 1 2 2 A 2 B 1 2) (lin '(1 (1 2 (2 (A 2 B) 1) 2))))
        )
    )
)

(defun change()
    (assert
        (and
            (equal '(nil) (bonus '()))
            (equal '(8 7 6 5 4 3 2 1) (bonus '(1 2 3 (4 5 (6) 7) 8)))
            (equal '(2 1 B 2 A 2 2 1 1) (bonus '(1 (1 2 (2 (A 2 B) 1) 2))))
        )
    )
)

(change)
(test)

