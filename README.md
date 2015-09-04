# Thrift SSL multithread server-client chat
This application has been compiled on my laptop 
> Linux snape-ubuntu 3.19.0-26-generic

## Prepare
To compile this application on your own you have to configure and install all the next libs:
* boost
* thrift
	* flex
	* bison
	* libevent
* openssl
* log4cxx

There are a lot of information in the Internet about configuration Thrift.

## Configure
Change following constants on your own at Makefile
```
THRIFT_DIR	= 	/usr/lib/thrift/lib/cpp/test
BOOST_DIR	= 	/usr/include/boost
LOG4CXX_DIR	= 	/usr/lib/apache-log4cxx-0.10.0/src/main/include
THRIFT_LIBS	= 	/usr/local/lib
BOOST_LIBS 	= 	/usr/lib/x86_64-linux-gnu
```
and also generate your own server and client ssl certificates:
### Generate the server private key:
```
snape@snape-ubuntu:~/programming/cpp/ssl-chat$ openssl genrsa -out server-key.pem 2048
```
### Generate the associated public key and self-sign it:
```
snape@snape-ubuntu:~/programming/cpp/ssl-chat$ openssl req -new -x509 -key server-key.pem -out server-cert.pem -days 10000
```
### Generate the client private key:
```
snape@snape-ubuntu:~/programming/cpp/ssl-chat$ openssl genrsa -out client-key.pem 2048
```
### Generate the associated public key and self-sign it:
```
snape@snape-ubuntu:~/programming/cpp/ssl-chat$ openssl req -new -x509 -key client-key.pem -out client-cert.pem -days 10000
```


## Run applications

Firstly, build the application via command
```
snape@snape-ubuntu:~/programming/cpp/ssl-chat$ make clean
snape@snape-ubuntu:~/programming/cpp/ssl-chat$ make server
snape@snape-ubuntu:~/programming/cpp/ssl-chat$ make client
```
or simply
```
snape@snape-ubuntu:~/programming/cpp/ssl-chat$ make clean
snape@snape-ubuntu:~/programming/cpp/ssl-chat$ make
```

To start up the server type to the console
```
snape@snape-ubuntu:~/programming/cpp/ssl-chat$ ./server
```

To run the client application type the next
```
snape@snape-ubuntu:~/programming/cpp/ssl-chat$ ./client
```