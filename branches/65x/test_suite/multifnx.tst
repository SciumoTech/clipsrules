(unwatch all)
(clear)
(set-strategy depth)
(open "Results//multifnx.rsl" multifnx "w")
(dribble-on "Actual//multifnx.out")
(batch "multifnx.bat")
(dribble-off)
(load "compline.clp")
(printout multifnx "multifnx.bat differences are as follows:" crlf)
(compare-files "Expected//multifnx.out" "Actual//multifnx.out" multifnx)
; close result file
(close multifnx)