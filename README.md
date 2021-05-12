# Software Basico Trabalhos
Repositório para versionamento do Trabalho 1 e 2 da disciplina Software Básico da Universidade de Brasília.

Este repositorio (https://github.com/igorbeduin/SoftwareBasicoTrabalhos) possui três programas: "montador", "ligador" e "simulador". Os três são compilados via `Makefile`, cada um com seu respectivo arquivo em seu diretório.

Todos os testes e compilações foram feitas em ambiente Linux (Ubuntu 20LTS).

Aluno: Igor Raposo Oliveira Beduin

## Compilação

Existe um script .sh para compilação dos três programas: `compile_all.sh`. Execute-o na pasta raiz deste repositório.

Se não quiser usar o script, cada um dos programas pode ser compilado individualmente dando o comando `make` em seus respectivos diretórios.

Compilador: g++.
Diretivas de compilação: `-std=c++11 -g -Wall -Wextra -Wno-unused-parameter`.

## Execução

O programa "montador" recebe como argumento um a três código .asm e escreve no diretório de execução o arquivo de saída para ser ligado .obj.

- Durante o processo de montagem é feita a verificação de erros. Caso algum erro seja detectado, o programa é parado e é escrito na tela o tipo de erro encontrado e em qual linha do codigo original ele ocorreu;
- O "montador" pode receber de 1 a 3 programas para ser montado;
  - No caso de apenas 1 programa dado como argumento, espera-se que ele não possua BEGIN e/ou END. Se possuir, um erro é detectado;
  - No caso de 2 a 3 programas serem dados como argumento, espera-se que cada um deles possuam BEGIN e END. Se não possuir, um erro é detectado.
- Caso algum erro durante o processo de montagem for detectado, o arquivo de saída não é criado;
- O arquivo .obj de saída possui todas as informações de cabeçalho e tabelas para ser ligado pelo "ligador";
  
O programa "ligador" recebe como argumento um a três códigos .obj de mesmo nome do módulo montado e escreve no diretório de execução o arquivo de saída *progs_linked.obj*.

- O arquivo *progs_linked.obj* serve como entrada para o "simulador"
- Este ligador espera que as diretivas PUBLIC e EXTERN sejam chamadas ANTES da SECTION DATA
- Este programa é gerado para funcionar com o simulador disponibilizado, isto é, que o primeiro valor é op code;
  
O programa "simulador" recebe como argumento um código *progs_linked.obj* ligado. Caso o programa chame a diretiva OUTPUT, um arquivo de saída .out é criado com os valores de OUTPUT.

- Durante o processo de simulação é mostrado na tela os valores de ACC e PC;
- Se o programa do código .obj não chamar a diretiva OUTPUT, o arquivo .out não é criado;
- Existem mensagens de comunicação com o usuário no caso das diretivas OUTPUT e INPUT, a fim de se facilitar o entendimento da execução;
- o simulador possui uma memória fixa de 216 palavras;
- Este simulador foi modificado para funcionar da mesma forma que o disponibilizado pelo professor. Caso este não funcione, recomenda-se testar com o do professor.

### Exemplo de uso do montador:

```
make
make clean # para remoção dos arquivos .o intermediários
./montador mod_A.asm mod_B.asm
# um arquivo mod_A.obj e um arquivo mod_B.obj foram criados neste diretório
```

### Exemplo de uso do ligador:

```
make
make clean # para remoção dos arquivos .o intermediários
./ligador mod_A.obj mod_B.obj # mod_A.obj e mod_B.obj foram criados na saída do montador
# um arquivo progs_linked.obj foi criado neste diretório
```

### Exemplo de uso do simulador:

```
make
make clean # para remoção dos arquivos .o intermediários
./simulador progs_linked.obj # progs_linked.obj criado na saída do ligador
# caso o código possua chamadas de OUTPUT, um arquivo texto de saída .out é criado neste diretório com os valores de OUTPUT
```
