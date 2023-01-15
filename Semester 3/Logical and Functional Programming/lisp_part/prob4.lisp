; insert A after every 2n-nd element

(defun ins (l i e)
	(cond
		((null l) nil)
		((= (mod i 2) 0) (cons e (cons (car l) (ins (cdr l) (+ i 1) e))))
		(T (cons (car l) (ins (cdr l) (+ i 1) e)))
	)
)

(defun wrp (l e)
	(cdr (ins l 0 e))
)

(print (wrp '(1 2 3 4 5 6 7 8) 0))


; linerize and revert

(defun perv (l)
	(cond
		((null (car l)) nil)
        ((listp (car l)) (append (perv (cdr l)) (perv (car l))))
        (T (append (perv (cdr l)) (list (car l))))
	)
)

(print (perv '(((A B) C) (D E))))

; gcd in non-linear

(defun mygcd (e1 e2)
	(cond
	  	((null e2) e1)
		((= e2 0) e1)
		((< e1 e2) (mygcd e2 e1))
		(T (mygcd e2 (mod e1 e2)))
	)
)

(defun manevra (l)
	(cond
		((null l) nil)
		((listp (car l)) (mygcd (manevra (car l)) (manevra (cdr l))))
		(T (mygcd (car l) (manevra (cdr l))))
	)
)

; (trace manevra)
(print (manevra '(16 (32 4) 8 (16 (32 64)))))

; number of occ

(defun occ (l e)
	(cond
		((null l) 0)
		((and (atom (car l)) (= (car l) e)) (+ (occ (cdr l) e) 1))
		((listp (car l)) (+ (occ (car l) e) (occ (cdr l) e)))
		(T (occ (cdr l) e))
	)
)

(print (occ '(1 2 2 (2 3 2 (4) 2) 2) 2))


