THRIFT_DIR	= 	/usr/lib/thrift/lib/cpp/test
BOOST_DIR	= 	/usr/include/boost
THRIFT_LIBS	= 	/usr/local/lib
BOOST_LIBS 	= 	/usr/lib/x86_64-linux-gnu	
GEN_INC 	= 	-I./gen-cpp
INCS_DIRS 	=	-I${BOOST_DIR} -I${THRIFT_DIR}
LIBS_DIRS   =	-L${BOOST_LIBS} -L${THRIFT_LIBS}
LIBS 		=	-lthrift

# SOURCES 	= 	src/multiply.cpp

PCH_NAME 	=	stdafx.h
STDAFX 		= 	${PCH_NAME}.gch

# OBJECTS 	= 	${SOURCES:%.cpp=%.o}

CC			=	g++
CFLAGS		= 	-Wall

default: server client

server: ${STDAFX} server.cpp
	${CC} ${CFLAGS} -o server ${GEN_INC} ${INCS_DIRS} server.cpp ${LIBS_DIRS} ${LIBS}

# src/%.o: src/%.cpp
# 	${CC} $< ${CFLAGS} -o $@

client: ${STDAFX} client.cpp
	${CC} ${CFLAGS} -o client ${GEN_INC} ${INCS_DIRS} client.cpp ${LIBS_DIRS} ${LIBS}

${STDAFX}:
	${CC} ${CFLAGS} -x c++-header ${PCH_NAME}

clean:
	rm -r server client ${STDAFX}