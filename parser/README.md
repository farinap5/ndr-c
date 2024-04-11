```
Expression -> <Term> (+-) <Term> | <Term>
      Term -> <Factor> (*/) <Factor> | <Factor>
    Factor -> <Number> | ( <Expression> )
```

- Criar função para cada simbolo não terminal. 

- https://www.inf.ufpr.br/lesoliveira/download/c-completo-total.pdf
- http://docs.fct.unesp.br/docentes/dmec/olivete/compiladores/arquivos/Aula5.pdf
- http://docs.fct.unesp.br/docentes/dmec/olivete/compiladores/

Atialmente a multiplicação apenas funciona caso a multiplicação esteja ao fina:

```
1 + 4 + 2 * 2
```

```
11 + 5

db 11 $end1
db 5 $end2

LDA $end2
ADD $end1
STA $end2
HLT
```

```
11 + 5 * 10

db 11 $end1
db 5  $end2
db 10 $end3

LDA $end3
MUL $end2
ADD $end1
STA $end4
HLT
```

```
11 + 5 * 10 - 5

db 11 $end1
db 5  $end2
db 10 $end3
db 5  $end4

LDA $end3
MUL $end2
SUB $end4
ADD $end1
STA $end5
HLT
```


---

```
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
    HLT
END
```

```
ADDR
    c0 $add0
    c1 $add1
END

DATA
    02 $add0
    03 $add1
END

TEXT
    :p1
    LDA $add0
    ADD $add0
    STA $add0

    LDA x=0
    ADD y=1

    NOT
    ADD $add1
    JN :p1
    STA $add0
    HLT
END
```