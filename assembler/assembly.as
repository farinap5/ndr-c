; Commend

ADDR ; start addressing section
    8 $end1
    89 $end1
END


DATA ; start data section
    a $end1
    02 8
END 


LDA $end1; aaaaa
STA 50;