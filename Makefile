.PHONY: all clean

NAME=lexer

CC=g++
BUILD=build
SRC=src

all: $(BUILD)
	@echo 'done'

$(BUILD): $(SRC)/*
	mkdir -p $(BUILD)
	$(CC) -o $(BUILD)/$(NAME) $(SRC)/*.cpp

clean:
	rm -rf $(BUILD)
