(define (domain power)

	(:requirements :adl :typing :fluents :durative-actions)

	(:types msc transformer time volts turnvalue demandchange circuit circuitcount)

	(:predicates

	(before ?t1 - time ?t2 - time)
	(timenow ?t1 - time)
	(canadvanceto ?t1 - time)
	(canstartclip ?t - time)
        (canhalfhour)
	(canstep)
	(on ?m - msc)
	(off ?m - msc)
	(mscconnectedto ?m - msc ?c - circuit)
	(demand ?t - time ?n - turnvalue)
	(timeup ?t - time)
	(transformerconnectedto ?t - transformer ?c - circuit)
	(donehalfhour ?t - time)
	(transformerused)
	(mscused)
	(clipfree)
	(canswitch)
	)

	(:functions

		(numberofturns ?t - transformer)
		(voltage ?c - circuit)
		(planmetric)
		(extra-metric)
		(value ?n - turnvalue)
		(absolutevalue ?n - turnvalue)
		(maxturns)
		(demandvalue)

	)

	(:durative-action switch_on_msc
         	:parameters(?m - msc ?c - circuit)
		:duration(= ?duration 0.1)
		:condition (and
                                (at start (off ?m))
				(at start (mscconnectedto ?m ?c))
				(over all (canstep))
				(over all (canswitch))
		)
		:effect ( and
				(at end (on ?m))
				(at end (increase (voltage ?c) 0.02))
				(at start (not (off ?m)))
				(at end (increase (planmetric) 0.1))
			)

	)

	(:durative-action switch_off_msc
		:parameters(?m - msc ?c - circuit)
		:duration(= ?duration 0.1)
		:condition (and
				(at start (on ?m))
				(at start (mscconnectedto ?m ?c))
				(over all (canstep))
				(over all (canswitch))
		)
		:effect ( and
				(at end (off ?m))
				(at start (not (on ?m)))
				(at end (decrease (voltage ?c) 0.02 ))
				(at end (increase (planmetric) 0.1))
			)

	)

	;action to increase the voltage using the transformer
	(:durative-action transformer_step
		:parameters(?trans - transformer ?n1 - turnvalue ?c - circuit)
		:duration(= ?duration (* 0.1 (absolutevalue ?n1)))
		:condition (and 
				(at start (<= (+ (numberofturns ?trans) (value ?n1)) (maxturns)))
				(at start (>= (+ (numberofturns ?trans) (value ?n1)) 0))
				(at start (transformerconnectedto ?trans ?c))
				(over all (canstep))
				(over all (canswitch))
		)
		:effect ( and 
				(at end (increase (numberofturns ?trans) (value ?n1)))
				;(increase (voltage ?c) (* 0.0067 (value ?n1)))
				(at end (increase (voltage ?c) (* 0.008 (value ?n1))))
				(at end (increase (planmetric) (* 0.1 (absolutevalue ?n1))))
				;(when (at end (< (voltage ?c) 0.97)) (at end (increase (extra-metric) 0.1)))
				(at end (increase (extra-metric) (- (voltage ?c) 0.95)))
		)
	)


	(:durative-action next_half_hour
		:parameters(?c - circuit ?t1 - time ?t2 - time ?n3 - turnvalue)
		:duration(= ?duration 30)
		:condition (and
				(at start (canadvanceto ?t2))
				(at start (before ?t1 ?t2))
				(at start (demand ?t2 ?n3))
                                (at start (canhalfhour))
				(over all (>= (voltage ?c) 0.95))
				(over all (<= (voltage ?c) 1.05))
		)
		:effect ( and
				(at start (canswitch))
				(at end   (not (canswitch)))
				(at start (canstartclip ?t2))
				(at start (not (canadvanceto ?t2)))
				(at start (timenow ?t2))
				(at start (not (timenow ?t1)))
				(at start (canstep))
                                (at start (not (canhalfhour)))
                                (at end (canhalfhour))
                                (at end (donehalfhour ?t2))
				; divide by 30 and multiply by 0.01
				(increase (voltage ?c) ( * #t  (/ (value ?n3) 3000)) )
				(increase (demandvalue) ( * #t (* 14 (/ (value ?n3) 30)) ) )

			)

	)

	(:durative-action clip
		:parameters(?c - circuit ?t1 - time ?t2 - time)
		:duration(= ?duration 0.1)
		:condition (and
				(at start (clipfree))
				(at start (canstep))
				(at start (timenow ?t1))
				(at start (before ?t1 ?t2))
				(at start (canstartclip ?t1))
                                (at end (donehalfhour ?t1))
		)
		:effect ( and
				(at start (not (clipfree)))
				(at end (clipfree))
				(at start (not (canstep)))
				(at start (not (canstartclip ?t1)))
        			(at start (canadvanceto ?t2))
;			        (at start (not (donehalfhour)))
;				(at end (canstartclip))
				(at end (canstep))
				(at end (not (canadvanceto ?t2)))
			)

	)

)
