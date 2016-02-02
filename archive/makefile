CC=g++

CFLAGSLINK=-Wall -lstdc++ -lc -lm -lGL -lGLU -lglut  
CFLAGS=$(CFLAGSLINK) -c

all: conway

conway: ca4dbase.o conway4D.o main.o spaceNd.o
	$(CC)  ca4dbase.o conway4D.o main.o spaceNd.o -o conway $(CFLAGSLINK)

conway4D.o: conway4D.cpp shared.h color.h vector.h cursor.h spaceNd.h ca4dbase.h conway4D.h
	$(CC) $(CFLAGS) conway4D.cpp

#unittests.o: unittests.cpp shared.h color.h vector.h cursor.h spaceNd.h ca4dbase.h conway4D.h unittests.h conway4Dscanner.h
#	$(CC) $(CFLAGS) unittests.cpp
	
spaceNd.o: spaceNd.cpp shared.h color.h vector.h cursor.h spaceNd.h ca4dbase.h conway4D.h
	$(CC) $(CFLAGS) spaceNd.cpp
	
main.o: main.cpp shared.h color.h vector.h cursor.h spaceNd.h ca4dbase.h conway4D.h
	$(CC) $(CFLAGS) main.cpp

ca4dbase.o: ca4dbase.cpp shared.h color.h vector.h cursor.h spaceNd.h ca4dbase.h conway4D.h
	$(CC) $(CFLAGS) ca4dbase.cpp

#conway4Dscanner.o: conway4Dscanner.cpp shared.h color.h vector.h cursor.h spaceNd.h ca4dbase.h conway4D.h unittests.h conway4Dscanner.h
#	$(CC) $(CFLAGS) conway4Dscanner.cpp

clean:
	rm -rf *.o *.h.gch conway
