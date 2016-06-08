(clear) ; Case 1a
(load* "attchtst3.clp")

(defrule fail-pass "Case 1a"
   (object (is-a A))
   (test (= 1 1))
   =>)

(defrule fail-fail "Case 1a"
   (object (is-a B))
   (test (!= 2 2))
   =>)
(agenda)
(make-instance a of A)
(make-instance b of B)
(agenda)
(clear) ; Case 1b
(load* "attchtst3.clp")

(defrule pass-fail "Case 1b"
   (not (object (is-a A)))
   (test (= 1 1))
   =>)

(defrule fail-fail "Case 1b"
   (not (object (is-a B)))
   (test (!= 2 2))
   =>)
(agenda)
(make-instance a of A)
(make-instance b of B)
(agenda)
(clear) ; Case 1c
(load* "attchtst3.clp")

(defrule fail-pass "Case 1c"
   (exists (object (is-a A)))
   (test (= 1 1))
   =>)

(defrule fail-fail "Case 1c"
   (exists (object (is-a B)))
   (test (!= 2 2))
   =>)
(agenda)
(make-instance a of A)
(make-instance b of B)
(agenda)
(clear) ; Case 3a
(load* "attchtst3.clp")

(defrule pass-fail "Case 3a"
   (not (and (object (is-a A))
             (test (= 1 1))))
   =>)

(defrule pass-pass "Case 3a"
   (not (and (object (is-a B))
             (test (!= 2 2))))
   =>)
(agenda)
(make-instance a of A)
(make-instance b of B)
(agenda)
(clear) ; Case 3b
(load* "attchtst3.clp")

(defrule fail-pass "Case 3b"
   (not (and (not (object (is-a A)))
             (test (= 1 1))))
   =>)

(defrule pass-pass "Case 3b"
   (not (and (not (object (is-a B)))
             (test (!= 2 2))))
   =>)
(agenda)
(make-instance a of A)
(make-instance b of B)
(agenda)
(clear) ; Case 3c
(load* "attchtst3.clp")

(defrule pass-fail "Case 3c"
   (not (and (exists (object (is-a A)))
             (test (= 1 1))))
   =>)

(defrule pass-pass "Case 3c"
   (not (and (exists (object (is-a B)))
             (test (!= 2 2))))
   =>)
(agenda)
(make-instance a of A)
(make-instance b of B)
(agenda)
(clear) ; Case 3d
(load* "attchtst3.clp")

(defrule fail-pass "Case 3d"
   (exists (and (object (is-a A))
                (test (= 1 1))))
   =>)

(defrule fail-fail "Case 3d"
   (exists (and (object (is-a B))
                (test (!= 2 2))))
   =>)
(agenda)
(make-instance a of A)
(make-instance b of B)
(agenda)
(clear) ; Case 3e
(load* "attchtst3.clp")

(defrule pass-fail "Case 3e"
   (exists (and (not (object (is-a A)))
                (test (= 1 1))))
   =>)

(defrule fail-fail "Case 3e"
   (exists (and (not (object (is-a B)))
                (test (!= 2 2))))
   =>)
(agenda)
(make-instance a of A)
(make-instance b of B)
(agenda)
(clear) ; Case 3f
(load* "attchtst3.clp")

(defrule fail-pass "Case 3f"
   (exists (and (exists (object (is-a A)))
                (test (= 1 1))))
   =>)

(defrule fail-fail "Case 3f"
   (exists (and (exists (object (is-a B)))
                (test (!= 2 2))))
   =>)
(agenda)
(make-instance a of A)
(make-instance b of B)
(agenda)
(clear) ; Case 4a
(load* "attchtst3.clp")

(defrule pass-pass-fail "Case 4a"
   (not (and (object (is-a A))
             (object (is-a B))
             (test (= 1 1))))
   =>)

(defrule pass-pass-pass "Case 4a"
   (not (and (object (is-a C))
             (object (is-a D))
             (test (!= 2 2))))
   =>)
(agenda)
(make-instance a of A)
(make-instance c of C)
(agenda)
(make-instance b of B)
(make-instance d of D)
(agenda)
(clear) ; Case 4b
(load* "attchtst3.clp")

(defrule pass-fail-pass "Case 4b"
   (not (and (object (is-a A))
             (not (object (is-a B)))
             (test (= 1 1))))
   =>)

(defrule pass-pass-pass "Case 4b"
   (not (and (object (is-a C))
             (not (object (is-a D)))
             (test (!= 2 2))))
   =>)
(agenda)
(make-instance a of A)
(make-instance c of C)
(agenda)
(make-instance b of B)
(make-instance d of D)
(agenda)
(clear) ; Case 4c
(load* "attchtst3.clp")

(defrule pass-pass-fail "Case 4c"
   (not (and (object (is-a A))
             (exists (object (is-a B)))
             (test (= 1 1))))
   =>)

(defrule pass-pass-pass "Case 4c"
   (not (and (object (is-a C))
             (exists (object (is-a D)))
             (test (!= 2 2))))
   =>)
(agenda)
(make-instance a of A)
(make-instance c of C)
(agenda)
(make-instance b of B)
(make-instance d of D)
(agenda)
(clear) ; Case 4d
(load* "attchtst3.clp")

(defrule fail-fail-pass "Case 4d"
   (exists (and (object (is-a A))
                (object (is-a B))
                (test (= 1 1))))
   =>)

(defrule fail-fail-fail "Case 4d"
   (exists (and (object (is-a C))
                (object (is-a D))
                (test (!= 2 2))))
   =>)
(agenda)
(make-instance a of A)
(make-instance c of C)
(agenda)
(make-instance b of B)
(make-instance d of D)
(agenda)
(clear) ; Case 4e
(load* "attchtst3.clp")

(defrule fail-pass-fail "Case 4e"
   (exists (and (object (is-a A))
                (not (object (is-a B)))
                (test (= 1 1))))
   =>)

(defrule fail-fail-fail "Case 4e"
   (exists (and (object (is-a C))
                (not (object (is-a D)))
                (test (!= 2 2))))
   =>)
(agenda)
(make-instance a of A)
(make-instance c of C)
(agenda)
(make-instance b of B)
(make-instance d of D)
(agenda)
(clear) ; Case 4f
(load* "attchtst3.clp")

(defrule fail-fail-pass "Case 4f"
   (exists (and (object (is-a A))
                (exists (object (is-a B)))
                (test (= 1 1))))
   =>)

(defrule fail-fail-fail "Case 4f"
   (exists (and (object (is-a C))
                (exists (object (is-a D)))
                (test (!= 2 2))))
   =>)
(agenda)
(make-instance a of A)
(make-instance c of C)
(agenda)
(make-instance b of B)
(make-instance d of D)
(agenda)
(clear) ; Case 4g
(load* "attchtst3.clp")

(defrule pass-fail-fail-pass "Case 4g"
   (not (and (not (and (x)
                       (y)))
             (object (is-a A))
             (test (= 1 1))))
   =>)

(defrule pass-pass-pass-pass "Case 4g"
   (not (and (not (and (z)
                       (w)))
             (object (is-a B))
             (test (!= 2 2))))
   =>)
(agenda)
(make-instance a of A)
(make-instance b of B)
(agenda)
(assert (x) (z))
(agenda)
(assert (y) (w))
(agenda)
(clear) ; Case 4h
(load* "attchtst3.clp")

(defrule fail-pass-pass-pass "Case 4h"
   (not (and (not (and (x)
                       (y)))
             (not (object (is-a A)))
             (test (= 1 1))))
   =>)

(defrule pass-pass-pass-pass "Case 4h"
   (not (and (not (and (z)
                       (w)))
             (not (object (is-a B)))
             (test (!= 2 2))))
   =>)
(agenda)
(make-instance a of A)
(make-instance b of B)
(agenda)
(assert (x) (z))
(agenda)
(assert (y) (w))
(agenda)
(clear) ; Case 4i
(load* "attchtst3.clp")

(defrule pass-fail-fail-pass "Case 4i"
   (not (and (not (and (x)
                       (y)))
             (exists (object (is-a A)))
             (test (= 1 1))))
   =>)

(defrule pass-pass-pass-pass "Case 4i"
   (not (and (not (and (z)
                       (w)))
             (exists (object (is-a B)))
             (test (!= 2 2))))
   =>)
(agenda)
(make-instance a of A)
(make-instance b of B)
(agenda)
(assert (x) (z))
(agenda)
(assert (y) (w))
(agenda)
(clear) ; Case 4j
(load* "attchtst3.clp")

(defrule fail-pass-pass-fail "Case 4j"
   (exists (and (not (and (x)
                          (y)))
                (object (is-a A))
                (test (= 1 1))))
   =>)

(defrule fail-fail-fail-fail "Case 4j"
   (exists (and (not (and (z)
                          (w)))
                (object (is-a B))
                (test (!= 2 2))))
   =>)
(agenda)
(make-instance a of A)
(make-instance b of B)
(agenda)
(assert (x) (z))
(agenda)
(assert (y) (w))
(agenda)
(clear) ; Case 4k
(load* "attchtst3.clp")

(defrule pass-fail-fail-fail "Case 4k"
   (exists (and (not (and (x)
                          (y)))
                (not (object (is-a A)))
                (test (= 1 1))))
   =>)

(defrule fail-fail-fail-fail "Case 4k"
   (exists (and (not (and (z)
                          (w)))
                (not (object (is-a B)))
                (test (!= 2 2))))
   =>)
(agenda)
(make-instance a of A)
(make-instance b of B)
(agenda)
(assert (x) (z))
(agenda)
(assert (y) (w))
(agenda)
(clear) ; Case 4l
(load* "attchtst3.clp")

(defrule fail-pass-pass-fail "Case 4l"
   (exists (and (not (and (x)
                          (y)))
                (exists (object (is-a A)))
                (test (= 1 1))))
   =>)

(defrule fail-fail-fail-fail "Case 4l"
   (exists (and (not (and (z)
                          (w)))
                (exists (object (is-a B)))
                (test (!= 2 2))))
   =>)
(agenda)
(make-instance a of A)
(make-instance b of B)
(agenda)
(assert (x) (z))
(agenda)
(assert (y) (w))
(agenda)
(clear) ; Case 5a
(load* "attchtst3.clp")

(defrule fail-pass-fail "Case 5a"
   (object (is-a A))
   (not (and (object (is-a B))
             (test (= 1 1))))
   =>)

(defrule fail-pass-pass "Case 5a"
   (object (is-a C))
   (not (and (object (is-a D))
             (test (!= 2 2))))
   =>)
(agenda)
(make-instance a of A)
(make-instance c of C)
(agenda)
(make-instance b of B)
(make-instance d of D)
(agenda)
(clear) ; Case 5b
(load* "attchtst3.clp")

(defrule fail-fail-pass "Case 5b"
   (object (is-a A))
   (not (and (not (object (is-a B)))
             (test (= 1 1))))
   =>)

(defrule fail-pass-pass "Case 5b"
   (object (is-a C))
   (not (and (not (object (is-a D)))
             (test (!= 2 2))))
   =>)
(agenda)
(make-instance a of A)
(make-instance c of C)
(agenda)
(make-instance b of B)
(make-instance d of D)
(agenda)
(clear) ; Case 5c
(load* "attchtst3.clp")

(defrule fail-pass-fail "Case 5c"
   (object (is-a A))
   (not (and (exists (object (is-a B)))
             (test (= 1 1))))
   =>)

(defrule fail-pass-pass "Case 5c"
   (object (is-a C))
   (not (and (exists (object (is-a D)))
             (test (!= 2 2))))
   =>)
(agenda)
(make-instance a of A)
(make-instance c of C)
(agenda)
(make-instance b of B)
(make-instance d of D)
(agenda)
(clear) ; Case 5d
(load* "attchtst3.clp")

(defrule fail-fail-pass "Case 5d"
   (object (is-a A))
   (exists (and (object (is-a B))
                (test (= 1 1))))
   =>)

(defrule fail-fail-fail "Case 5d"
   (object (is-a C))
   (exists (and (object (is-a D))
                (test (!= 2 2))))
   =>)
(agenda)
(make-instance a of A)
(make-instance c of C)
(agenda)
(make-instance b of B)
(make-instance d of D)
(agenda)
(clear) ; Case 5e
(load* "attchtst3.clp")

(defrule fail-pass-fail "Case 5e"
   (object (is-a A))
   (exists (and (not (object (is-a B)))
                (test (= 1 1))))
   =>)

(defrule fail-fail-fail "Case 5e"
   (object (is-a C))
   (exists (and (not (object (is-a D)))
                (test (!= 2 2))))
   =>)
(agenda)
(make-instance a of A)
(make-instance c of C)
(agenda)
(make-instance b of B)
(make-instance d of D)
(agenda)
(clear) ; Case 5f
(load* "attchtst3.clp")

(defrule fail-fail-pass "Case 5f"
   (object (is-a A))
   (exists (and (exists (object (is-a B)))
                (test (= 1 1))))
   =>)

(defrule fail-fail-fail "Case 5f"
   (object (is-a C))
   (exists (and (exists (object (is-a D)))
                (test (!= 2 2))))
   =>)
(agenda)
(make-instance a of A)
(make-instance c of C)
(agenda)
(make-instance b of B)
(make-instance d of D)
(agenda)
(clear) ; Case 5g
(load* "attchtst3.clp")

(defrule fail-pass-both "Case 5g"
   (object (is-a A) (sa ?x))
   (not (and (object (is-a B) (sb ?x))
             (test (> ?x 0))))
   =>)

(defrule fail-pass-pass "Case 5g"
   (object (is-a C) (sc ?x))
   (not (and (object (is-a D) (sd ?x))
             (test (< ?x 0))))
   =>)
(agenda)
(make-instance a1 of A (sa 1))
(make-instance c1 of C (sc 1))
(make-instance a2 of A (sa 2))
(make-instance c2 of C (sc 2))
(agenda)
(make-instance b1 of B (sb 1))
(make-instance d1 of D (sd 1))
(agenda)
(clear) ; Case 5h
(load* "attchtst3.clp")

(defrule fail-fail-both "Case 5h"
   (object (is-a A) (sa ?x))
   (not (and (not (object (is-a B) (sb ?x)))
             (test (> ?x 0))))
   =>)

(defrule fail-pass-pass "Case 5h"
   (object (is-a C) (sc ?x))
   (not (and (not (object (is-a D) (sd ?x)))
             (test (< ?x 0))))
   =>)
(agenda)
(make-instance a1 of A (sa 1)) 
(make-instance c1 of C (sc 1))
(make-instance a2 of A (sa 2))
(make-instance c2 of C (sc 2))
(agenda)
(make-instance b1 of B (sb 1))
(make-instance d1 of D (sd 1))
(agenda)
(clear) ; Case 5i
(load* "attchtst3.clp")

(defrule fail-pass-both "Case 5i"
   (object (is-a A) (sa ?x))
   (not (and (exists (object (is-a B) (sb ?x)))
             (test (> ?x 0))))
   =>)

(defrule fail-pass-pass "Case 5i"
   (object (is-a C) (sc ?x))
   (not (and (exists (object (is-a D) (sd ?x)))
             (test (< ?x 0))))
   =>)
(agenda)
(make-instance a1 of A (sa 1)) 
(make-instance c1 of C (sc 1))
(make-instance a2 of A (sa 2)) 
(make-instance c2 of C (sc 2))
(agenda)
(make-instance b1 of B (sb 1)) 
(make-instance d1 of D (sd 1))
(agenda)
(clear) ; Case 5j
(load* "attchtst3.clp")

(defrule fail-fail-both "Case 5j"
   (object (is-a A) (sa ?x))
   (exists (and (object (is-a B) (sb ?x))
                (test (> ?x 0))))
   =>)

(defrule fail-fail-fail "Case 5j"
   (object (is-a C) (sc ?x))
   (exists (and (object (is-a D) (sd ?x))
                (test (< ?x 0))))
   =>)
(agenda)
(make-instance a1 of A (sa 1)) 
(make-instance c1 of C (sc 1))
(make-instance a2 of A (sa 2)) 
(make-instance c2 of C (sc 2))
(agenda)
(make-instance b1 of B (sb 1)) 
(make-instance d1 of D (sd 1))
(agenda)
(clear) ; Case 5k
(load* "attchtst3.clp")

(defrule fail-pass-both "Case 5k"
   (object (is-a A) (sa ?x))
   (exists (and (not (object (is-a B) (sb ?x)))
                (test (> ?x 0))))
   =>)

(defrule fail-fail-fail "Case 5k"
   (object (is-a C) (sc ?x))
   (exists (and (not (object (is-a D) (sd ?x)))
                (test (< ?x 0))))
   =>)
(agenda)
(make-instance a1 of A (sa 1)) 
(make-instance c1 of C (sc 1))
(make-instance a2 of A (sa 2)) 
(make-instance c2 of C (sc 2))
(agenda)
(make-instance b1 of B (sb 1)) 
(make-instance d1 of D (sd 1))
(agenda)
(clear) ; Case 5l
(load* "attchtst3.clp")

(defrule fail-fail-both "Case 5l"
   (object (is-a A) (sa ?x))
   (exists (and (exists (object (is-a B) (sb ?x)))
                (test (> ?x 0))))
   =>)

(defrule fail-fail-fail "Case 5l"
   (object (is-a C) (sc ?x))
   (exists (and (exists (object (is-a D) (sd ?x)))
                (test (< ?x 0))))
   =>)
(agenda)
(make-instance a1 of A (sa 1)) 
(make-instance c1 of C (sc 1))
(make-instance a2 of A (sa 2)) 
(make-instance c2 of C (sc 2))
(agenda)
(make-instance b1 of B (sb 1)) 
(make-instance d1 of D (sd 1))
(agenda)
(clear) ; Case 5m
(load* "attchtst3.clp")

(defrule fail-pass-pass-pass "Case 5m"
   (not (and (not (and (object (is-a A))
                       (object (is-a B))))
             (not (and (object (is-a C))
                       (test (= 1 1))))))
   =>)

(defrule fail-fail-fail-pass "Case 5m"
   (not (and (not (and (object (is-a D))
                       (object (is-a E))))
             (not (and (object (is-a F))
                       (test (!= 2 2))))))
   =>)
(agenda)
(make-instance c of C)
(make-instance f of F)
(agenda)
(make-instance a of A)
(make-instance d of D)
(agenda)
(make-instance b of B)
(make-instance e of E)
(agenda)
(clear) ; Case 5n
(load* "attchtst3.clp")

(defrule pass-fail-fail-pass "Case 5n"
   (not (and (not (and (object (is-a A))
                       (object (is-a B))))
             (exists (and (object (is-a C))
                          (test (= 1 1))))))
   =>)

(defrule pass-pass-pass-pass "Case 5n"
   (not (and (not (and (object (is-a D))
                       (object (is-a E))))
             (exists (and (object (is-a F))
                          (test (!= 2 2))))))
   =>)
(agenda)
(make-instance c of C)
(make-instance f of F)
(agenda)
(make-instance a of A)
(make-instance d of D)
(agenda)
(make-instance b of B)
(make-instance e of E)
(agenda)
(clear) ; Case 5o
(load* "attchtst3.clp")

(defrule fail-pass-both "Case 5o"
   (x)
   (object (is-a A) (sa ?x))
   (not (and (object (is-a B) (sb ?x))
             (test (> ?x 0))))
   =>)

(defrule fail-pass-pass "Case 5o"
   (x)
   (object (is-a C) (sc ?x))
   (not (and (object (is-a D) (sd ?x))
             (test (< ?x 0))))
   =>)
(assert (x))
(agenda)
(make-instance a1 of A (sa 1)) 
(make-instance c1 of C (sc 1))
(make-instance a2 of A (sa 2)) 
(make-instance c2 of C (sc 2))
(agenda)
(make-instance b1 of B (sb 1)) 
(make-instance d1 of D (sd 1))
(agenda)
(clear) ; Case 5p
(load* "attchtst3.clp")

(defrule fail-fail-both "Case 5p"
   (x)
   (object (is-a A) (sa ?x))
   (not (and (not (object (is-a B) (sb ?x)))
             (test (> ?x 0))))
   =>)

(defrule fail-pass-pass "Case 5p"
   (x)
   (object (is-a C) (sc ?x))
   (not (and (not (object (is-a D) (sd ?x)))
             (test (< ?x 0))))
   =>)
(assert (x))
(agenda)
(make-instance a1 of A (sa 1)) 
(make-instance c1 of C (sc 1))
(make-instance a2 of A (sa 2)) 
(make-instance c2 of C (sc 2))
(agenda)
(make-instance b1 of B (sb 1)) 
(make-instance d1 of D (sd 1))
(agenda)
(clear) ; Case 5q
(load* "attchtst3.clp")

(defrule fail-pass-both "Case 5q"
   (x)
   (object (is-a A) (sa ?x))
   (not (and (exists (object (is-a B) (sb ?x)))
             (test (> ?x 0))))
   =>)

(defrule fail-pass-pass "Case 5q"
   (x)
   (object (is-a C) (sc ?x))
   (not (and (exists (object (is-a D) (sd ?x)))
             (test (< ?x 0))))
   =>)
(assert (x))
(agenda)
(make-instance a1 of A (sa 1)) 
(make-instance c1 of C (sc 1))
(make-instance a2 of A (sa 2)) 
(make-instance c2 of C (sc 2))
(agenda)
(make-instance b1 of B (sb 1)) 
(make-instance d1 of D (sd 1))
(agenda)
(clear) ; Case 5r
(load* "attchtst3.clp")

(defrule fail-fail-both "Case 5r"
   (x)
   (object (is-a A) (sa ?x))
   (exists (and (object (is-a B) (sb ?x))
                (test (> ?x 0))))
   =>)

(defrule fail-fail-fail "Case 5r"
   (x)
   (object (is-a C) (sc ?x))
   (exists (and (object (is-a D) (sd ?x))
                (test (< ?x 0))))
   =>)
(assert (x))
(agenda)
(make-instance a1 of A (sa 1)) 
(make-instance c1 of C (sc 1))
(make-instance a2 of A (sa 2)) 
(make-instance c2 of C (sc 2))
(agenda)
(make-instance b1 of B (sb 1)) 
(make-instance d1 of D (sd 1))
(agenda)
(clear) ; Case 5s
(load* "attchtst3.clp")

(defrule fail-pass-both "Case 5s"
   (x)
   (object (is-a A) (sa ?x))
   (exists (and (not (object (is-a B) (sb ?x)))
                (test (> ?x 0))))
   =>)

(defrule fail-fail-fail "Case 5s"
   (x)
   (object (is-a C) (sc ?x))
   (exists (and (not (object (is-a D) (sd ?x)))
                (test (< ?x 0))))
   =>)
(assert (x))
(agenda)
(make-instance a1 of A (sa 1)) 
(make-instance c1 of C (sc 1))
(make-instance a2 of A (sa 2)) 
(make-instance c2 of C (sc 2))
(agenda)
(make-instance b1 of B (sb 1)) 
(make-instance d1 of D (sd 1))
(agenda)
(clear) ; Case 5t
(load* "attchtst3.clp")

(defrule fail-fail-both "Case 5t"
   (x)
   (object (is-a A) (sa ?x))
   (exists (and (exists (object (is-a B) (sb ?x)))
                (test (> ?x 0))))
   =>)

(defrule fail-fail-fail "Case 5t"
   (x)
   (object (is-a C) (sc ?x))
   (exists (and (exists (object (is-a D) (sd ?x)))
                (test (< ?x 0))))
   =>)
(assert (x))
(agenda)
(make-instance a1 of A (sa 1)) 
(make-instance c1 of C (sc 1))
(make-instance a2 of A (sa 2)) 
(make-instance c2 of C (sc 2))
(agenda)
(make-instance b1 of B (sb 1)) 
(make-instance d1 of D (sd 1))
(agenda)
(clear) ; Case 6a
(load* "attchtst3.clp")

(defrule fail-pass-fail-fail-pass "Case 6a"
   (object (is-a A))
   (not (and (not (and (object (is-a B))
                       (object (is-a C))))
             (test (= 1 1))
             (object (is-a D))))
   =>)

(defrule fail-pass-pass-pass-pass "Case 6a"
   (object (is-a E))
   (not (and (not (and (object (is-a F))
                       (object (is-a G))))
             (test (!= 2 2))
             (object (is-a H))))
   =>)
(agenda)
(make-instance a of A)
(make-instance e of E)
(agenda)
(make-instance d of D)
(make-instance h of H)
(agenda)
(make-instance b of B)
(make-instance f of F)
(agenda)
(make-instance c of C)
(make-instance g of G)
(agenda)
(clear) ; Case 6b
(load* "attchtst3.clp")

(defrule fail-pass-pass-pass-fail "Case 6b"
   (object (is-a A))
   (not (and (exists (and (object (is-a B))
                          (object (is-a C))))
             (test (= 1 1))
             (object (is-a D))))
   =>)

(defrule fail-pass-pass-pass-pass "Case 6b"
   (object (is-a E))
   (not (and (exists (and (object (is-a F))
                          (object (is-a G))))
             (test (!= 2 2))
             (object (is-a H))))
   =>)
(agenda)
(make-instance a of A)
(make-instance e of E)
(agenda)
(make-instance d of D)
(make-instance h of H)
(agenda)
(make-instance b of B)
(make-instance f of F)
(agenda)
(make-instance c of C)
(make-instance g of G)
(agenda)
(clear) ; Case 6c
(load* "attchtst3.clp")

(defrule fail-fail-pass-pass-fail "Case 6c"
   (object (is-a A))
   (exists (and (not (and (object (is-a B))
                          (object (is-a C))))
                (test (= 1 1))
                (object (is-a D))))
   =>)

(defrule fail-fail-fail-fail-fail "Case 6c"
   (object (is-a E))
   (exists (and (not (and (object (is-a F))
                          (object (is-a G))))
                (test (!= 2 2))
                (object (is-a H))))
   =>)
(agenda)
(make-instance a of A)
(make-instance e of E)
(agenda)
(make-instance d of D)
(make-instance h of H)
(agenda)
(make-instance b of B)
(make-instance f of F)
(agenda)
(make-instance c of C)
(make-instance g of G)
(agenda)
(clear) ; Case 6d
(load* "attchtst3.clp")

(defrule fail-fail-fail-fail-pass "Case 6d"
   (object (is-a A))
   (exists (and (exists (and (object (is-a B))
                             (object (is-a C))))
                (test (= 1 1))
                (object (is-a D))))
   =>)

(defrule fail-fail-fail-fail-fail "Case 6d"
   (object (is-a E))
   (exists (and (exists (and (object (is-a F))
                             (object (is-a G))))
                (test (!= 2 2))
                (object (is-a H))))
   =>)
(agenda)
(make-instance a of A)
(make-instance e of E)
(agenda)
(make-instance d of D)
(make-instance h of H)
(agenda)
(make-instance b of B)
(make-instance f of F)
(agenda)
(make-instance c of C)
(make-instance g of G)
(agenda)
(clear) ; Case 6e
(load* "attchtst3.clp")

(defrule fail-pass-fail-fail-both "Case 6e"
   (object (is-a A) (sa ?x))
   (not (and (not (and (object (is-a B) (sb ?x))
                       (object (is-a C) (sc ?x))))
             (test (= 1 1))
             (object (is-a D) (sd ?x))))
   =>)

(defrule fail-pass-pass-pass-pass "Case 6e"
   (object (is-a E) (se ?x))
   (not (and (not (and (object (is-a F) (sf ?x))
                       (object (is-a G) (sg ?x))))
             (test (!= 2 2))
             (object (is-a H) (sh ?x))))
   =>)
(agenda)
(make-instance a1 of A (sa 1))
(make-instance e1 of E (se 1))
(make-instance a2 of A (sa 2))
(make-instance e2 of E (se 2))
(agenda)
(make-instance d1 of D (sd 1)) 
(make-instance h1 of H (sh 1))
(make-instance d2 of D (sd 2))
(make-instance h2 of H (sh 2))
(agenda)
(make-instance b1 of B (sb 1)) 
(make-instance f1 of F (sf 1))
(agenda)
(make-instance c1 of C (sc 1)) 
(make-instance g1 of G (sg 1))
(agenda)
(clear) ; Case 6f
(load* "attchtst3.clp")

(defrule fail-pass-pass-pass-both "Case 6f"
   (object (is-a A) (sa ?x))
   (not (and (exists (and (object (is-a B) (sb ?x))
                          (object (is-a C) (sc ?x))))
             (test (= 1 1))
             (object (is-a D) (sd ?x))))
   =>)

(defrule fail-pass-pass-pass-pass "Case 6f"
   (object (is-a E) (se ?x))
   (not (and (exists (and (object (is-a F) (sf ?x))
                          (object (is-a G) (sg ?x))))
             (test (!= 2 2))
             (object (is-a H) (sh ?x))))
   =>)
(agenda)
(make-instance a1 of A (sa 1))
(make-instance e1 of E (se 1))
(make-instance a2 of A (sa 2))
(make-instance e2 of E (se 2))
(agenda)
(make-instance d1 of D (sd 1)) 
(make-instance h1 of H (sh 1))
(make-instance d2 of D (sd 2))
(make-instance h2 of H (sh 2))
(agenda)
(make-instance b1 of B (sb 1)) 
(make-instance f1 of F (sf 1))
(agenda)
(make-instance c1 of C (sc 1)) 
(make-instance g1 of G (sg 1))
(agenda)
(clear) ; Case 6g
(load* "attchtst3.clp")

(defrule fail-fail-pass-pass-both "Case 6g"
   (object (is-a A) (sa ?x))
   (exists (and (not (and (object (is-a B) (sb ?x))
                          (object (is-a C) (sc ?x))))
                (test (= 1 1))
                (object (is-a D) (sd ?x))))
   =>)

(defrule fail-fail-fail-fail-fail "Case 6g"
   (object (is-a E) (se ?x))
   (exists (and (not (and (object (is-a F) (sf ?x))
                          (object (is-a G) (sg ?x))))
                (test (!= 2 2))
                (object (is-a H) (sh ?x))))
   =>)
(agenda)
(make-instance a1 of A (sa 1))
(make-instance e1 of E (se 1))
(make-instance a2 of A (sa 2))
(make-instance e2 of E (se 2))
(agenda)
(make-instance d1 of D (sd 1)) 
(make-instance h1 of H (sh 1))
(make-instance d2 of D (sd 2))
(make-instance h2 of H (sh 2))
(agenda)
(make-instance b1 of B (sb 1)) 
(make-instance f1 of F (sf 1))
(agenda)
(make-instance c1 of C (sc 1)) 
(make-instance g1 of G (sg 1))
(agenda)
(clear) ; Case 6h
(load* "attchtst3.clp")

(defrule fail-fail-fail-fail-both "Case 6h"
   (object (is-a A) (sa ?x))
   (exists (and (exists (and (object (is-a B) (sb ?x))
                             (object (is-a C) (sc ?x))))
                (test (= 1 1))
                (object (is-a D) (sd ?x))))
   =>)

(defrule fail-fail-fail-fail-fail "Case 6h"
   (object (is-a E) (se ?x))
   (exists (and (exists (and (object (is-a F) (sf ?x))
                             (object (is-a G) (sg ?x))))
                (test (!= 2 2))
                (object (is-a H) (sh ?x))))
   =>)
(agenda)
(make-instance a1 of A (sa 1))
(make-instance e1 of E (se 1))
(make-instance a2 of A (sa 2))
(make-instance e2 of E (se 2))
(agenda)
(make-instance d1 of D (sd 1)) 
(make-instance h1 of H (sh 1))
(make-instance d2 of D (sd 2))
(make-instance h2 of H (sh 2))
(agenda)
(make-instance b1 of B (sb 1)) 
(make-instance f1 of F (sf 1))
(agenda)
(make-instance c1 of C (sc 1)) 
(make-instance g1 of G (sg 1))
(agenda)
(clear) ; Case 6i
(load* "attchtst3.clp")

(defrule fail-pass-fail-fail-both "Case 6i"
   (x)
   (object (is-a A) (sa ?x))
   (not (and (not (and (object (is-a B) (sb ?x))
                       (object (is-a C) (sc ?x))))
             (test (= 1 1))
             (object (is-a D) (sd ?x))))
   =>)

(defrule fail-pass-pass-pass-pass "Case 6i"
   (x)
   (object (is-a E) (se ?x))
   (not (and (not (and (object (is-a F) (sf ?x))
                       (object (is-a G) (sg ?x))))
             (test (!= 2 2))
             (object (is-a H) (sh ?x))))
   =>)
(assert (x))
(agenda)
(make-instance a1 of A (sa 1))
(make-instance e1 of E (se 1))
(make-instance a2 of A (sa 2))
(make-instance e2 of E (se 2))
(agenda)
(make-instance d1 of D (sd 1)) 
(make-instance h1 of H (sh 1))
(make-instance d2 of D (sd 2))
(make-instance h2 of H (sh 2))
(agenda)
(make-instance b1 of B (sb 1)) 
(make-instance f1 of F (sf 1))
(agenda)
(make-instance c1 of C (sc 1)) 
(make-instance g1 of G (sg 1))
(agenda)
(clear) ; Case 6j
(load* "attchtst3.clp")

(defrule fail-pass-pass-pass-both "Case 6j"
   (x)
   (object (is-a A) (sa ?x))
   (not (and (exists (and (object (is-a B) (sb ?x))
                          (object (is-a C) (sc ?x))))
             (test (= 1 1))
             (object (is-a D) (sd ?x))))
   =>)

(defrule fail-pass-pass-pass-pass "Case 6j"
   (x)
   (object (is-a E) (se ?x))
   (not (and (exists (and (object (is-a F) (sf ?x))
                          (object (is-a G) (sg ?x))))
             (test (!= 2 2))
             (object (is-a H) (sh ?x))))
   =>)
(assert (x))
(agenda)
(make-instance a1 of A (sa 1))
(make-instance e1 of E (se 1))
(make-instance a2 of A (sa 2))
(make-instance e2 of E (se 2))
(agenda)
(make-instance d1 of D (sd 1)) 
(make-instance h1 of H (sh 1))
(make-instance d2 of D (sd 2))
(make-instance h2 of H (sh 2))
(agenda)
(make-instance b1 of B (sb 1)) 
(make-instance f1 of F (sf 1))
(agenda)
(make-instance c1 of C (sc 1)) 
(make-instance g1 of G (sg 1))
(agenda)
(clear) ; Case 6k
(load* "attchtst3.clp")

(defrule fail-fail-pass-pass-both "Case 6k"
   (x)
   (object (is-a A) (sa ?x))
   (exists (and (not (and (object (is-a B) (sb ?x))
                          (object (is-a C) (sc ?x))))
                (test (= 1 1))
                (object (is-a D) (sd ?x))))
   =>)

(defrule fail-fail-fail-fail-fail "Case 6k"
   (x)
   (object (is-a E) (se ?x))
   (exists (and (not (and (object (is-a F) (sf ?x))
                          (object (is-a G) (sg ?x))))
                (test (!= 2 2))
                (object (is-a H) (sh ?x))))
   =>)
(assert (x))
(agenda)
(make-instance a1 of A (sa 1))
(make-instance e1 of E (se 1))
(make-instance a2 of A (sa 2))
(make-instance e2 of E (se 2))
(agenda)
(make-instance d1 of D (sd 1)) 
(make-instance h1 of H (sh 1))
(make-instance d2 of D (sd 2))
(make-instance h2 of H (sh 2))
(agenda)
(make-instance b1 of B (sb 1)) 
(make-instance f1 of F (sf 1))
(agenda)
(make-instance c1 of C (sc 1)) 
(make-instance g1 of G (sg 1))
(agenda)
(clear) ; Case 6l
(load* "attchtst3.clp")

(defrule fail-fail-fail-fail-both "Case 6l"
   (x)
   (object (is-a A) (sa ?x))
   (exists (and (exists (and (object (is-a B) (sb ?x))
                             (object (is-a C) (sc ?x))))
                (test (= 1 1))
                (object (is-a D) (sd ?x))))
   =>)

(defrule fail-fail-fail-fail-fail "Case 6l"
   (x)
   (object (is-a E) (se ?x))
   (exists (and (exists (and (object (is-a F) (sf ?x))
                             (object (is-a G) (sg ?x))))
                (test (!= 2 2))
                (object (is-a H) (sh ?x))))
   =>)
(assert (x))
(agenda)
(make-instance a1 of A (sa 1))
(make-instance e1 of E (se 1))
(make-instance a2 of A (sa 2))
(make-instance e2 of E (se 2))
(agenda)
(make-instance d1 of D (sd 1)) 
(make-instance h1 of H (sh 1))
(make-instance d2 of D (sd 2))
(make-instance h2 of H (sh 2))
(agenda)
(make-instance b1 of B (sb 1)) 
(make-instance f1 of F (sf 1))
(agenda)
(make-instance c1 of C (sc 1)) 
(make-instance g1 of G (sg 1))
(agenda)
(clear) ; Case 7a
(load* "attchtst3.clp")

(defrule fail-fail-fail-pass "Case 7a"
   (object (is-a A))
   (not (and (not (and (object (is-a B))
                       (object (is-a C))))
             (test (= 1 1))))
   =>)

(defrule fail-pass-pass-pass "Case 7a"
   (object (is-a E))
   (not (and (not (and (object (is-a F))
                       (object (is-a G))))
             (test (!= 2 2))))
   =>)
(agenda)
(make-instance a of A)
(make-instance e of E)
(agenda)
(make-instance b of B)
(make-instance f of F)
(agenda)
(make-instance c of C)
(make-instance g of G)
(agenda)
(clear) ; Case 7b
(load* "attchtst3.clp")

(defrule fail-pass-pass-fail "Case 7b"
   (object (is-a A))
   (not (and (exists (and (object (is-a B))
                          (object (is-a C))))
             (test (= 1 1))))
   =>)

(defrule fail-pass-pass-pass "Case 7b"
   (object (is-a E))
   (not (and (exists (and (object (is-a F))
                          (object (is-a G))))
             (test (!= 2 2))))
   =>)
(agenda)
(make-instance a of A)
(make-instance e of E)
(agenda)
(make-instance b of B)
(make-instance f of F)
(agenda)
(make-instance c of C)
(make-instance g of G)
(agenda)
(clear) ; Case 7c
(load* "attchtst3.clp")

(defrule fail-pass-pass-fail "Case 7c"
   (object (is-a A))
   (exists (and (not (and (object (is-a B))
                          (object (is-a C))))
                (test (= 1 1))))
   =>)

(defrule fail-fail-fail-fail "Case 7c"
   (object (is-a E))
   (exists (and (not (and (object (is-a F))
                          (object (is-a G))))
                (test (!= 2 2))))
   =>)
(agenda)
(make-instance a of A)
(make-instance e of E)
(agenda)
(make-instance b of B)
(make-instance f of F)
(agenda)
(make-instance c of C)
(make-instance g of G)
(agenda)
(clear) ; Case 7d
(load* "attchtst3.clp")

(defrule fail-fail-fail-pass "Case 7d"
   (object (is-a A))
   (exists (and (exists (and (object (is-a B))
                             (object (is-a C))))
                (test (= 1 1))))
   =>)

(defrule fail-fail-fail-fail "Case 7d"
   (object (is-a E))
   (exists (and (exists (and (object (is-a F))
                             (object (is-a G))))
                (test (!= 2 2))))
   =>)
(agenda)
(make-instance a of A)
(make-instance e of E)
(agenda)
(make-instance b of B)
(make-instance f of F)
(agenda)
(make-instance c of C)
(make-instance g of G)
(agenda)
(clear) ; Case 7e
(load* "attchtst3.clp")

(defrule fail-fail-fail-both "Case 7e"
   (object (is-a A) (sa ?x))
   (not (and (not (and (object (is-a B) (sb ?x))
                       (object (is-a C) (sc ?x))))
             (test (= 1 1))))
   =>)

(defrule fail-pass-pass-pass "Case 7e"
   (object (is-a E) (se ?x))
   (not (and (not (and (object (is-a F) (sf ?x))
                       (object (is-a G) (sg ?x))))
             (test (!= 2 2))))
   =>)
(agenda)
(make-instance a1 of A (sa 1))
(make-instance e1 of E (se 1)) 
(make-instance a2 of A (sa 2))
(make-instance e2 of E (se 2))
(agenda)
(make-instance b1 of B (sb 1))
(make-instance f1 of F (sf 1))
(agenda)
(make-instance c1 of C (sc 1)) 
(make-instance g1 of G (sg 1))
(agenda)
(clear) ; Case 7f
(load* "attchtst3.clp")

(defrule fail-pass-pass-both "Case 7f"
   (object (is-a A) (sa ?x))
   (not (and (exists (and (object (is-a B) (sb ?x))
                          (object (is-a C) (sc ?x))))
             (test (= 1 1))))
   =>)

(defrule fail-pass-pass-pass "Case 7f"
   (object (is-a E) (se ?x))
   (not (and (exists (and (object (is-a F) (sf ?x))
                          (object (is-a G) (sg ?x))))
             (test (!= 2 2))))
   =>)
(agenda)
(make-instance a1 of A (sa 1))
(make-instance e1 of E (se 1)) 
(make-instance a2 of A (sa 2))
(make-instance e2 of E (se 2))
(agenda)
(make-instance b1 of B (sb 1))
(make-instance f1 of F (sf 1))
(agenda)
(make-instance c1 of C (sc 1)) 
(make-instance g1 of G (sg 1))
(agenda)
(clear) ; Case 7g
(load* "attchtst3.clp")

(defrule fail-pass-pass-both "Case 7g"
   (object (is-a A) (sa ?x))
   (exists (and (not (and (object (is-a B) (sb ?x))
                          (object (is-a C) (sc ?x))))
                (test (= 1 1))))
   =>)

(defrule fail-fail-fail-fail "Case 7g"
   (object (is-a E) (se ?x))
   (exists (and (not (and (object (is-a F) (sf ?x))
                          (object (is-a G) (sg ?x))))
                (test (!= 2 2))))
   =>)
(agenda)
(make-instance a1 of A (sa 1))
(make-instance e1 of E (se 1)) 
(make-instance a2 of A (sa 2))
(make-instance e2 of E (se 2))
(agenda)
(make-instance b1 of B (sb 1))
(make-instance f1 of F (sf 1))
(agenda)
(make-instance c1 of C (sc 1)) 
(make-instance g1 of G (sg 1))
(agenda)
(clear) ; Case 7h
(load* "attchtst3.clp")

(defrule fail-fail-fail-both "Case 7h"
   (object (is-a A) (sa ?x))
   (exists (and (exists (and (object (is-a B) (sb ?x))
                             (object (is-a C) (sc ?x))))
                (test (= 1 1))))
   =>)

(defrule fail-fail-fail-fail "Case 7h"
   (object (is-a E) (se ?x))
   (exists (and (exists (and (object (is-a F) (sf ?x))
                             (object (is-a G) (sg ?x))))
                (test (!= 2 2))))
   =>)
(agenda)
(make-instance a1 of A (sa 1))
(make-instance e1 of E (se 1)) 
(make-instance a2 of A (sa 2))
(make-instance e2 of E (se 2))
(agenda)
(make-instance b1 of B (sb 1))
(make-instance f1 of F (sf 1))
(agenda)
(make-instance c1 of C (sc 1)) 
(make-instance g1 of G (sg 1))
(agenda)
(clear) ; Case 7i
(load* "attchtst3.clp")

(defrule fail-fail-fail-both "Case 7i"
   (x)
   (object (is-a A) (sa ?x))
   (not (and (not (and (object (is-a B) (sb ?x))
                       (object (is-a C) (sc ?x))))
             (test (= 1 1))))
   =>)

(defrule fail-pass-pass-pass "Case 7i"
   (x)
   (object (is-a E) (se ?x))
   (not (and (not (and (object (is-a F) (sf ?x))
                       (object (is-a G) (sg ?x))))
             (test (!= 2 2))))
   =>)
(assert (x))
(agenda)
(make-instance a1 of A (sa 1))
(make-instance e1 of E (se 1)) 
(make-instance a2 of A (sa 2))
(make-instance e2 of E (se 2))
(agenda)
(make-instance b1 of B (sb 1))
(make-instance f1 of F (sf 1))
(agenda)
(make-instance c1 of C (sc 1)) 
(make-instance g1 of G (sg 1))
(agenda)
(clear) ; Case 7j
(load* "attchtst3.clp")

(defrule fail-pass-pass-both "Case 7j"
   (x)
   (object (is-a A) (sa ?x))
   (not (and (exists (and (object (is-a B) (sb ?x))
                          (object (is-a C) (sc ?x))))
             (test (= 1 1))))
   =>)

(defrule fail-pass-pass-pass "Case 7j"
   (x)
   (object (is-a E) (se ?x))
   (not (and (exists (and (object (is-a F) (sf ?x))
                          (object (is-a G) (sg ?x))))
             (test (!= 2 2))))
   =>)
(assert (x))
(agenda)
(make-instance a1 of A (sa 1))
(make-instance e1 of E (se 1)) 
(make-instance a2 of A (sa 2))
(make-instance e2 of E (se 2))
(agenda)
(make-instance b1 of B (sb 1))
(make-instance f1 of F (sf 1))
(agenda)
(make-instance c1 of C (sc 1)) 
(make-instance g1 of G (sg 1))
(agenda)
(clear) ; Case 7k
(load* "attchtst3.clp")

(defrule fail-pass-pass-both "Case 7k"
   (x)
   (object (is-a A) (sa ?x))
   (exists (and (not (and (object (is-a B) (sb ?x))
                          (object (is-a C) (sc ?x))))
                (test (= 1 1))))
   =>)

(defrule fail-fail-fail-fail "Case 7k"
   (x)
   (object (is-a E) (se ?x))
   (exists (and (not (and (object (is-a F) (sf ?x))
                          (object (is-a G) (sg ?x))))
                (test (!= 2 2))))
   =>)
(assert (x))
(agenda)
(make-instance a1 of A (sa 1))
(make-instance e1 of E (se 1)) 
(make-instance a2 of A (sa 2))
(make-instance e2 of E (se 2))
(agenda)
(make-instance b1 of B (sb 1))
(make-instance f1 of F (sf 1))
(agenda)
(make-instance c1 of C (sc 1)) 
(make-instance g1 of G (sg 1))
(agenda)
(clear) ; Case 7l
(load* "attchtst3.clp")

(defrule fail-fail-fail-both "Case 7l"
   (x)
   (object (is-a A) (sa ?x))
   (exists (and (exists (and (object (is-a B) (sb ?x))
                             (object (is-a C) (sc ?x))))
                (test (= 1 1))))
   =>)

(defrule fail-fail-fail-fail "Case 7l"
   (x)
   (object (is-a E) (se ?x))
   (exists (and (exists (and (object (is-a F) (sf ?x))
                             (object (is-a G) (sg ?x))))
                (test (!= 2 2))))
   =>)
(assert (x))
(agenda)
(make-instance a1 of A (sa 1))
(make-instance e1 of E (se 1)) 
(make-instance a2 of A (sa 2))
(make-instance e2 of E (se 2))
(agenda)
(make-instance b1 of B (sb 1))
(make-instance f1 of F (sf 1))
(agenda)
(make-instance c1 of C (sc 1)) 
(make-instance g1 of G (sg 1))
(agenda)
(clear)