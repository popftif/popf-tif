(define (domain t3)
; Test case provided by Ashutosh Verma (avermaa at gmail dot com)

  (:requirements :durative-actions :numeric-fluents :duration-inequalities)

  (:predicates (started) (five-done) (five-started) (six-done) (seven-done) (not-started) )
  (:functions (utime) (total-duration) (endtime))

  ;; ## UCLOCK ###########
  (:durative-action uclock
  	:parameters()
  	:duration (= ?duration (total-duration))
  	:condition (at start (not-started))
  	:effect ( and 
  		(increase (utime) (* #t (* 1 1)))
  		(at start (not(not-started)))
  		(at start (started))
  	)  
  )
  ;;end of UCLOCK

  ;; ## FIVE ###########
  (:durative-action five
  	:parameters()
    :duration (= ?duration 10)
  	:condition (and 
  		(at start( = (utime) 5))
  		(at start (started))
  	)
  	:effect ( and
  		(at start (five-started))
  		(at end (five-done)) 
  		(at start (assign (endtime) (utime)))
  	)
  )
  ;;end of FIVE
  
    ;; ## SIX ###########
  (:durative-action six
  	:parameters()
    :duration (= ?duration 10)
  	:condition (and 
  		(at start (five-started))
  		(at start (= (- utime endtime) 1))
  	)
  	:effect (at end(six-done))
  )
  ;;end of SIX

)
;; end of domain
 
  
