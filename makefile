CMD = cc -Wall -Wextra
BIN = ./bin
SRC = ./src
INC = ./include

all: rchat_server rchat_client
rchat_server: $(BIN)/rchat_server.o 
	$(CMD) $(BIN)/rchat_server.o -o rchat_server
rchat_client: $(BIN)/rchat_clinet.o
	$(CMD) $(BIN)/rchat_client.o -o rchat_client
$(BIN)/rchat_server.o: $(SRC)/rchat_server.c
	$(CMD) -c $(SRC)/rchat_server.c -o $(BIN)/rchat_server.o
$(BIN)/rchat_client.o: $(SRC)/rchat_client.c
	$(CMD) -c $(SRC)/rchat_client.c -o $(BIN)/rchat_client.o
clean:
	rm -rf rchat_server rchat_client $(BIN)/*.o
debug: CMD += g
debug: clean all
