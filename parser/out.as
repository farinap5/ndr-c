ADDR
    c0 $add0
    c1 $add1
END

DATA
    0 fa
    1 fb
    0 fc
    02 $add0
    02 $add1
END

TEXT
    LDA $add0
    ADD $add1
    STA $add0

    HLT
END
