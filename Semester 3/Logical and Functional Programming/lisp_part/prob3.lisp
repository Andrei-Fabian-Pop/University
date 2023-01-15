; dot product of 2 vectors
(defun dotp (l1 l2)
	(cond
		((and (null l1) (null l2)) nil)
		((null (car l1)) l2)
		((null (car l2)) l1)
		(T (cons (* (car l1) (car l2)) (dotp (cdr l1) (cdr l2))))
	)
)

(print (dotp '(1 2 3 4 5 6 7) '(2 2 3 3)))


; depth
(defun depth (l)
	(cond
		((null l) 1)
		((listp (car l)) (max (+ (depth (car l)) 1) (depth (cdr l))))
		(T (depth (cdr l)))
	)
)

(print (depth '(1 2 (3 4 (5 6) (7 (8))) 9)))
; (trace depth)
; (depth '(1 2 (3 4 (5 6) (7 (8))) 9))


; sort linear list
(defun aux (l e)
	(cond
	  	((null l) (list e))
		((= e (car l)) l)
		((< e (car l)) (cons e l))
		(T (cons (car l) (aux (cdr l) e)))
	)
)

; (print (aux '(6 5 3 2 1) 4))
; (print (aux '(4) 7))

(defun srt (l)
	(cond
		((null l) nil)
		(T (aux (srt (cdr l)) (car l)))
	)	
)

; (trace srt)
(print (srt '(8 56 8 0 7 5 3 3)))


; intersection of 2 sets
(defun check (l e)
	(cond
		((null l) (list e))
		((= e (car l)) l)
		(T (cons (car l) (check (cdr l) e)))
	)
)

(defun inter (l1 l2)
	(cond
		((null l2) l1)
		(T (inter (check l1 (car l2)) (cdr l2)))
	)
)

(print (inter '(1 2 3 4 5) '(2 6 7 5 3)))

