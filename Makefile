CC = g++
CFLAGS = -Wall -O2
SRC = src/main.cpp
OUT = tpp
BIN_DIR = /usr/local/bin

all: $(OUT)

$(OUT): $(SRC)
	$(CC) $(CFLAGS) -o $(OUT) $(SRC)

install: $(OUT)
	@echo "Installing tpp binary on $(BIN_DIR)..."
	sudo cp $(OUT) $(BIN_DIR)
	sudo chmod +x $(BIN_DIR)/$(OUT)
	@echo "tpp installed sucessfully!"

uninstall:
	@echo "Uninstalling tpp binary on $(BIN_DIR)..."
	sudo rm -f $(BIN_DIR)/$(OUT)
	@echo "tpp uninstalled sucessfully!"

clean:
	rm -f $(OUT)

.PHONY: all install uninstall clean
