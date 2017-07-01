TARGET	= project

SIM_DIR		= ./simulation
CABER_DIR	= ./caber
SIM_OBJ_DIR	= $(SIM_DIR)/obj
CABER_OBJ_DIR	= $(CABER_DIR)/obj
BIN_DIR		= ./
INCL_DIR	= ./includes
LIB		= ../caber/includes
EXTERNAL	= -lsfml-graphics -lsfml-window -lsfml-system

CC	= g++
LINKER	= $(CC) -o
DEBUG	= -g
VERSION	= -std=c++11
INCLUDE = -I $(INCL_DIR) -I $(LIB)
LFLAGS	= -Wall $(DEBUG) $(VERSION) $(INCLUDE) -o $@

SIM_OBJECTS := $(SIM_OBJ_DIR)/main.o $(SIM_OBJ_DIR)/simulation.o $(SIM_OBJ_DIR)/configure.o

CABER_OBJECTS := $(CABER_OBJ_DIR)/caber.o $(CABER_OBJ_DIR)/CaberMotion.o \
	$(CABER_OBJ_DIR)/EulerTossModel.o $(CABER_OBJ_DIR)/FlyingModel.o \
	$(CABER_OBJ_DIR)/LandingModel.o $(CABER_OBJ_DIR)/MotionModel.o \
	$(CABER_OBJ_DIR)/RunningModel.o $(CABER_OBJ_DIR)/ThrowModel.o

OBJECTS = $(SIM_OBJECTS) $(CABER_OBJECTS)

rm	= \rm 

# links program:

$(BIN_DIR)/$(TARGET) : all
	$(LINKER) $(LFLAGS) $(OBJECTS) $(EXTERNAL)
	@echo "Linking complete!"


# compiling everything:

all :
	(cd $(CABER_DIR) && make all)
	(cd $(SIM_DIR) && make all)
	@echo "Compiling complete!"




.PHONY: clean
clean:
	@$(rm) $(OBJECTS)
	@echo "Cleanup complete!"

.PHONY: remove
remove: clean
	@$(rm) $(BIN_DIR)/$(TARGET)
	@echo "Executable removed!"
