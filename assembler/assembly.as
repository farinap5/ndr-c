; Comment

ADDR ; start addressing section
    8 $end1
    89 $end2
END

DATA ; start data section
    a $end1
    b $end2
    02 8
END 

TEXT
    LDA $end1; aaaaa
    STA $end1;
    
    :batata
END