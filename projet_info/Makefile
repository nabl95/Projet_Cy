# Variables de compilation
CC = gcc
CFLAGS = -Wall -g
TARGET = refuge
OBJS = main.o refuge.o util.o

# Cible par défaut
all: $(TARGET)

# Création de l'exécutable
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)

# Compilation des fichiers objets
main.o: main.c refuge.h util.h
	$(CC) $(CFLAGS) -c main.c -o main.o

refuge.o: refuge.c refuge.h util.h
	$(CC) $(CFLAGS) -c refuge.c -o refuge.o

util.o: util.c util.h refuge.h
	$(CC) $(CFLAGS) -c util.c -o util.o

# Nettoyage des fichiers objets et de l'exécutable
clean:
	rm -f *.o $(TARGET)
