THRIFT_DIR	= 	/usr/lib/thrift/lib/cpp/test
BOOST_DIR	= 	/usr/include/boost
LOG4CXX_DIR	= 	/usr/lib/apache-log4cxx-0.10.0/src/main/include
#Thrift and log4cxx libs in /usr/local/lib
THRIFT_LIBS	= 	/usr/local/lib
BOOST_LIBS 	= 	/usr/lib/x86_64-linux-gnu	
GEN_INC 	= 	-I./gen-cpp
INCS_DIRS 	=	-I${BOOST_DIR} -I${THRIFT_DIR} -I${LOG4CXX_DIR}
LIBS_DIRS   =	-L${BOOST_LIBS} -L${THRIFT_LIBS}
LIBS 		=	-lthrift -lthriftnb -levent -lboost_system -llog4cxx -lssl -lcrypto

# SOURCES 	= 	src/multiply.cpp

PCH_NAME 	=	stdafx.h
STDAFX 		= 	${PCH_NAME}.gch

SRC		= 	gen-cpp/SSLChatService.cpp  \
			gen-cpp/sslchat_types.cpp \
			src/SSLChatHandler.cpp \
			src/IOService.cpp

# OBJECTS 	= 	${SOURCES:%.cpp=%.o}

CC			=	g++
CFLAGS		= 	-std=c++11 -Wall

default: server client

server: ${STDAFX} server.cpp
	${CC} ${CFLAGS} -o server ${GEN_INC} ${INCS_DIRS} server.cpp ${SRC} ${LIBS_DIRS} ${LIBS}

# src/%.o: src/%.cpp
# 	${CC} $< ${CFLAGS} -o $@

client: ${STDAFX} client.cpp
	${CC} ${CFLAGS} -o client ${GEN_INC} ${INCS_DIRS} client.cpp ${SRC} ${LIBS_DIRS} ${LIBS}

${STDAFX}:
	${CC} ${CFLAGS} -x c++-header ${PCH_NAME}

clean:
	rm -r server client ${STDAFX}