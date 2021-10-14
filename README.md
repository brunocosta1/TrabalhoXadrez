# Trabalho Xadrez

Projeto de um jogo de xadrez que foi avaliado no 2º semestre da faculdade na disciplina Programação de Computadores II.

# Começando

Para execução do projeto, será necessário os seguintes programas:

- make: Necessário para rodar o makefile
- gcc: Necessário para compilar o programa
- git: Necessário para clonar o repositório

Para instalar os programas no Ubuntu/Debian, rode os comandos no terminal:

```
sudo apt install make gcc git
```

Ou

```
sudo apt install build-essential git
```

# Instalação

Clone o repositório em seu computador:

```
git clone https://github.com/brunocosta1/TrabalhoXadrez
```
Rode os seguintes comandos:

```
cd TrabalhoXadrez
make
```
Agora para rodar o programa, basta digitar em seu terminal:

```
./main
```

# Peças

0 -> Não há peça
1 -> Peão
2 -> Cavalo
3 -> Bispo
4 -> Torre
5 -> Dama
6 -> Rei

Os valores positivos são para peças brancas, negativos para peças pretas.

# Configurações

Se o seu computador permitir um processamento grande, você pode ir no arquivo elements.h e alterar o nível de profundidade da IA na constante MAX_NIVEL 

