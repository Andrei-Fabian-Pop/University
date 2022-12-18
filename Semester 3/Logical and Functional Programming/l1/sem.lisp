(defun getList(l n)
	(cond
	  	((null l) nil)
		((= n 0) nil)
		((numberp (car l)) (cons (car l) (getList (cdr l) (- n 1))))
		((listp (car l)) (getList (car l) n))
		(T (getList (cdr l) n))
	)
)

(defun sum(l)
  	(cond
		((null l) 0)
		(+ (car l) (sum (cdr l)))
	)
)

(defun main(l n)
	(sum (getList l n))
)

(print (getList '(a 1 (2 b (c 3) 4 5 6 d) 7) 5))
