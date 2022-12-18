; Write recursive Lisp functions for the following problems (optionally, you may use MAP functions):
; A binary tree is memorised in the following two ways:
; (node no-subtrees list-subtree-1 list-subtree-2 ...) (1)
; (node (list-subtree-1) (list-subtree-2) ...) (2)
; As an example, the tree
;  A
; / \
; B C
;  / \
;  D E
; is represented as follows:
; (A 2 B 0 C 2 D 0 E 0) (1)
; (A (B) (C (D) (E))) (2)
; Except for problems 4 and 9, conversion between types is not allowed; a direct method should be
; used instead.
 
; 1. For a given tree of type (1) return the path from the root node to a certain given node X.

; v = vertices; e = edges
; traverse_left(l1..ln, v, e) = {
; 	nil, l is null
; 	nil, v = e+1
; 	l1 + l2 + traverse_left(l3, v+1, e+l2), otherwise
; }
(defun traverse_left(tree v e)
	(cond
		((null tree) nil)
		((= v (+ e 1)) nil)
		(T (cons (car tree) (cons (cadr tree) (traverse_left (cddr tree) (+ v 1) (+ (cadr tree) e)))))
	)
)

(defun left(tree)
	(traverse_left (cddr tree) 0 0)
)
; (print (left '(a 2 b 1 bb 0 c 2 d 0 e 0)))
; => (B 1 BB 0)


; v = vertices; e = edges
; traverse_right(l1..ln, v, e) = {
; 	nil, l is null
;	l, v = e+1
;	traverse_right(l3,v+1,e+l2), otherwise
; }
(defun traverse_right(tree v e)
    (cond
        ((null tree) nil)
        ((= v (+ e 1)) tree)
        (T (traverse_right (cddr tree) (+ v 1) (+ (cadr tree) e)))
    )   
)

(defun right(tree)
    (traverse_right (cddr tree) 0 0)
)

; (print (right '(a 2 b 1 bb 0 c 2 d 0 e 0)))
; => (C 2 D 0 E 0)

; manevra(l1..ln, e) = {
; 	nil, tree is null
; 	true, l1 = e
; 	manevra(left(l1..ln), e) or manevra(right(l1..ln), e), otherwise
; } 
(defun manevra(tree e)
  	; (print e)
  	; (print tree)
	(cond
		((null tree) nil)
		((equal (car tree) e) T)
		(T (or (manevra (left tree) e) (manevra (right tree) e)))
	)
)

; solve(l1..ln, e) = {
; 	nil, l is null
; 	e, l1 = e
; 	l1 + solve(left(l), e), manevra(left(l), e)
; 	l1 + solve(right(l), e), manevra(right(l), e)
; }
(defun solve(tree e)
	(cond
		((null tree) nil)
		((equal (car tree) e) (list e))
		((manevra (left tree) e) (cons (car tree) (solve (left tree) e)))
		((manevra (right tree) e) (cons (car tree) (solve (right tree) e)))
	)
)

; (trace manevra)
; (manevra '(a 2 b 1 bb 0 c 2 d 0 e 0) 'd 0)
; (print (manevra '(a 2 b 1 bb 0 c 2 d 0 e 0) )

(print (solve '(a 2 b 1 bb 0 c 2 d 0 e 0) 'd))


(defun test_a()
	(assert
		(equal '(A C D) (solve '(a 2 b 1 bb 0 c 2 d 0 e 0) 'd))
	)
)

(test_a)




