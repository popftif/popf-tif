(define (problem prob)
    (:domain UAV)
    (:objects v-177669 v-179119 v-180215 v-188837 v-188858 v-188153 v-187433 v-190659 v-198934 v-211594 v-221698  - destination
        spiral1 spiral2 spiral3 spiral4 spiral5 spiral6 spiral7 spiral8 spiral9 spiral10 spiral11 spiral12 spiral13 spiral14  - spiral
        - smallLawnmower
        - largeLawnmower
	origin s1s s1e s2s s2e s3s s3e s4s s4e s5s s5e s6s s6e s7s s7e s8s s8e s9s s9e s10s s10e s11s s11e s12s s12e s13s s13e s14s s14e  - waypoint)
    (:init
	(= (n-pattern) 0)
	(= (expected-time) 0)
	(= (previous-expected-time) 0)
	(= (total-probability) 0)
	(= (previous-total-probability) 0)
	(= (profile) -1)
	(at 6161 (f)
	    (s) (at 0.003 (not (s)))
	    (= (heuristic-expected spiral9) 0.001)
	    (= (heuristic-approximation spiral9) 0.001)
	    (= (heuristic-expected spiral8) 0.001)
	    (= (heuristic-approximation spiral8) 0.001)
	    (= (heuristic-expected spiral7) 0.001)
	    (= (heuristic-approximation spiral7) 0.001)
	    (= (heuristic-expected spiral6) 0.001)
	    (= (heuristic-approximation spiral6) 0.001)
	    (= (heuristic-expected spiral5) 0.001)
	    (= (heuristic-approximation spiral5) 0.001)
	    (= (heuristic-expected spiral4) 0.001)
	    (= (heuristic-approximation spiral4) 0.001)
	    (= (heuristic-expected spiral3) 0.001)
	    (= (heuristic-approximation spiral3) 0.001)
	    (= (heuristic-expected spiral2) 0.001)
	    (= (heuristic-approximation spiral2) 0.001)
	    (= (heuristic-expected spiral14) 0.001)
	    (= (heuristic-approximation spiral14) 0.001)
	    (= (heuristic-expected spiral13) 0.001)
	    (= (heuristic-approximation spiral13) 0.001)
	    (= (heuristic-expected spiral12) 0.001)
	    (= (heuristic-approximation spiral12) 0.001)
	    (= (heuristic-expected spiral11) 0.001)
	    (= (heuristic-approximation spiral11) 0.001)
	    (= (heuristic-expected spiral10) 0.001)
	    (= (heuristic-approximation spiral10) 0.001)
	    (= (heuristic-expected spiral1) 0.001)
	    (= (heuristic-approximation spiral1) 0.001)
	    (at origin)
	    (= (previous-probability v-177669) 0.09090909)
	    (= (probability v-177669) 0.09090909)
	    (= (previous-probability v-179119) 0.09090909)
	    (= (probability v-179119) 0.09090909)
	    (= (previous-probability v-180215) 0.09090909)
	    (= (probability v-180215) 0.09090909)
	    (= (previous-probability v-188837) 0.09090909)
	    (= (probability v-188837) 0.09090909)
	    (= (previous-probability v-188858) 0.09090909)
	    (= (probability v-188858) 0.09090909)
	    (= (previous-probability v-188153) 0.09090909)
	    (= (probability v-188153) 0.09090909)
	    (= (previous-probability v-187433) 0.09090909)
	    (= (probability v-187433) 0.09090909)
	    (= (previous-probability v-190659) 0.09090909)
	    (= (probability v-190659) 0.09090909)
	    (= (previous-probability v-198934) 0.09090909)
	    (= (probability v-198934) 0.09090909)
	    (= (previous-probability v-211594) 0.09090909)
	    (= (probability v-211594) 0.09090909)
	    (= (previous-probability v-221698) 0.09090909)
	    (= (probability v-221698) 0.09090909)
	    (= (is-doing spiral1) 0)
	    (= (timefor spiral1) 299)
	    (beginAt s1s spiral1)
	    (endAt s1e spiral1)
	    (at 1473 (active spiral1))
	    (at 2753 (not (active spiral1)))
	    (= (n-pattern-active spiral1) 2113.0)
	    (= (distance origin s1s) 241)
	    (= (distance s1e s1s) 38)
	    (= (distance s1e s2s) 203)
	    (= (distance s1e s3s) 73)
	    (= (distance s1e s4s) 178)
	    (= (distance s1e s5s) 271)
	    (= (distance s1e s6s) 219)
	    (= (distance s1e s7s) 241)
	    (= (distance s1e s8s) 281)
	    (= (distance s1e s9s) 289)
	    (= (distance s1e s10s) 491)
	    (= (distance s1e s11s) 404)
	    (= (distance s1e s12s) 488)
	    (= (distance s1e s13s) 520)
	    (= (distance s1e s14s) 534)
	    (= (is-doing spiral2) 0)
	    (= (timefor spiral2) 299)
	    (beginAt s2s spiral2)
	    (endAt s2e spiral2)
	    (at 1374 (active spiral2))
	    (at 2330 (not (active spiral2)))
	    (= (n-pattern-active spiral2) 1852.0)
	    (= (distance origin s2s) 276)
	    (= (distance s2e s1s) 269)
	    (= (distance s2e s2s) 38)
	    (= (distance s2e s3s) 313)
	    (= (distance s2e s4s) 63)
	    (= (distance s2e s5s) 51)
	    (= (distance s2e s6s) 111)
	    (= (distance s2e s7s) 147)
	    (= (distance s2e s8s) 61)
	    (= (distance s2e s9s) 161)
	    (= (distance s2e s10s) 264)
	    (= (distance s2e s11s) 288)
	    (= (distance s2e s12s) 276)
	    (= (distance s2e s13s) 742)
	    (= (distance s2e s14s) 350)
	    (= (is-doing spiral3) 0)
	    (= (timefor spiral3) 299)
	    (beginAt s3s spiral3)
	    (endAt s3e spiral3)
	    (at 1821 (active spiral3))
	    (at 3414 (not (active spiral3)))
	    (= (n-pattern-active spiral3) 2617.5)
	    (= (distance origin s3s) 273)
	    (= (distance s3e s1s) 47)
	    (= (distance s3e s2s) 252)
	    (= (distance s3e s3s) 38)
	    (= (distance s3e s4s) 228)
	    (= (distance s3e s5s) 318)
	    (= (distance s3e s6s) 258)
	    (= (distance s3e s7s) 275)
	    (= (distance s3e s8s) 328)
	    (= (distance s3e s9s) 324)
	    (= (distance s3e s10s) 535)
	    (= (distance s3e s11s) 430)
	    (= (distance s3e s12s) 530)
	    (= (distance s3e s13s) 470)
	    (= (distance s3e s14s) 570)
	    (= (is-doing spiral4) 0)
	    (= (timefor spiral4) 299)
	    (beginAt s4s spiral4)
	    (endAt s4e spiral4)
	    (at 1306 (active spiral4))
	    (at 2237 (not (active spiral4)))
	    (= (n-pattern-active spiral4) 1771.5)
	    (= (distance origin s4s) 264)
	    (= (distance s4e s1s) 245)
	    (= (distance s4e s2s) 15)
	    (= (distance s4e s3s) 289)
	    (= (distance s4e s4s) 38)
	    (= (distance s4e s5s) 66)
	    (= (distance s4e s6s) 103)
	    (= (distance s4e s7s) 141)
	    (= (distance s4e s8s) 77)
	    (= (distance s4e s9s) 162)
	    (= (distance s4e s10s) 285)
	    (= (distance s4e s11s) 292)
	    (= (distance s4e s12s) 295)
	    (= (distance s4e s13s) 719)
	    (= (distance s4e s14s) 365)
	    (= (is-doing spiral5) 0)
	    (= (timefor spiral5) 299)
	    (beginAt s5s spiral5)
	    (endAt s5e spiral5)
	    (at 1838 (active spiral5))
	    (at 2900 (not (active spiral5)))
	    (= (n-pattern-active spiral5) 2369.0)
	    (= (distance origin s5s) 343)
	    (= (distance s5e s1s) 338)
	    (= (distance s5e s2s) 107)
	    (= (distance s5e s3s) 380)
	    (= (distance s5e s4s) 131)
	    (= (distance s5e s5s) 38)
	    (= (distance s5e s6s) 129)
	    (= (distance s5e s7s) 152)
	    (= (distance s5e s8s) 32)
	    (= (distance s5e s9s) 142)
	    (= (distance s5e s10s) 191)
	    (= (distance s5e s11s) 250)
	    (= (distance s5e s12s) 205)
	    (= (distance s5e s13s) 793)
	    (= (distance s5e s14s) 284)
	    (= (is-doing spiral6) 0)
	    (= (timefor spiral6) 299)
	    (beginAt s6s spiral6)
	    (endAt s6e spiral6)
	    (at 1973 (active spiral6))
	    (at 2892 (not (active spiral6)))
	    (= (n-pattern-active spiral6) 2432.5)
	    (= (distance origin s6s) 363)
	    (= (distance s6e s1s) 290)
	    (= (distance s6e s2s) 103)
	    (= (distance s6e s3s) 327)
	    (= (distance s6e s4s) 114)
	    (= (distance s6e s5s) 68)
	    (= (distance s6e s6s) 38)
	    (= (distance s6e s7s) 53)
	    (= (distance s6e s8s) 69)
	    (= (distance s6e s9s) 59)
	    (= (distance s6e s10s) 244)
	    (= (distance s6e s11s) 190)
	    (= (distance s6e s12s) 235)
	    (= (distance s6e s13s) 707)
	    (= (distance s6e s14s) 284)
	    (= (is-doing spiral7) 0)
	    (= (timefor spiral7) 299)
	    (beginAt s7s spiral7)
	    (endAt s7e spiral7)
	    (at 2171 (active spiral7))
	    (at 3165 (not (active spiral7)))
	    (= (n-pattern-active spiral7) 2668.0)
	    (= (distance origin s7s) 401)
	    (= (distance s7e s1s) 311)
	    (= (distance s7e s2s) 142)
	    (= (distance s7e s3s) 345)
	    (= (distance s7e s4s) 151)
	    (= (distance s7e s5s) 104)
	    (= (distance s7e s6s) 58)
	    (= (distance s7e s7s) 38)
	    (= (distance s7e s8s) 102)
	    (= (distance s7e s9s) 20)
	    (= (distance s7e s10s) 243)
	    (= (distance s7e s11s) 151)
	    (= (distance s7e s12s) 225)
	    (= (distance s7e s13s) 701)
	    (= (distance s7e s14s) 260)
	    (= (is-doing spiral8) 0)
	    (= (timefor spiral8) 299)
	    (beginAt s8s spiral8)
	    (endAt s8e spiral8)
	    (at 1918 (active spiral8))
	    (at 2994 (not (active spiral8)))
	    (= (n-pattern-active spiral8) 2456.0)
	    (= (distance origin s8s) 353)
	    (= (distance s8e s1s) 348)
	    (= (distance s8e s2s) 117)
	    (= (distance s8e s3s) 390)
	    (= (distance s8e s4s) 141)
	    (= (distance s8e s5s) 47)
	    (= (distance s8e s6s) 134)
	    (= (distance s8e s7s) 155)
	    (= (distance s8e s8s) 38)
	    (= (distance s8e s9s) 142)
	    (= (distance s8e s10s) 180)
	    (= (distance s8e s11s) 246)
	    (= (distance s8e s12s) 194)
	    (= (distance s8e s13s) 800)
	    (= (distance s8e s14s) 275)
	    (= (is-doing spiral9) 0)
	    (= (timefor spiral9) 299)
	    (beginAt s9s spiral9)
	    (endAt s9e spiral9)
	    (at 2439 (active spiral9))
	    (at 3596 (not (active spiral9)))
	    (= (n-pattern-active spiral9) 3017.5)
	    (= (distance origin s9s) 435)
	    (= (distance s9e s1s) 359)
	    (= (distance s9e s2s) 174)
	    (= (distance s9e s3s) 393)
	    (= (distance s9e s4s) 187)
	    (= (distance s9e s5s) 117)
	    (= (distance s9e s6s) 103)
	    (= (distance s9e s7s) 85)
	    (= (distance s9e s8s) 111)
	    (= (distance s9e s9s) 38)
	    (= (distance s9e s10s) 201)
	    (= (distance s9e s11s) 125)
	    (= (distance s9e s12s) 178)
	    (= (distance s9e s13s) 743)
	    (= (distance s9e s14s) 213)
	    (= (is-doing spiral10) 0)
	    (= (timefor spiral10) 299)
	    (beginAt s10s spiral10)
	    (endAt s10e spiral10)
	    (at 3632 (active spiral10))
	    (at 5635 (not (active spiral10)))
	    (= (n-pattern-active spiral10) 4633.5)
	    (= (distance origin s10s) 537)
	    (= (distance s10e s1s) 552)
	    (= (distance s10e s2s) 323)
	    (= (distance s10e s3s) 594)
	    (= (distance s10e s4s) 347)
	    (= (distance s10e s5s) 249)
	    (= (distance s10e s6s) 316)
	    (= (distance s10e s7s) 316)
	    (= (distance s10e s8s) 239)
	    (= (distance s10e s9s) 276)
	    (= (distance s10e s10s) 38)
	    (= (distance s10e s11s) 289)
	    (= (distance s10e s12s) 88)
	    (= (distance s10e s13s) 980)
	    (= (distance s10e s14s) 180)
	    (= (is-doing spiral11) 0)
	    (= (timefor spiral11) 299)
	    (beginAt s11s spiral11)
	    (endAt s11e spiral11)
	    (at 3439 (active spiral11))
	    (at 4727 (not (active spiral11)))
	    (= (n-pattern-active spiral11) 4083.0)
	    (= (distance origin s11s) 567)
	    (= (distance s11e s1s) 469)
	    (= (distance s11e s2s) 305)
	    (= (distance s11e s3s) 497)
	    (= (distance s11e s4s) 317)
	    (= (distance s11e s5s) 247)
	    (= (distance s11e s6s) 224)
	    (= (distance s11e s7s) 193)
	    (= (distance s11e s8s) 239)
	    (= (distance s11e s9s) 149)
	    (= (distance s11e s10s) 223)
	    (= (distance s11e s11s) 38)
	    (= (distance s11e s12s) 173)
	    (= (distance s11e s13s) 785)
	    (= (distance s11e s14s) 134)
	    (= (is-doing spiral12) 0)
	    (= (timefor spiral12) 299)
	    (beginAt s12s spiral12)
	    (endAt s12e spiral12)
	    (at 4010 (active spiral12))
	    (at 6161 (not (active spiral12)))
	    (= (n-pattern-active spiral12) 5085.5)
	    (= (distance origin s12s) 561)
	    (= (distance s12e s1s) 551)
	    (= (distance s12e s2s) 328)
	    (= (distance s12e s3s) 590)
	    (= (distance s12e s4s) 351)
	    (= (distance s12e s5s) 252)
	    (= (distance s12e s6s) 303)
	    (= (distance s12e s7s) 297)
	    (= (distance s12e s8s) 241)
	    (= (distance s12e s9s) 252)
	    (= (distance s12e s10s) 41)
	    (= (distance s12e s11s) 242)
	    (= (distance s12e s12s) 38)
	    (= (distance s12e s13s) 956)
	    (= (distance s12e s14s) 122)
	    (= (is-doing spiral13) 0)
	    (= (timefor spiral13) 299)
	    (beginAt s13s spiral13)
	    (endAt s13e spiral13)
	    (at 4282 (active spiral13))
	    (at 5813 (not (active spiral13)))
	    (= (n-pattern-active spiral13) 5047.5)
	    (= (distance origin s13s) 727)
	    (= (distance s13e s1s) 519)
	    (= (distance s13e s2s) 704)
	    (= (distance s13e s3s) 477)
	    (= (distance s13e s4s) 682)
	    (= (distance s13e s5s) 751)
	    (= (distance s13e s6s) 664)
	    (= (distance s13e s7s) 656)
	    (= (distance s13e s8s) 758)
	    (= (distance s13e s9s) 696)
	    (= (distance s13e s10s) 935)
	    (= (distance s13e s11s) 732)
	    (= (distance s13e s12s) 909)
	    (= (distance s13e s13s) 38)
	    (= (distance s13e s14s) 903)
	    (= (is-doing spiral14) 0)
	    (= (timefor spiral14) 299)
	    (beginAt s14s spiral14)
	    (endAt s14e spiral14)
	    (at 4165 (active spiral14))
	    (at 6086 (not (active spiral14)))
	    (= (n-pattern-active spiral14) 5125.5)
	    (= (distance origin s14s) 641)
	    (= (distance s14e s1s) 598)
	    (= (distance s14e s2s) 391)
	    (= (distance s14e s3s) 632)
	    (= (distance s14e s4s) 411)
	    (= (distance s14e s5s) 317)
	    (= (distance s14e s6s) 342)
	    (= (distance s14e s7s) 324)
	    (= (distance s14e s8s) 306)
	    (= (distance s14e s9s) 274)
	    (= (distance s14e s10s) 145)
	    (= (distance s14e s11s) 210)
	    (= (distance s14e s12s) 100)
	    (= (distance s14e s13s) 955)
	    (= (distance s14e s14s) 38)
	    )
	(:goal (and (g)))
	(:metric maximize ( - (total-probability) (* 0.1 (expected-time)))))
    ; SpiralSearchPattern 1 38695.0 72181.0 2000.0 2500.0 299 1473 2753 93
    ; SpiralSearchPattern 2 24695.0 77681.0 2000.0 2500.0 299 1374 2330 90
    ; SpiralSearchPattern 3 41695.0 72181.0 2000.0 2500.0 299 1821 3414 19
    ; SpiralSearchPattern 4 26195.0 77181.0 2000.0 2500.0 299 1306 2237 18
    ; SpiralSearchPattern 5 21195.0 81181.0 2000.0 2500.0 299 1838 2900 34
    ; SpiralSearchPattern 6 26695.0 83681.0 2000.0 2500.0 299 1973 2892 17
    ; SpiralSearchPattern 7 27195.0 86181.0 2000.0 2500.0 299 2171 3165 71
    ; SpiralSearchPattern 8 20695.0 81681.0 2000.0 2500.0 299 1918 2994 26
    ; SpiralSearchPattern 9 24695.0 88181.0 2000.0 2500.0 299 2439 3596 69
    ; SpiralSearchPattern 10 9195.0 89181.0 2000.0 2500.0 299 3632 5635 34
    ; SpiralSearchPattern 11 23695.0 96681.0 2000.0 2500.0 299 3439 4727 65
    ; SpiralSearchPattern 12 11195.0 92181.0 2000.0 2500.0 299 4010 6161 53
    ; SpiralSearchPattern 13 70195.0 82681.0 2000.0 2500.0 299 4282 5813 59
    ; SpiralSearchPattern 14 12695.0 98681.0 2000.0 2500.0 299 4165 6086 54
    ; UAV 28611.575809840495 60171.61702671006 -64.85907537923887 -4.277889777709477 true 0.0
    ; Target 27912.27050638602 61796.27460838339 1.997055896016852 6.845218255359974 true 608 4386.0 91110.75
    ; Time 622 false true
