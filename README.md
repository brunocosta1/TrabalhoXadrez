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

0 -> Não há peça < br />
1 -> Peão < br />
2 -> Cavalo < br />
3 -> Bispo < br />
4 -> Torre < br />
5 -> Dama < br />
6 -> Rei < br />

Os valores positivos são para peças brancas, negativos para peças pretas. < br />

# Configurações

Se o seu computador permitir um processamento grande, você pode ir no arquivo elements.h e alterar o nível de profundidade da IA na constante MAX_NIVEL 

