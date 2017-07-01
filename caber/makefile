TARGET	= caber

SRC_DIR		= ./src
OBJ_DIR		= ./obj
INCL_DIR	= ./includes

CC	= g++
LINKER	= $(CC) -o
DEBUG	= -g
VERSION	= -std=c++11
INCLUDE = -I $(INCL_DIR)
CFLAGS	= -Wall -c $(DEBUG) $(VERSION) $(INCLUDE) -o $@
LFLAGS	= -Wall $(DEBUG) $(VERSION) $(INCLUDE) -o $@

OBJECTS := $(OBJ_DIR)/caber.o $(OBJ_DIR)/CaberMotion.o $(OBJ_DIR)/EulerTossModel.o \
	$(OBJ_DIR)/FlyingModel.o $(OBJ_DIR)/LandingModel.o $(OBJ_DIR)/MotionModel.o \
	$(OBJ_DIR)/RunningModel.o $(OBJ_DIR)/ThrowModel.o

rm	= \rm 
INCLUDES = $(wildcard $(INCL_DIR)/*.h)


# compiling everything:

all : $(TARGET)

$(TARGET) : $(OBJECTS)
	@echo "Compiling complete!"

# Caber files:

$(OBJ_DIR)/caber.o : $(INCL_DIR)/Caber.h
	$(CC) $(CFLAGS) $(SRC_DIR)/Caber.cpp

$(OBJ_DIR)/CaberMotion.o : $(INCL_DIR)/CaberMotion.h
	$(CC) $(CFLAGS) $(SRC_DIR)/CaberMotion.cpp

$(OBJ_DIR)/EulerTossModel.o : $(INCL_DIR)/EulerTossModel.h
	$(CC) $(CFLAGS) $(SRC_DIR)/EulerTossModel.cpp

$(OBJ_DIR)/FlyingModel.o : $(INCL_DIR)/FlyingModel.h
	$(CC) $(CFLAGS) $(SRC_DIR)/FlyingModel.cpp

$(OBJ_DIR)/LandingModel.o : $(INCL_DIR)/LandingModel.h
	$(CC) $(CFLAGS) $(SRC_DIR)/LandingModel.cpp

$(OBJ_DIR)/MotionModel.o : $(INCL_DIR)/MotionModel.h
	$(CC) $(CFLAGS) $(SRC_DIR)/MotionModel.cpp

$(OBJ_DIR)/RunningModel.o : $(INCL_DIR)/RunningModel.h
	$(CC) $(CFLAGS) $(SRC_DIR)/RunningModel.cpp
	
$(OBJ_DIR)/ThrowModel.o : $(INCL_DIR)/ThrowModel.h
	$(CC) $(CFLAGS) $(SRC_DIR)/ThrowModel.cpp

# Caber headers:

$(INCL_DIR)/EulerTossModel.h : $(INCL_DIR)/CaberMotion.h $(INCL_DIR)/RunningModel.h \
	$(INCL_DIR)/ThrowModel.h $(INCL_DIR)/FlyingModel.h $(INCL_DIR)/LandingModel.h

$(INCL_DIR)/FlyingModel.h : $(INCL_DIR)/MotionModel.h

$(INCL_DIR)/LandingModel.h : $(INCL_DIR)/MotionModel.h

$(INCL_DIR)/MotionModel.h : $(INCL_DIR)/Caber.h $(INCL_DIR)/CaberMotion.h
 
$(INCL_DIR)/RunningModel.h : $(INCL_DIR)/MotionModel.h $(INCL_DIR)/Caber.h

$(INCL_DIR)/ThrowModel.h : $(INCL_DIR)/MotionModel.h


.PHONY: clean
clean:
	@$(rm) $(OBJECTS)
	@echo "Cleanup complete!"

.PHONY: remove
remove: clean
