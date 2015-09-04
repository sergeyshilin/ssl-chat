#include "stdafx.h"

#include "gen-cpp/SSLChatService.h"
#include "src/IOService.h"

#define HOST "localhost"
#define PORT 9090


using namespace std;
using namespace apache::thrift;
using namespace apache::thrift::protocol;
using namespace apache::thrift::transport;

using namespace sslchat;

boost::shared_ptr<TSSLSocketFactory> getSSLSocketFactory() {
	boost::shared_ptr<TSSLSocketFactory> factory(new TSSLSocketFactory());
	factory->loadPrivateKey("/home/snape/programming/cpp/ssl-chat/ssl/client-key.pem");
	factory->authenticate(true);
	factory->loadTrustedCertificates("/home/snape/programming/cpp/ssl-chat/ssl/server-cert.pem");
    factory->ciphers("ALL:!ADH:!LOW:!EXP:!MD5:@STRENGTH");

    return factory;
}

int main(int argc, char const *argv[]) {

	signal(SIGPIPE, SIG_IGN); 

	boost::shared_ptr<TSSLSocketFactory> factory = getSSLSocketFactory();
	boost::shared_ptr<TSSLSocket> socket = factory->createSocket(HOST, PORT);
	boost::shared_ptr<TBufferedTransport> transport(new TBufferedTransport(socket));
	boost::shared_ptr<TProtocol> protocol(new TBinaryProtocol(transport));
	SSLChatServiceClient client(protocol);

	try {
	    transport->open();

	    string name;
	    Message msg;

	    cout << "Hi, we're glad to see you! \n Please enter your unique name to get an access and \n be able to send and receive messages from other users" << endl;

	    bool auth = false;
	    do {
			getline(std::cin, name);
			auth = client.authorize(name);
			if(!auth)
				cout << "This name is in use yet. Please try another one." << endl;
	    } while (!auth);	

	    bool EXIT_TRIGGER = false;

		std::thread t1(IOService::read, client, name, &EXIT_TRIGGER);
		std::thread t2(IOService::write, client, name, &EXIT_TRIGGER);

		t1.join();
		t2.join();

    	transport->close();
	} catch (TException& tx) {
		cout << "ERROR: " << tx.what() << endl;
	}

	return 0;
}