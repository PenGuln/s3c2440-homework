
include $(TOPDIR)Rules.mak

EXTRA_LIBS += -lsqlite3
EXTRA_LIBS += -lpthread

EXEC =  $(INSTALL_DIR)/SQLite_test
#OBJS =  main-bak1.o 
OBJS =  SQLite.o tty.o dcm.o keyboard.o get_key.o main.o

all: $(EXEC)


$(EXEC): $(OBJS)
	$(CC) $(LDFLAGS) -I ./sqlite/ -L ./sqlite/ -o $@ $(OBJS)  $(EXTRA_LIBS)

install:
	$(EXP_INSTALL) $(EXEC) $(INSTALL_DIR)

clean:
	-rm -f $(EXEC) *.elf *.elf2flt *.gdb *.o
