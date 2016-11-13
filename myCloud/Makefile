CC:=gcc 
LINK:= -lpthread -lsqlite3
DEBUG:=
CFLAGS:= -g -I./include/ $(DEBUG)
REPODIR:=./repo/
SRCDIR:=./src/
SER_SRC:=$(SRCDIR)main_server.c $(SRCDIR)parser.c $(SRCDIR)thread_pool.c $(SRCDIR)semi_generic_lqueue.c $(SRCDIR)debug.c
CLI_SRC:=$(SRCDIR)main_client.c 

TARDIR:=./elf/
SERVER:=$(TARDIR)server
CLIENT:=$(TARDIR)client

all:
	$(CC) $(CFLAGS) $(SER_SRC) $(LINK) -o $(SERVER)
	$(CC) $(CFLAGS) $(CLI_SRC) -o $(CLIENT)

.PHONY:clean cleanall
clean:
	$(RM) $(SERVER) $(CLIENT)
cleanall:
	$(RM) $(SERVER) $(CLIENT) $(REPODIR)*
	mv $(SRCDIR)*.db $(REPODIR)
	
