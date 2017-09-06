;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;; 4 Op-blocks world
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

(define (domain patblock)
  (:requirements :strips)
  (:constants Z)
  (:predicates (top ?pos ?index)
               (contents ?pos ?index ?block)
               (notmaxblock ?index)
	       (notzero ?index)
	       (notequal ?a ?b)
	       (index ?index)
               (position ?pos)
               (block ?block)
	       (lower ?index1 ?index2)
               (higher ?index1 ?index2)
	       )

(:action move
  :parameters (?pos1 ?pos2 ?block ?index1 ?index2 ?newindex1 ?newindex2)
  :precondition (and
		    (position ?pos1) (position ?pos2) (block ?block) 
		    (index ?index1) (index ?index2) (index ?newindex1) (index ?newindex2) 

		    (top ?pos1 ?index1) (notzero ?index1) (contents ?pos1 ?index1 ?block)

		    (top ?pos2 ?index2) (notmaxblock ?index2)

		    (lower ?index1 ?newindex1) 
		    (higher ?index2 ?newindex2) 
		    (lower ?newindex2 ?index2)

		    (contents ?pos2 ?newindex2 Z)
		    (notequal ?pos1 ?pos2)
	      )
	     :effect
	     (and (not (top ?pos1 ?index1))
 	     	  (top ?pos1 ?newindex1)
		  (not (contents ?pos1 ?index1 ?block))
                  (contents ?pos1 ?index1 Z)
		  (not (top ?pos2 ?index2))
		  (top ?pos2 ?newindex2)
		  (not (contents ?pos2 ?newindex2 Z))
		  (contents ?pos2 ?newindex2 ?block))))


