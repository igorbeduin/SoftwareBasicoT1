# SoftwareBasicoT1
Repositório para versionamento do Trabalho 1 da disciplina Software Básico da Universidade de Brasília.

Este repositorio (https://github.com/igorbeduin/SoftwareBasicoT1) possui dois programas: "montador" e "simulador". Os dois são compilados via `Makefile`, cada um com seu respectivo arquivo em seu diretório.

Aluno: Igor Raposo Oliveira Beduin

## Compilação

Existe um script .sh para compilação dos dois programas: `compile_all.sh`. Execute-o na pasta raiz deste repositório.

Se não quiser usar o script, cada um dos programas pode ser compilado individualmente dando o comando `make` em seus respectivos diretórios.

Compilador: g++.
Diretivas de compilação: `-std=c++11 -g -Wall -Wextra -Wno-unused-parameter`.

## Execução

O programa "montador" recebe como argumento um código .asm e escreve no diretório de execução o arquivo de saída .obj.

- Durante o processo de montagem é feita a verificação de erros. Caso algum erro seja detectado, o programa é parado e é escrito na tela o tipo de erro encontrado e em qual linha do codigo original ele ocorreu;
- Caso algum erro durante o processo de montagem for detectado, o arquivo de saída não é criado;
- O arquivo .obj de saída possui como primeiro valor a localização de memória onde a seção de dados termina;
  
O programa "simulador" recebe como argumento um código .obj. Caso o programa chame a diretiva OUTPUT, um arquivo de saída .out é criado com os valores de OUTPUT.

- Durante o processo de simulação é mostrado na tela os valores de ACC e PC;
- Se o programa do código .obj não chamar a diretiva OUTPUT, o arquivo .out não é criado;
- Existe mensagens de comunicação com o usuário no caso das diretivas OUTPUT e INPUT, a fim de se facilitar o entendimento da execução;
- o simulador possui uma memória fixa de 216 palavras;

Como a posição de encerramento da seção de dados é indicada no início do código .obj, o "montador" e "simulador" não são sensíveis à posição das seções, isto é, devem funcionar tanto se a seção de dados vier no início ou no fim. No entando, ainda as seções devem vir indicadas no código .asm.

### Exemplo de uso do montador:

```
make
make clean # para remoção dos arquivos .o intermediários
./montador fat.asm
# um arquivo fat.obj foi criado neste diretório
```

### Exemplo de uso do simulador:

```
make
make clean # para remoção dos arquivos .o intermediários
./simulador fat.obj # fat.obj criado na saída do montador
# como este código possui chamadas de OUTPUT, um arquivo texto de saída fat.out é criado neste diretóiro com os valores de OUTPUT
```
