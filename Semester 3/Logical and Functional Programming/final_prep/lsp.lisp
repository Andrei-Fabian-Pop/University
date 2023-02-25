(defun f(l1 l2)
	(append (f (car l1) l2)
		(cond 
			((null l1) l2)
			(T (list (f (car l1) l2) (car l2)))
		)
	)
)

(trace f)
(print (f '((1)) '((4))))
