#include "stdafx.h"

// #include "src/multiply.h"
#include "gen-cpp/SSLChatService.h"

using namespace std;
using namespace apache::thrift;
using namespace apache::thrift::concurrency;
using namespace apache::thrift::protocol;
using namespace apache::thrift::transport;
using namespace apache::thrift::server;

using namespace sslchat;

class SSLChatHandler : virtual public SSLChatServiceIf {
private:
	map<string, SSLChatServiceClient> clients;
	/**
	* Send to all clients that user @name joins the chat.
	* Send user @name that he was successfully joined.
	*/
	void sendGreating(const std::string& name) {
		string join_great = "You were successfully logged in with name " + name + ".";
		string user_join = "User " + name + " joined the conversation";
		// clients[name].getMessage(join_great);
		// clients[others].getMessage(user_join);
	}

	/**
	* Out message to client
	*/
	void getMessage(std::string& _return, const std::string& msg) {
		_return = msg;
	}

public:
	SSLChatHandler() {}

	/**
	* Check if name is in map
	*/
	bool authorize(const std::string& name) {
		sendGreating(name);
		return true;
	}

	/**
	* Send message to all clients without the message's author
	*/
	void send(const Message& message) {
	}

};

int main(int argc, char const *argv[]) {

	boost::shared_ptr<TProtocolFactory> protocolFactory(new TBinaryProtocolFactory());
	boost::shared_ptr<SSLChatHandler> handler(new SSLChatHandler());
	boost::shared_ptr<TProcessor> processor(new SSLChatServiceProcessor(handler));
	boost::shared_ptr<TServerTransport> serverTransport(new TServerSocket(9090));
	boost::shared_ptr<TTransportFactory> transportFactory(new TBufferedTransportFactory());

  	TSimpleServer server(processor, serverTransport, transportFactory, protocolFactory);

	cout << "Starting the server..." << endl;
	server.serve();
	cout << "Done." << endl;

	return 0;
}