FLAGS = -Wall -lraylib -lGL -lm -lpthread -ldl -lrt -lX11 -o
PROJECT = Scratchpad

.PHONY: all
all:
	gcc $(PROJECT).c $(FLAGS) $(PROJECT).out

.PHONY: debug
debug:
	gcc $(PROJECT).c $(FLAGS) $(PROJECT).out -g

.PHONY: clean
clean:
	rm -f $(PROJECT).out
