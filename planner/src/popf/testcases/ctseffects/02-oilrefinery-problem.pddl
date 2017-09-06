(define (problem oiltest)
(:domain oilrefinery)

(:objects
  averagecrude - oiltype
  therefinery - refinery
  lightendstank napthatank kerosenetank lightgasoiltank pgotank - tank
  petroltankera petroltankerb - tanker
  kerosenetankera kerosenetankerb - tanker
  car-park - location
  crackingunit - cracker
)

(:init
  
  (= (light-ends-percent averagecrude) 3.27)
  (= (naptha-percent averagecrude) 25.35)
  (= (kerosene-percent averagecrude) 16.8)
  (= (light-gasoil-percent averagecrude) 12.46)
  (= (pgo-percent averagecrude) 26.68)
  (inactive therefinery)

  (= (refine-rate therefinery) 0.01)

  (tank-for light-ends lightendstank)
  (connected therefinery lightendstank)
  (= (capacity lightendstank) 10000)
  (= (fuel-level lightendstank) 50)
  (= (minimum-level lightendstank) 50)

  (tank-for naptha napthatank)
  (connected therefinery napthatank)
  (= (capacity napthatank) 10000)
  (= (fuel-level napthatank) 50)
  (= (minimum-level napthatank) 50)

  (tank-for kerosene kerosenetank)
  (connected therefinery kerosenetank)
  (= (capacity kerosenetank) 10000)
  (= (fuel-level kerosenetank) 50)
  (= (minimum-level kerosenetank) 50)

  (tank-for light-gasoil lightgasoiltank)
  (connected therefinery lightgasoiltank)
  (= (capacity lightgasoiltank) 10000)
  (= (fuel-level lightgasoiltank) 50)
  (= (minimum-level lightgasoiltank) 50)

  (tank-for pgo pgotank)
  (connected therefinery pgotank)
  (= (capacity pgotank) 10000)
  (= (fuel-level pgotank) 50)
  (= (minimum-level pgotank) 50)

  (= (barrels-left) 100)

  (= (cracking-rate crackingunit) 7)

  (connected crackingunit lightgasoiltank)
  (connected crackingunit napthatank)

  (= (tank-fill-rate) 10)
  (= (barrel-fill-rate) 10)

  (= (tanker-capacity petroltankera) 100)
  (= (tanker-fuel-level petroltankera) 0)
  (= (tanker-capacity petroltankerb) 100)
  (= (tanker-fuel-level petroltankerb) 0)

  (at petroltankera car-park)
  (at petroltankerb car-park)

  (tanker-is-for petroltankera pgo)
  (tanker-is-for petroltankerb pgo)

  (= (tanker-capacity kerosenetankera) 100)
  (= (tanker-fuel-level kerosenetankera) 0)
  (= (tanker-capacity kerosenetankerb) 100)
  (= (tanker-fuel-level kerosenetankerb) 0)

  (at kerosenetankera car-park)
  (at kerosenetankerb car-park)

  (tanker-is-for kerosenetankera kerosene)
  (tanker-is-for kerosenetankerb kerosene)

  (adjacent bythehoses car-park)
  (adjacent car-park bythehoses)

  (= (free-hoses) 1)

)

(:goal (and
    (refining therefinery)
    (>= (tanker-fuel-level petroltankera) 100)
    (>= (tanker-fuel-level petroltankerb) 100)
    (>= (tanker-fuel-level kerosenetankera) 100)
    (>= (tanker-fuel-level kerosenetankerb) 100)

  )
)
(:metric minimize (total-time))
)