```
Expression -> <Term> (+-) <Term> | <Term>
      Term -> <Factor> (*/) <Factor> | <Factor>
    Factor -> <Number> | ( <Expression> )
```

- Criar função para cada simbolo não terminal. 

- https://www.inf.ufpr.br/lesoliveira/download/c-completo-total.pdf
- http://docs.fct.unesp.br/docentes/dmec/olivete/compiladores/arquivos/Aula5.pdf
- http://docs.fct.unesp.br/docentes/dmec/olivete/compiladores/


```
11 + 5

db 11 $end1
db 5 $end2

LDA $end2
ADD $end1
STA $end3
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