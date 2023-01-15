; find the nth element if exists


(defun lin (l)
	(cond
	  	((null (car l)) nil)
		((listp (car l)) (append (lin (car l)) (lin (cdr l))))
		(T (cons (car l) (lin (cdr l))))
	)
)

(defun nel (l n i)
	(cond
		((> i n) nil)
	  	((listp (car l)) (nel (car l) n i))
	  	((= i n) (car l))
		(T (nel (cdr l) n (+ i 1)))
	)
)

;(print (lin '(1 2 (3 (4 5) 6) 7)))
(print (nel (lin '(1 2 (3 (4 5) 6) 7)) 6 1))


; find elem in list

(defun inlist (l e)
	(cond
		((null l) nil)
		((listp (car l)) (or (inlist (car l) e) (inlist (cdr l) e)))
		((and (atom (car l)) (equal (car l) e)) T)
		(T (inlist (cdr l) e))
	)
)

; (print (or T nil))
(print (inlist '(1 2 (3 (4 5) 6) 7) 6))



; sublists from lists

;(defun getlist (l)
;	(cond
;		((null l) nil)
;		((listp (car l)) (progn (cons (getlist (car l)) (getlist (cdr l))) (getlist (cdr l))))
;		(T (cons (car l) (getlist (cdr l))))
;	)
;)

;(defun main (l)
;	(cond
;		((null (car l)) nil)
;		((listp (car l)) (progn (cons (getlist (car l)) (main (car l))) (main (cdr l))))
;		(T (main (cdr l)))
;	)
;)

(defun main (l)
	(cond
		((null (car l)) nil)
		((listp (car l)) (append (list (car l)) (main (car l))))
		(T (main (cdr l)))
	)
)

(print (main '(1 2 (3 (4 (44 55) 5) 2 (11 21) 6) 7)))

; list to set

(defun isin (l e)
	(cond
		((null (car l)) e)
		((= e (car l)) nil)
		(T (isin (cdr l) e))
	)
)

(defun move (l)
	(cond
		((null (car l)) nil)
		(T (append (move (cdr l)) (isin (cdr l) (car l))))
	)
)

(print (move '(1 2 3 4 3 2 4 5 6)))




