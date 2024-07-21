## Colaboradores
- Raphael de Jesus Gramosa (@Gramosa)
- Ravena Dafne Costa Carneiro (@RavenaDafne)
- Uitan Maciel(UitanMaciel)


## QUESTÃO 01

| L0Q1.in                                                       | L0Q1.out                                                                       |
|---------------------------------------------------------------|-------------------------------------------------------------------------------|
| p o i n t s ( −2 , −1) ( 4 , 2 ) ( 4 , 0 ) ( 2 , 2 ) ( 8 , 6 ) | p o i n t s ( −2 , −1) ( 2 , 2 ) ( 4 , 0 ) ( 4 , 2 ) ( 8 , 6 ) d i s t a n c e 1 8 . 7 5 s h o r t c u t 1 2 . 2 1  |


### Entrada

A cada linha um points marca o inı́cio de uma lista de pontos no espaço bidimensional; veja a figura
abaixo.


### Saı́da

Na saı́da é preciso ordenar todos os pontos points conforme suas distâncias Euclidianas em relação
origem, ou seja, em relação ao ponto (0,0).
Em seguida deve-se exibir a distância total Euclidiana distance considerando os pontos na mesma
ordem em que aparecem na entrada.
Por fim, deve-se exibir a distância total Euclidiana shortcut entre o primeiro e último ponto na
mesma ordem em que aparecem na entrada.

**Observações**

• Cada ponto aparece separado por apenas um espaço em branco dos demais e entre (), números
com parte decimal são representados usando o ponto final e não a vı́rgula.
• Sua resposta deve estar em um único arquivo chamado RL0Q1.[java, py, js, c, cpp, etc]
• Você deve ler o arquivo L0Q1.in e escrever o arquivo L0Q1.out no mesmo diretório onde estiver
rodando seu código RL0Q1.[java, py, js, c, cpp, etc]jose.dihego@ifba.edu.br
• Não deve ser usado nenhum recurso de ordenação da linguagem de programação de sua escolha
• Pode e vai haver mais de uma linha na estrada
• O número de linhas na entrada deve ser o mesmo da saı́da, ou seja cada linha da entrada
produzirá uma linha na saı́da
• Os pontos podem ter coordenadas reais, ou seja o ponto (13.34,10.2) é um ponto válido para a
entrada
• Não existem dois espaços em branco seguidos

## Compilação

Para compilar o projeto, siga os passos abaixo:

1. Navegue até o diretório do projeto:

    ```bash
    cd atividade1/
    ```

2. Execute o comando de compilação:

    ```bash
    gcc RL0Q1.c -lm -o atividade1 && ./atividade1
    ```

## QUESTÃO 02


| L0Q2.in                     | L0Q2.out                                                                   |
|-----------------------------|----------------------------------------------------------------------------|
| maria 3 . 1 5 j o s e 4 8 −1 1 2 . 7 ( −1 , −1) j u l i a ( −0.5 , −0.5)        | s t r : j o s e j u l i a m a r i a i n t : − 1 4 8 f l o a t : 3 . 1 5 1 2 . 7 p : ( − 0 . 5 , − 0 . 5 ) ( − 1 , − 1 )   |
| 7 4 . 5 3 . 1 5 j o s e 4 8 −1 1 2 . 7 ( 8 , 2 ) c a r l o s ( −0.5 , −0.5)      | s t r : c a r l o s j o s e i n t : − 1 4 8 f l o a t : 3 . 1 5 1 2 . 7 7 4 . 5 p : ( − 0 . 5 , − 0 . 5 ) ( 8 , 2 )                 |



Esta questão consiste em ler uma lista de valores contendo strings, inteiros, reais e pontos no espaço
bidimensional. A saı́da consiste em ordenar de maneira crescente, as strings por ordem alfabética,
os inteiros, os reais e por fim os pontos por ordem crescente em relação a suas distância Euclidianas
em relação a origem, o ponto (0,0).

**Observações**

• Não faça Ctrl+C/Ctrl+V deste arquivo PDF no seu arquivo de entrada pois podem ocorrer
erros.
• Cada ponto aparece entre (), números com parte decimal são representados usando o ponto
final e não a vı́rgula.
• Sua resposta deve estar em um único arquivo chamado RL0Q2.[java, py, js, c, cpp, etc]
• Você deve ler o arquivo L0Q2.in e escrever o arquivo L0Q2.out no mesmo diretório onde estiver
rodando seu código RL0Q2.[java, py, js, c, cpp, etc]
• Não deve ser usado nenhum recurso de ordenação da linguagem de programação de sua escolha
• Pode e vai haver mais de uma linha na estrada
• O número de linhas na entrada deve ser o mesmo da saı́da, ou seja cada linha da entrada
produzirá uma linha na saı́da
• Os pontos podem ter coordenadas reais, ou seja o ponto (13.34,10.2) é um ponto válido para a
entrada
• não existem dois espaços em branco seguidos

## Compilação

Para compilar o projeto, siga os passos abaixo:

1. Navegue até o diretório do projeto:

    ```bash
    cd atividade1/
    ```

2. Execute o comando de compilação:

  ```bash
  gcc RL0Q2.c -lm -o atividade2 && ./atividade2
  ```