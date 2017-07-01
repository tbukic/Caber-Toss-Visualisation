TARGET	= simulation

SRC_DIR		= ./src
OBJ_DIR		= ./obj
BIN_DIR		= ./bin
INCL_DIR	= ./includes
LIB		= ../caber/includes
EXTERNAL	= -lsfml-graphics -lsfml-window -lsfml-system

CC	= g++
LINKER	= $(CC) -o
DEBUG	= -g
VERSION	= -std=c++11
INCLUDE = -I $(INCL_DIR) -I $(LIB)
CFLAGS	= -Wall -c $(DEBUG) $(VERSION) $(INCLUDE) -o $@
LFLAGS	= -Wall $(DEBUG) $(VERSION) $(INCLUDE) -o $@



OBJECTS	:= $(OBJ_DIR)/main.o $(OBJ_DIR)/simulation.o $(OBJ_DIR)/configure.o
rm	= \rm 

# links program:

$(BIN_DIR)/$(TARGET) : $(OBJECTS)
	$(LINKER) $(LFLAGS) $(OBJECTS) $(EXTERNAL)
	@echo "Linking complete!"


# compiling everything:

all : $(TARGET)

$(TARGET) : $(OBJECTS)
	@echo "Compiling complete!"

# compiles object files:

$(OBJ_DIR)/main.o : $(SRC_DIR)/main.cpp $(INCL_DIR)/simulation.h $(INCL_DIR)/configure.h
	$(CC) $(CFLAGS) $(SRC_DIR)/main.cpp $(EXTERNAL)

$(OBJ_DIR)/simulation.o : $(INCL_DIR)/simulation.h $(SRC_DIR)/simulation.cpp \
	$(INCL_DIR)/configure.h
	$(CC) $(CFLAGS) $(SRC_DIR)/simulation.cpp

$(OBJ_DIR)/configure.o :  $(INCL_DIR)/configure.h $(SRC_DIR)/configure.cpp
	$(CC) $(CFLAGS) $(SRC_DIR)/configure.cpp

# Headers:

#$(OBJ_DIR)/simulation.h : $(INCL_DIR)/caber/EulerTossModel.h $(INCL_DIR)/caber/Caber.h


.PHONY: clean
clean:
	@$(rm) $(OBJECTS)
	@echo "Cleanup complete!"

.PHONY: remove
remove: clean
	@$(rm) $(BIN_DIR)/$(TARGET)
	@echo "Executable removed!"
