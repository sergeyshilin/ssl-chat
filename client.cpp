#include "stdafx.h"

#include "gen-cpp/SSLChatService.h"

#define MSG_SLEEP_TIME 100


using namespace std;
using namespace apache::thrift;
using namespace apache::thrift::protocol;
using namespace apache::thrift::transport;

using namespace sslchat;

class IOService {
public:
	static void read(SSLChatServiceClient client, string name) {
		while(true) {
			Message msg;
			client.getMessage(msg, name);
			if(msg.message.compare("EOF") != 0 && msg.name.compare("Server") != 0)
	    		cout << msg.name << ":: " << msg.message << endl;
	    	std::this_thread::sleep_for(std::chrono::milliseconds(MSG_SLEEP_TIME));
	    }
	}

	static void write() {
		string input;
		do {
			cin >> input;
		} while (input.compare("exit") != 0);
	}
};

int main(int argc, char const *argv[]) {

	boost::shared_ptr<TTransport> socket(new TSocket("localhost", 9090));
	boost::shared_ptr<TTransport> transport(new TFramedTransport(socket));
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
				cout << "This name is in use yet. Please try another one" << endl;
	    } while (!auth);			

	   std::thread t1(IOService::read, client, name);
	   t1.join();
	   IOService::write();

	   t1.detach();

    	transport->close();
	} catch (TException& tx) {
		cout << "ERROR: " << tx.what() << endl;
	}

	return 0;
}