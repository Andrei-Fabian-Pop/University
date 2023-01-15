; erase all list with an even number of elements from a non-lineary list
; e.g. ((2 3 4) (6 (7 8) ((7 9) 8)) (6 8) 9) --> ((2 3 4) (6 (8)) 9)

(defun ers (l i)
	(cond
		((listp (car l)) (if (= (mod (ers (car l)) 2) 1) (cons l (ers (cdr l) 0)) (ers (cdr l) 0)))
		; if ers(l i)%2==1 then l + ers (l2 0) else ers(l2 0)
	)
)

(defun main (l)
	(ers l 0)
)

