(defun inv (l)
	(cond
		((null l) nil)
		;((listp (car l)) (cons (inv (cdr l)) (inv (car l))))
		((atom (car l)) (append (inv (cdr l)) (list (car l))))
		(T (cons (inv (car l)) (inv (cdr l))))
	)
)

;(trace inv)
(print (inv '(A B C (D (E F) G H I))))
(print (inv '(A B C D E F)))
;(print (inv '(A (B C) D E (F (G)))))
;(print (inv '(A (B (C (D) E) F) G)))


(defun test ()
  	(or
		(equal (inv '(A B C (D (E F) G H I))) '(C B A (D (F E) I H G)))
	(equal (inv '(A B C D E F)) '(F E D C B A))
	(equal (inv '(A (B C) D E (F (G)))) '(A (C B) E D (F(G))))
	(equal (inv '(A (B (C (D) E) F) G)) '(A (B (C (D) E) F) G))
	)
	)

(print (test))
