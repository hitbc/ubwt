CC      =	gcc
CFLAGS  =	-Wall -O3 -Wno-unused-variable -Wno-unused-but-set-variable -Wno-unused-function
DFLAGS  =	-g -Wall
LIB     =	-lm -lz -lpthread

BIN_DIR =	.
SRC_DIR =   .

SOURCE  =	$(wildcard ${SRC_DIR}/*.c) 
OBJS    =	$(SOURCE:.c=.o)

BIN     =	$(BIN_DIR)/ubwt

GDB_DEBUG   =   $(BIN_DIR)/gdb_ubwt
NOR_DEBUG   =   $(BIN_DIR)/debug_ubwt
DMARCRO =	-D __DEBUG__

.c.o:
	$(CC) -c $(CFLAGS) $< -o $@

all:       $(SOURCE) $(BIN) 
gdb_ubwt:  $(SOURCE) $(GDB_DEBUG) 
debug_ubwt:$(SOURCE) $(NOR_DEBUG)


$(BIN): $(OBJS)
	$(CC) $(OBJS) -o $@ $(LIB)

$(GDB_DEBUG):
	$(CC) $(DFLAGS) $(SOURCE) $(DMARCRO) -o $@ $(LIB)
$(NOR_DEBUG):
	$(CC) $(CFLAGS) $(SOURCE) $(DMARCRO) -o $@ $(LIB)

clean:
	rm -f $(SRC_DIR)/*.o $(BIN)

clean_debug:
	rm -f $(SRC_DIR)/*.o $(GDB_DEBUG) $(NOR_DEBUG)
