


(define (problem logistics-c2-s2-p2-a2)
(:domain logistics)
(:objects airplane0 airplane1  - airplane
          city0 city1  - city
          truck0 truck1  - truck
          loc0-0 loc1-0  - airport
          loc0-1 loc1-1  - location
          p0 p1  - package
)
(:init
(in-city  loc0-0 city0)
(in-city  loc0-1 city0)
(in-city  loc1-0 city1)
(in-city  loc1-1 city1)
(at truck0 loc0-0)
(at truck1 loc1-1)
(at p0 loc0-0)
(at p1 loc0-0)
(at airplane0 loc0-0)
(at airplane1 loc1-0)
(= (total-cost) 0)
)
(:goal
(and
(at p0 loc0-1)
(at p1 loc0-0)
)
)
(:metric minimize (total-cost))

)



