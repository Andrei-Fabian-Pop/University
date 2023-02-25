
(defun nrn (l k level)
	(cond
		((and (atom l) (= k level)) 1)
		((atom l) 0)
		(T (apply #'+ (mapcar #' (lambda (a) (nrn a k (+ level 1))) l)))
	)
)

(print (nrn '(a (b (g)) (c (d (e)) (f))) 3 -1))

