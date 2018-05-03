# Makefile
#
# Any files which are required for compilation must have their .o name put in the OBJECTS list
# eg. cell.h and cell.cc will require cell.o being added
#
# Nothing else need be modified
#
# % make [ cc3k ]

########## Variables ##########

CXX = g++-4.9									# compiler
CXXFLAGS = -g -Wall -Werror -std=c++11 -MMD		# compiler flags
MAKEFILE_NAME = ${firstword ${MAKEFILE_LIST}}	# makefile name

OBJECTS = cc3k.o game.o	cell.o gameobject.o character.o player.o orc.o treasure.o gridbug.o potion.o goblin.o dragon.o merchant.o# object files forming executable
DEPENDS = ${OBJECTS:.o=.d}			# substitute ".o" with ".d"
EXEC = cc3k							# executable name

########## Targets ##########

.PHONY : clean					# not file names

${EXEC} : ${OBJECTS}				# link step
	${CXX} ${CXXFLAGS} $^ -o $@		# additional object files before $^

${OBJECTS} : ${MAKEFILE_NAME}		# OPTIONAL : changes to this file => recompile

# make implicitly generates rules to compile C++ files that generate .o files

-include ${DEPENDS}					# include *.d files containing program dependences

clean :						# remove files that can be regenerated
	rm -f ${DEPENDS} ${OBJECTS} ${EXEC}
