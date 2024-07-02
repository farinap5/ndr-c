ADDR
    c0 $add0
    c1 $add1
    c2 $add2
END

DATA
    0 fa
    1 fb
    0 fc
    02 $add0
    03 $add1
    02 $add2
END

TEXT
    LDA $add0
    ADD $add1
    STA $add0

    LDA $add0
    ADD $add1
    STA $add0

    HLT
END
