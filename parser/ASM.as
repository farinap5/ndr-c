ADDR
    64 $add0
    65 $add1
    66 $add2
    67 $add3
END

DATA
    01 $add0
    02 $add1
    03 $add2
    04 $add3
END

TEXT
   LDA $add3
   ADD $add2
   ADD $add1
   ADD $add0
         HLT
END
