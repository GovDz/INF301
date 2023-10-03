CC=clang
CFLAGS=-g -Wall -Wextra -Werror -gdwarf-4

EXEC=client-introduction client-tutoriel client-interactif Northwoods client-tutorielFORT projetX crypteSeq planB cryptMove BayOfPigs OneMillion LostCause

all: $(EXEC)

client-interactif: client-interactif.o client.o

client-tutoriel: client-tutoriel.o client.o

projetX : projetX.o client.o

planB: planB.o client.o

LostCause: LostCause.o client.o

crypteSeq : crypteSeq.o client.o

cryptMove: cryptMove.o client.o

client-tutorielFORT: client-tutorielFORT.o client.o

client-introduction: client-introduction.o client.o

client.o: client.c client.h

BayOfPigs: BayOfPigs.o client.o

Northwoods: Northwoods.o client.o

OneMillion : OneMillion.o client.o

crypto.o: crypto.c crypto.h

clean:
	rm -f *.o

clear:
	rm -f $(EXEC)
