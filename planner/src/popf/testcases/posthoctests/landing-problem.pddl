(define (problem KLM)
	(:domain landing)
	(:objects  UA938_CHICAGO CA7021_SHANGHAI BA038_BEIJING BA268_LOSANGELES AA6428_BRUSSELS AA6711_ABERDEEN IB5390_BILBAO AA6439_GLASGOW BD164_PALMAMALLORCA RB409_DAMASCUS - plane
		main -runway)


	(:init (free main)
		(ready)
		(= (earliest UA938_CHICAGO) 20)
		(= (target UA938_CHICAGO) 30)
		(= (latest UA938_CHICAGO) 40)
		(= (latePenalty UA938_CHICAGO) 500)
		(= (latePenaltyRate UA938_CHICAGO) 50)
		(= (earlyPenaltyRate UA938_CHICAGO) 30)
		(= (earliest CA7021_SHANGHAI) 215)
		(= (target CA7021_SHANGHAI) 225)
		(= (latest CA7021_SHANGHAI) 235)
		(= (latePenalty CA7021_SHANGHAI) 500)
		(= (latePenaltyRate CA7021_SHANGHAI) 50)
		(= (earlyPenaltyRate CA7021_SHANGHAI) 30)
		(= (earliest BA038_BEIJING) 255)
		(= (target BA038_BEIJING) 265)
		(= (latest BA038_BEIJING) 275)
		(= (latePenalty BA038_BEIJING) 500)
		(= (latePenaltyRate BA038_BEIJING) 50)
		(= (earlyPenaltyRate BA038_BEIJING) 30)
		(= (earliest BA268_LOSANGELES) 275)
		(= (target BA268_LOSANGELES) 285)
		(= (latest BA268_LOSANGELES) 295)
		(= (latePenalty BA268_LOSANGELES) 500)
		(= (latePenaltyRate BA268_LOSANGELES) 50)
		(= (earlyPenaltyRate BA268_LOSANGELES) 30)
		(= (earliest AA6428_BRUSSELS) 280)
		(= (target AA6428_BRUSSELS) 290)
		(= (latest AA6428_BRUSSELS) 300)
		(= (latePenalty AA6428_BRUSSELS) 500)
		(= (latePenaltyRate AA6428_BRUSSELS) 50)
		(= (earlyPenaltyRate AA6428_BRUSSELS) 30)
		(= (earliest AA6711_ABERDEEN) 270)
		(= (target AA6711_ABERDEEN) 290)
		(= (latest AA6711_ABERDEEN) 310)
		(= (latePenalty AA6711_ABERDEEN) 200)
		(= (latePenaltyRate AA6711_ABERDEEN) 20)
		(= (earlyPenaltyRate AA6711_ABERDEEN) 10)
		(= (earliest IB5390_BILBAO) 285)
		(= (target IB5390_BILBAO) 295)
		(= (latest IB5390_BILBAO) 305)
		(= (latePenalty IB5390_BILBAO) 500)
		(= (latePenaltyRate IB5390_BILBAO) 50)
		(= (earlyPenaltyRate IB5390_BILBAO) 30)
		(= (earliest AA6439_GLASGOW) 280)
		(= (target AA6439_GLASGOW) 300)
		(= (latest AA6439_GLASGOW) 320)
		(= (latePenalty AA6439_GLASGOW) 200)
		(= (latePenaltyRate AA6439_GLASGOW) 20)
		(= (earlyPenaltyRate AA6439_GLASGOW) 10)
		(= (earliest BD164_PALMAMALLORCA) 290)
		(= (target BD164_PALMAMALLORCA) 300)
		(= (latest BD164_PALMAMALLORCA) 310)
		(= (latePenalty BD164_PALMAMALLORCA) 500)
		(= (latePenaltyRate BD164_PALMAMALLORCA) 50)
		(= (earlyPenaltyRate BD164_PALMAMALLORCA) 30)
		(= (earliest RB409_DAMASCUS) 290)
		(= (target RB409_DAMASCUS) 300)
		(= (latest RB409_DAMASCUS) 310)
		(= (latePenalty RB409_DAMASCUS) 500)
		(= (latePenaltyRate RB409_DAMASCUS) 50)
		(= (earlyPenaltyRate RB409_DAMASCUS) 30)
		(= (total-cost) 0)
		(= (fake-duration) 0)
	)
(:goal (and
		(landed UA938_CHICAGO)
		(landed CA7021_SHANGHAI)
		(landed BA038_BEIJING)
		(landed BA268_LOSANGELES)
		(landed AA6428_BRUSSELS)
		(landed AA6711_ABERDEEN)
		(landed IB5390_BILBAO)
		(landed AA6439_GLASGOW)
		(landed BD164_PALMAMALLORCA)
		(landed RB409_DAMASCUS)
	))
(:metric minimize (total-cost))
)
