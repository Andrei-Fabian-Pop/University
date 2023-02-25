
; (1 s 4 (2 f (7))) => (1 s 5 (3 f (7)))

(defun f(l)
	(cond
		((and (numberp l) (= (mod l 2) 0)) (+ l 1))
		((atom l) l)
		(T (mapcar #' f l))
	)
)

(print (f '(1 s 4 (2 f (7)))))

