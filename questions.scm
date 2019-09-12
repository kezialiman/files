(define (caar x) (car (car x)))
(define (cadr x) (car (cdr x)))
(define (cdar x) (cdr (car x)))
(define (cddr x) (cdr (cdr x)))



;; Problem 17
;; Returns a list of two-element lists
(define (enumerate s)
  ; BEGIN PROBLEM 17
  (define (helper index lst)
        (if (null? lst) 
            ()
            (cons (list index (car lst)) (helper (+ index 1) (cdr lst)))
        )
  )
    
  (helper 0 s)
)
  ; END PROBLEM 17

;; Problem 18

(define (zip pairs)
  ; BEGIN PROBLEM 18
  (define (helper1 lst)
        (if (null? lst)
            ()
            (cons (car(car lst)) (helper1 (cdr lst)))
        )
    )
    
    (define (helper2 lst)
        (if (null? lst)
            ()
            (cons (car (cdr (car lst))) (helper2 (cdr lst)))
        )
    )
    
    (list (helper1 pairs) (helper2 pairs))  
)
  ; END PROBLEM 18


;; Problem 19
;; Returns a function that checks if an expression is the special form FORM
(define (check-special form)
  (lambda (expr) (equal? form (car expr))))

(define lambda? (check-special 'lambda))
(define define? (check-special 'define))
(define quoted? (check-special 'quote))
(define let?    (check-special 'let))

;; Converts all let special forms in EXPR into equivalent forms using lambda
(define (let-to-lambda expr)
  (cond ((atom? expr)
         ; BEGIN PROBLEM 19
         expr
         ; END PROBLEM 19
         )
        ((quoted? expr)
         ; BEGIN PROBLEM 19
          expr
         ; END PROBLEM 19
         )
        ((or (lambda? expr)
             (define? expr))
         (let ((form   (car expr))
               (params (cadr expr))
               (body   (cddr expr)))
           ; BEGIN PROBLEM 19
              (append '(lambda) (list params) (map let-to-lambda body))
           ))
        ((let? expr)
         (let ((values (cadr expr))
               (body   (cddr expr)))
           ; BEGIN PROBLEM 19
            (append (list(append '(lambda) (list (map let-to-lambda (car (zip values)))) (map let-to-lambda body))) 
              (map let-to-lambda (car(cdr (zip values)))))
           ; END PROBLEM 19
           ))
        (else
         ; BEGIN PROBLEM 19
         (map let-to-lambda expr)
         ; END PROBLEM 19
         )))



