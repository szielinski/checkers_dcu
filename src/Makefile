#
# This is an example Makefile for a countwords program.  This
# program uses both the scanner module and a counter module.
# Typing 'make' or 'make count' will create the executable file.
#

# define some Makefile variables for the compiler and compiler flags
# to use Makefile variables later in the Makefile: $()
#
#  -g    adds debugging information to the executable file
#  -Wall turns on most, but not all, compiler warnings
#
CXX = g++
CXXFLAGS  = -g -Wall

# typing 'make' will invoke the first target entry in the file 
# (in this case the default target entry)
#
default: all

# Make all the tests, and the client and server
all:  testBoard testCheckers testPiece testttt client server

# Test files
testBoard:	testBoard.o testBoard.o board.o piece.o
	$(CXX) $(CXXFLAGS) -o testBoard $^

testCheckers:	testCheckers.o checkersgame.o piece.o board.o
	$(CXX) $(CXXFLAGS) -o testCheckers $^
	
testPiece: testPiece.o piece.o
	$(CXX) $(CXXFLAGS) -o testPiece $^
	
testttt:	testttt.o tttgame.o piece.o board.o
	$(CXX) $(CXXFLAGS) -o testttt $^

#Client and Server
client:	client.o
	$(CXX) $(CXXFLAGS) -o client $^

server:	server.o checkersgame.o tttgame.o piece.o board.o
	$(CXX) $(CXXFLAGS) -o server $^

# To start over from scratch, type 'make clean'.  This
# removes the executable file, as well as old .o object
# files and *~ backup files:
#
clean:
	rm -f testBoard testCheckers testPiece testttt client server *.o
