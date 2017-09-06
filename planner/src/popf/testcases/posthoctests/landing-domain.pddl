(define (domain landing)                 
(:requirements :typing :fluents :durative-actions :duration-inequalities)

(:types plane runway)

(:predicates (free ?r - runway)
             (scheduled ?p - plane ?r - runway)
             (occupied ?r - runway)            
             (landed ?p - plane)               
             (takeOff)                         
             (flying ?p - plane)               
             (ready)                           
)                                              

(:functions (target ?p - plane)
            (earliest ?p - plane)
            (latest ?p - plane)  
            (latePenaltyRate ?p - plane)
            (latePenalty ?p - plane)    
            (earlyPenaltyRate ?p - plane)
            (total-cost)                 
            (fake-duration)              
)                                        

(:durative-action releasePlanes
 :parameters ()                
 :duration (= ?duration 1)  
 :condition (and (at start (ready)))
 :effect (and (at start (takeOff))  
              (at start (not (ready)))
              (at end (not (takeOff)))))

(:durative-action schedule
 :parameters (?p - plane ?r - runway)
 :duration (= ?duration 2)
 :condition (and (over all (flying ?p))
                 (at start (free ?r)))
 :effect (and (at end (scheduled ?p ?r))
              (at start (occupied ?r))
              (at start (not (free ?r)))))

(:durative-action clear
 :parameters (?p - plane ?r - runway)
 :duration (= ?duration 2)
 :condition (and (at start (landed ?p))
                 (at start (scheduled ?p ?r))
                 (over all (occupied ?r)))
 :effect (and (at end (free ?r))
              (at end (not (occupied ?r)))
              (at end (not (scheduled ?p ?r)))))

(:durative-action land
 :parameters (?p - plane ?r - runway)
 :duration (and (>= ?duration (earliest ?p)) (<= ?duration (latest ?p)))
 :condition (and (at start (takeOff))
                 (over all (flying ?p))
                 (at end (scheduled ?p ?r)))
 :effect (and (at start (flying ?p))
              (at end (landed ?p))
              (at end (not (flying ?p)))
              (when (at end (<= (fake-duration) (target ?p)))

                (at end (increase (total-cost) (* (earlyPenaltyRate ?p) (- (target ?p) ?duration)))))

              (when (at end (> (fake-duration) (target ?p)))
                (at end (increase (total-cost) (+ (latePenalty ?p) (* (latePenaltyRate ?p) (- ?duration (target ?p)))))))
  )
)
)

