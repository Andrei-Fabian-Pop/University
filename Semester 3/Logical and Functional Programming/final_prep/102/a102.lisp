(defun fun (f l)
	(cond
		((null l) nil)
		(T 
		  	(
			 	(lambda (x) 
					(cond
						(x (cons x (fun f (cdr l))))
						(T nil)
					)
				) (funcall f (car l))
			)
		)
	)
)
