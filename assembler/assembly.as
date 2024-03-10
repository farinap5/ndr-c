; Comment

ADDR ; start addressing section
    50 $end1
    89 $end2
END

DATA ; start data section
    a $end1
    b $end2
    02 8
END 

TEXT
    STA 09
    :aaaa
    STA $end1
    STA 09
    STA 09
    STA 09
    STA 09
    STA 09
    STA 09
    JMP :aaaa
END