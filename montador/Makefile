# ----------------------------------------------------
# >>>>>>>>>> UNIX <<<<<<<<<<
# = Distribuições Linux
# = MacOS X com SDL instalado pelo "brew", sem XCode
# ----------------------------------------------------

# Compilador
COMPILER=g++

# Comando para remover pastas
RMDIR = rm -rdf

# Comando para remover arquivos
RM = rm -f

# Bibliotecas
LIBS = 

# Diretivas de compilacao
FLAGS = -std=c++11 -g -Wall -Wextra -Wno-unused-parameter

# Paths
INC_PATH = include
SRC_PATH = src
BIN_PATH = bin
OBJ_PATH = object

# Nome do executavel
EXECNAME = montador

# Listas de arquivos por extensão
BIN = $(BIN_PATH)/$(EXECNAME)
CPP_FILES = $(wildcard $(SRC_PATH)/*.cpp)
OBJ_FILES = $(patsubst $(SRC_PATH)/%.cpp, %.o, $(CPP_FILES))

# ----------------------------------------------------
# >>>>>>>>>> MacOS X <<<<<<<<<<
# = (usando os .frameworks) 
# ----------------------------------------------------
# 		ifeq ($(UNAME_S), Darwin)
# 		LIBS = 

# 		endif

# ===========================================================
# ===========================================================

# Linkagem a partir dos objetos (.o)
all: clean $(OBJ_FILES)
	$(COMPILER) $(OBJ_FILES) $(LIBS)  $(FLAGS) -o $(EXECNAME)

# Geração dos objetos a partir dos arquivos src (.cpp)
%.o: $(patsubst %.o, $(SRC_PATH)/%.cpp, $@)
	$(COMPILER) -c $(FLAGS) $(patsubst %.o, $(SRC_PATH)/%.cpp, $@) -o $@

clean:
	rm -f $(OBJ_FILES)