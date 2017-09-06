(define (problem oiltest)
(:domain oilrefinery)

(:objects
  averagecrude - oiltype
  therefinery - refinery
  lightendstank napthatank kerosenetank lightgasoiltank pgotank - tank
  petroltanker - tanker
)

(:init
  
  (= (light-ends-percent averagecrude) 3.27)
  (= (naptha-percent averagecrude) 25.35)
  (= (kerosene-percent averagecrude) 16.8)
  (= (light-gasoil-percent averagecrude) 12.46)
  (= (pgo-percent averagecrude) 26.68)
  (inactive therefinery)

  (light-ends-tank lightendstank)
  (= (capacity lightendstank) 10000)
  (= (fuel-level lightendstank) 0)
  (naptha-tank napthatank)
  (= (capacity napthatank) 10000)
  (= (fuel-level napthatank) 0)
  (kerosene-tank kerosenetank)
  (= (capacity kerosenetank) 10000)
  (= (fuel-level kerosenetank) 0)
  (light-gasoil-tank lightgasoiltank)
  (= (capacity lightgasoiltank) 10000)
  (= (fuel-level lightgasoiltank) 0)
  (pgo-tank pgotank)
  (= (capacity pgotank) 10000)
  (= (fuel-level pgotank) 0)

  (= (barrels-left) 100)

  (= (cracking-rate) 7)
  (= (tank-fill-rate) 10)
  (= (barrel-fill-rate) 10)
  (= (tanker-capacity petroltanker) 10000)
  (= (tanker-fuel-level petroltanker) 0)

)

(:goal (and
    (refining therefinery)
    (>= (tanker-fuel-level petroltanker) 10)
  )
)

)