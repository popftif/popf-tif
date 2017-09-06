(define (domain CafeDomain)
     (:requirements :typing :fluents :durative-actions :duration-inequalities) 
     (:types table chef socket - object tea toast cooked_breaky - item)
     (:predicates 
          (delivered ?i - item ?t - table)
          (d_w_available ?t - table)
          (d_w_open ?t - table)
          (ready ?i - item)
          (loosing_heat_tea ?i - tea)
          (loosing_heat_toast ?i - toast)
          (loosing_heat_breaky ?i - cooked_breaky)
          (started_delivery ?i - item)
          (chef_free ?c - chef)
          (socket_free ?s - socket)
          (started_cooking_tea ?i - tea)
          (started_cooking_toast ?i - toast)
          (started_cooking_breaky ?i - cooked_breaky)
     )
     (:functions
          (total_delivery_window)
          (total_heat_lost))
          
     (:durative-action DELIVERY_WINDOW
          :parameters (?t - table)
          :duration (<= ?duration 10000000)
          :condition (and
               (at start (d_w_available ?t)))
          :effect (and 
               (at start (not (d_w_available ?t)))
               (at start (d_w_open ?t))
               (at end (not (d_w_open ?t)))
               (at end (increase (total_delivery_window) ?duration))))

     (:durative-action DELIVER
          :parameters (?i - item ?t - table)
          :duration (= ?duration 2)
          :condition (and
               (at end (d_w_open ?t))
               (over all(d_w_open ?t))
               (at start (ready ?i)))
          :effect (and 
               (at start (started_delivery ?i))
               (at end (not (started_delivery ?i)))
               (at end (delivered ?i ?t))
               (at end (not (ready ?i)))))
               
     (:durative-action LOOSING_HEAT_TEA
          :parameters (?i - tea)
          :duration (<= ?duration 1000)
          :condition (and 
               (at start (started_cooking_tea ?i))
               (at end (started_delivery ?i)))
          :effect (and 
               (at start (loosing_heat_tea ?i))
               (at end (not (loosing_heat_tea ?i)))
               (at end (increase (total_heat_lost) ?duration))))

     (:durative-action LOOSING_HEAT_TOAST
          :parameters (?i - toast)
          :duration (<= ?duration 1000)
          :condition (and
               (at start (started_cooking_toast ?i))
               (at end (started_delivery ?i)))
          :effect (and
               (at start (loosing_heat_toast ?i))
               (at end (not (loosing_heat_toast ?i)))
               (at end (increase (total_heat_lost) ?duration))))

     (:durative-action LOOSING_HEAT_BREAKY
          :parameters (?i - cooked_breaky)
          :duration (<= ?duration 1000)
          :condition (and
               (at start (started_cooking_breaky ?i))
               (at end (started_delivery ?i)))
          :effect (and
               (at start (loosing_heat_breaky ?i))
               (at end (not (loosing_heat_breaky ?i)))
               (at end (increase (total_heat_lost) ?duration))))

          
     (:durative-action MAKE_TEA
          :parameters (?i - tea ?s - socket)
          :duration (= ?duration 1)
          :condition (and 
               (at start (socket_free ?s))
               (at end (loosing_heat_tea ?i)))
          :effect (and 
               (at start (not (socket_free ?s)))
               (at start (started_cooking_tea ?i))
               (at end (socket_free ?s))
               (at end (ready ?i))))
               
     (:durative-action MAKE_TOAST
          :parameters (?i - toast ?s - socket)
          :duration (= ?duration 2)
          :condition (and 
               (at start (socket_free ?s))
               (at end (loosing_heat_toast ?i)))
          :effect (and 
               (at start (not (socket_free ?s)))
               (at start (started_cooking_toast ?i))
               (at end (socket_free ?s))
               (at end (ready ?i))))
               
     (:durative-action MAKE_COOKED_BREAKY
          :parameters (?i - cooked_breaky ?c - chef)
          :duration (= ?duration 4)
          :condition (and 
               (at start (chef_free ?c))
               (at end (loosing_heat_breaky ?i)))
          :effect (and 
               (at start (not (chef_free ?c)))
               (at start (started_cooking_breaky ?i))
               (at end (chef_free ?c))
               (at end (ready ?i)))))
