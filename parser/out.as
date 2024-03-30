ADDR
    c0 $add0
    c1 $add1
    c2 $add2
END

DATA
    0 fa
    1 fb
    0 fc
    04 $add0
    03 $add1
    01 $add2
END

TEXT
    :p1
    LDA fc
    ADD $add1
    STA fc
    LDA fa
    ADD fb
    STA fa
    NOT
    ADD $add2
    JZ :p2
    JMP :p1
    :p2
    STA fa
    LDA fc
    STA $add1
    LDA fd
    STA fa
    STA fc
    LDA $add1
    LDA $add1
    ADD $add2
    STA $add1
    LDA $add0
    ADD $add1
    STA $add0
    HLT
END
