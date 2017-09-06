(define (domain matchlift)
     (:requirements :durative-actions :typing) 
     (:types fuse match lift electrician floor room - object)
     (:predicates
          (light ?match - match ?room - room)
          (handfree ?elec - electrician)
          (unused ?match - match)
          (mended ?fuse - fuse)
          (onfloor ?elec - electrician ?floor - floor)
          (inlift ?elec - electrician ?lift - lift)
          (roomonfloor ?room - room ?floor - floor)
          (liftonfloor ?lift - lift ?floor - floor)
          (inroom ?elec - electrician ?room - room)
          (fuseinroom ?fuse - fuse ?room - room)
          (connectedfloors ?floor1 ?floor2 - floor))

     (:durative-action LIGHT_MATCH
           :parameters (?match - match 
               ?elec - electrician 
               ?room - room)
            :duration (= ?duration 8)
            :condition (and 
               (at start (unused ?match))
               (over all (inroom ?elec ?room))
               (over all (light ?match ?room)))
          :effect (and 
               (at start (not (unused ?match)))
               (at start (light ?match ?room))
               (at end (not (light ?match ?room)))))

     (:durative-action MEND_FUSE
          :parameters (?fuse - fuse 
               ?match - match
               ?room - room
               ?elec - electrician)
           :duration (= ?duration 5)
          :condition (and
               (at start (inroom ?elec ?room))
               (over all (inroom ?elec ?room))
               (at start (fuseinroom ?fuse ?room))
               (at start (handfree ?elec))
               (at start (light ?match ?room))
               (over all (light ?match ?room)))
          :effect (and
               (at start (not (handfree ?elec)))
               (at end (mended ?fuse))
               (at end (handfree ?elec))))

     (:durative-action ENTER_ROOM
          :parameters (?floor - floor
               ?room - room
               ?elec - electrician)
          :duration (= ?duration 1)
          :condition (and
               (at start (onfloor ?elec ?floor))
               (at start (roomonfloor ?room ?floor)))
          :effect  (and 
               (at end (inroom ?elec ?room))
               (at start (not (onfloor ?elec ?floor)))))

     (:durative-action EXIT_ROOM
          :parameters (?floor - floor
               ?room - room
               ?elec - electrician)
          :duration (= ?duration 1)
          :condition (and
               (at start (inroom ?elec ?room))
               (at start (roomonfloor ?room ?floor)))
          :effect  (and 
               (at start (not (inroom ?elec ?room)))
               (at end (onfloor ?elec ?floor))))

     (:durative-action ENTER_LIFT
          :parameters (?floor - floor
               ?lift - lift
               ?elec - electrician)
          :duration (= ?duration 1)
          :condition (and
               (at start (onfloor ?elec ?floor))
               (at start (liftonfloor ?lift ?floor))
               (over all (liftonfloor ?lift ?floor)))
          :effect  (and 
               (at end (inlift ?elec ?lift))
               (at start (not (onfloor ?elec ?floor)))))

     (:durative-action EXIT_LIFT
          :parameters (?floor - floor
               ?lift - lift
               ?elec - electrician)
          :duration (= ?duration 1)
          :condition (and
               (at start (inlift ?elec ?lift))
               (at start (liftonfloor ?lift ?floor))
               (over all (liftonfloor ?lift ?floor)))
          :effect  (and 
               (at start (not (inlift ?elec ?lift)))
               (at end (onfloor ?elec ?floor))))

     (:durative-action MOVE_LIFT
          :parameters (?floorfrom ?floorto - floor
               ?lift - lift)
          :duration (= ?duration 2)
          :condition (and
               (at start (connectedfloors ?floorfrom ?floorto))
               (at start (liftonfloor ?lift ?floorfrom)))
          :effect  (and 
               (at start (not (liftonfloor ?lift ?floorfrom)))
               (at end (liftonfloor ?lift ?floorto))))
)
