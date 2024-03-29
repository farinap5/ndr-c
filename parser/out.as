ADDR
    64 $add0
    65 $add1
END

DATA
    03 $add0
    05 $add1
END

TEXT
    LDA $add1
    ADD $add0
    HLT
END
