;(defun triple (l)
;	(cond
;		((null l) nil)
;		(T (cons (* 3 (car l)) (triple (cdr l))))
;	)
;)
(DEFUN triple (x)
	(COND
	 	((numberp x) (* x 3))
		((atom x) x)
		(t (mapcar #'triple x))
	)
)

(print (triple '(1 2 3)))

(print (mapcar #'triple '(1 2 3)))
(print (mapList #'triple '(1 2 3)))
(print (mapcan #'triple '(1 3 2)))
(print (mapcon #'triple '(1 2 3)))
