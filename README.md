# Descrição
Jogo da velha composto por dois módulos: um aprendiz e um jogador.
O aprendiz guarda em um arquivo as jogadas que o levam à derrota. 
O jogador lê esse arquivo e usa para tentar evitar a derrota.

O jogador permite apenas uma iteração. Para cada entrada, uma saída. Não existe continuidade no jogo.

Com o aprendiz é possível jogar uma partida inteira.

O formato de entrada e saída é o seguinte: 

```X________```

Onde os tres primeiros '_' representam a primeira linha do tabuleiro, os tres posteriores representam a segunda e a mesma lógica aplica-se aos tres ultimos.

O primeiro a jogar decide com qual tipo de peça vai jogar. 

A cada iteração é necessário 'redesenhar' o último estado do tabuleiro.