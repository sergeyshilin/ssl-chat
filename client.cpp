#include "stdafx.h"

#include "gen-cpp/MultiplicationService.cpp"


using namespace std;
using namespace apache::thrift;
using namespace apache::thrift::protocol;
using namespace apache::thrift::transport;

using namespace test;

int main(int argc, char const *argv[]) {

	boost::shared_ptr<TTransport> socket(new TSocket("localhost", 9090));
	boost::shared_ptr<TTransport> transport(new TBufferedTransport(socket));
	boost::shared_ptr<TProtocol> protocol(new TBinaryProtocol(transport));
	SSLChatServiceClient client(protocol);

	try {
	    transport->open();

	    string name;

	    cout << "Hi, we're glad to see you! \n Please enter your unique name to get an access and \n be able to send and receive messages from other users" << endl;

	    do
	    {
			cin >> name;
			bool auth = client.authorize(name);
			if(!auth)
				cout << "This name is in use yet. Please try another one" << endl;
	    } while (!auth);			

	    // client.ping();
	    // cout << "ping()" << endl;

	    // cout << "1 + 1 = " << client.add(1, 1) << endl;

	    transport->close();
	  } catch (TException& tx) {
	    cout << "ERROR: " << tx.what() << endl;
	  }

	return 0;
}