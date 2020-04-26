COMPILATEUR = gcc -o
PRINCIPALE	= main.c
FONCTIONS 	= fonctions.c
EXECUTABLE	= main.x

executer:  compiler
	@echo "\nExecution"
	./$(EXECUTABLE)

compiler: $(PRINCIPALE) $(FONCTIONS) fonctions.h
	@echo "Compilation"
	$(COMPILATEUR) $(EXECUTABLE) $(PRINCIPALE) $(FONCTIONS)