(define (problem oiltest)
(:domain oilrefinery)

(:objects
  averagecrude - oiltype
  therefinery - refinery
  nhttank kerotank untreatedcgotank residuetank bitumentank - tank
  lpgtank c4tank topstank napthatank platformatetank - tank
  ccgtank lcotank hcotank - tank
  petroltankera petroltankerb - tanker
  kerosenetankera kerosenetankerb - tanker
  cgotanker - tanker
  fueloiltanker - tanker
  ulg92tank ulg97tank - tank
  car-park - location
  nhtsplitter - splitter
  crackingunit - cracker
  platformerunit - platformer
  gasolineblender - blender
)

(:init
  
  (= (constituentpercentage nht averagecrude) 28.62)
  (= (constituentpercentage kerosene averagecrude) 16.8)
  (= (constituentpercentage untreatedcgo averagecrude) 41.14)
  (= (constituentpercentage bitumen averagecrude) 13.50)
  (inactive therefinery)

  (= (refine-rate therefinery) 1)

  ;; Tanks connected directly to the CDU

  (tank-for nht nhttank)
  (connected therefinery nhttank)
  (= (capacity nhttank) 200) ; is a dummy tank - really, we want the splitter to be running straight away to put the NHT into real tanks
  (= (fuel-level nhttank) 50)
  (= (minimum-level nhttank) 50)

  (tank-for kerosene kerotank)
  (connected therefinery kerotank)
  (= (capacity kerotank) 10000)
  (= (fuel-level kerotank) 50)
  (= (minimum-level kerotank) 50)

  (tank-for untreatedcgo untreatedcgotank)
  (connected therefinery untreatedcgotank)
  (= (capacity untreatedcgotank) 10000)
  (= (fuel-level untreatedcgotank) 50)
  (= (minimum-level untreatedcgotank) 50)

  (tank-for bitumen residuetank)
  (connected therefinery residuetank)
  (= (capacity residuetank) 10000)
  (= (fuel-level residuetank) 50)
  (= (minimum-level residuetank) 50)

  (tank-for bitumen bitumentank)
  (connected therefinery bitumentank)
  (= (capacity bitumentank) 10000)
  (= (fuel-level bitumentank) 50)
  (= (minimum-level bitumentank) 50)

  ;; NHT reprocessing

  (tank-for lpg lpgtank)
  (connected nhtsplitter lpgtank)
  (= (capacity lpgtank) 10000)
  (= (fuel-level lpgtank) 50)
  (= (minimum-level lpgtank) 50)

  (tank-for c4 c4tank)
  (connected nhtsplitter c4tank)
  (= (capacity c4tank) 10000)
  (= (fuel-level c4tank) 50)
  (= (minimum-level c4tank) 50)
  
  (tank-for tops topstank)
  (connected nhtsplitter topstank)
  (= (capacity topstank) 10000)
  (= (fuel-level topstank) 50)
  (= (minimum-level topstank) 50)


  (tank-for naptha napthatank)
  (connected nhtsplitter napthatank)
  (= (capacity napthatank) 10000)
  (= (fuel-level napthatank) 50)
  (= (minimum-level napthatank) 50)

  (connected nhtsplitter nhttank)
  (connected nhtsplitter lpgtank)
  (connected nhtsplitter c4tank)
  (connected nhtsplitter topstank)
  (connected nhtsplitter napthatank)

  (inactive nhtsplitter)

  (= (rate nhtsplitter) 0.2862)

  (= (constituentpercentage lpg nht) 1.328)
  (= (constituentpercentage c4 nht) 3.704)
  (= (constituentpercentage tops nht) 6.394)
  (= (constituentpercentage naptha nht) 88.574)

  ;; Catalytic cracker

  (= (rate crackingunit) 0.135)

  (connected crackingunit residuetank)
  (connected crackingunit lpgtank)
  
  (tank-for ccg ccgtank)
  (connected crackingunit ccgtank)
  (= (capacity ccgtank) 10000)
  (= (fuel-level ccgtank) 50)
  (= (minimum-level ccgtank) 50)

  (tank-for lco lcotank)
  (connected crackingunit lcotank)
  (= (capacity lcotank) 10000)
  (= (fuel-level lcotank) 50)
  (= (minimum-level lcotank) 50)

  (tank-for hco hcotank)
  (connected crackingunit hcotank)
  (= (capacity hcotank) 10000)
  (= (fuel-level hcotank) 50)
  (= (minimum-level hcotank) 50)

  (= (constituentpercentage lpg bitumen) 9)
  (= (constituentpercentage ccg bitumen) 9)
  (= (constituentpercentage lco bitumen) 20)
  (= (constituentpercentage hco bitumen) 30)

  (inactive crackingunit)

  ;; Platformer

  (= (rate platformerunit) 0.127)

  (connected platformerunit napthatank)
  (connected platformerunit platformatetank)

  (tank-for platformate platformatetank)
  (= (capacity platformatetank) 10000)
  (= (fuel-level platformatetank) 50)
  (= (minimum-level platformatetank) 50)

  (inactive platformerunit)

  ;; Blender


  (connected gasolineblender c4tank)
  (connected gasolineblender platformatetank)
  (connected gasolineblender topstank)
  (connected gasolineblender napthatank)
  (connected gasolineblender ccgtank)

  (= (blendinputrate gasolineblender c4) 0.0053)          ; Half the C4 produced by the splitter
  (= (blendinputrate gasolineblender platformate) 0.127)  ; All the platformate
  (= (blendinputrate gasolineblender tops) 0.182996)      ; All the tops
  (= (blendinputrate gasolineblender naptha) 0.127)       ; Half the naptha (the rest going to platformate)
  (= (blendinputrate gasolineblender ccg) 0.01215)        ; All the CCG

  (connected gasolineblender ulg92tank)
  (connected gasolineblender ulg97tank)

  (tank-for ulg92 ulg92tank)
  (= (capacity ulg92tank) 10000)
  (= (fuel-level ulg92tank) 50)
  (= (minimum-level ulg92tank) 50)

  (tank-for ulg97 ulg97tank)
  (= (capacity ulg97tank) 10000)
  (= (fuel-level ulg97tank) 50)
  (= (minimum-level ulg97tank) 50)

  (inactive gasolineblender)

  ;; Logistics

  (= (barrels-left) 100)


  (= (tank-fill-rate) 5)
  (= (barrel-fill-rate) 10)

  (= (tanker-capacity petroltankera) 50)
  (= (tanker-fuel-level petroltankera) 0)
  (= (tanker-capacity petroltankerb) 50)
  (= (tanker-fuel-level petroltankerb) 0)

  (at petroltankera car-park)
  (at petroltankerb car-park)

  (tanker-is-for petroltankera ulg92)
  (tanker-is-for petroltankerb ulg97)

  (= (tanker-capacity kerosenetankera) 50)
  (= (tanker-fuel-level kerosenetankera) 0)
  (= (tanker-capacity kerosenetankerb) 50)
  (= (tanker-fuel-level kerosenetankerb) 0)

  (at kerosenetankera car-park)
  (at kerosenetankerb car-park)

  (tanker-is-for kerosenetankera kerosene)
  (tanker-is-for kerosenetankerb kerosene)

  (tanker-is-for cgotanker  untreatedcgo)
  (= (tanker-capacity cgotanker) 50)
  (= (tanker-fuel-level cgotanker) 0)
  (at cgotanker car-park)

  (tanker-is-for fueloiltanker fueloil)
  (= (tanker-capacity fueloiltanker) 25)
  (= (tanker-fuel-level fueloiltanker) 0)
  (at fueloiltanker car-park)


  (adjacent bythehoses car-park)
  (adjacent car-park bythehoses)
 

  (= (free-hoses) 1)

)

(:goal (and
    (>= (tanker-fuel-level petroltankera) 50)
    (>= (tanker-fuel-level petroltankerb) 50)
    ;(>= (tanker-fuel-level kerosenetankera) 50)
    ;(>= (tanker-fuel-level kerosenetankerb) 50)
    ;(>= (tanker-fuel-level cgotanker) 50)
    ;(>= (tanker-fuel-level fueloiltanker) 25)

    ;(>= (fuel-level platformatetank) 51)
    ;(>= (fuel-level napthatank) 51)
    ;(>= (fuel-level ccgtank) 51)    
    ;(>= (fuel-level topstank) 51)
    ;(>= (fuel-level c4tank) 51)
    ;(>= (fuel-level lpgtank) 51)
    
     ;(>= (fuel-level ulg92tank) 100)
     ;(>= (fuel-level ulg97tank) 100)  
  )
)
(:metric minimize (total-time))
)
