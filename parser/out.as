ADDR
    64 $add0
    65 $add1
    66 $add2
    67 $add3
END

DATA
    01 $add0
    05 $add1
    03 $add2
    01 $add3
END

TEXT
    LDA $add2
    ADD $add3
    STA $add2
    LDA $add1
    NOT
    ADD $add2
    NOT
    STA $add1
    LDA $add0
    ADD $add1
    STA $add0
    HLT
END
