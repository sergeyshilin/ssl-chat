#include "stdafx.h"

#include "gen-cpp/SSLChatService.h"

#define PORT 9090
#define THREAD_POOL_SIZE 15

using namespace std;
using namespace apache::thrift;
using namespace apache::thrift::concurrency;
using namespace apache::thrift::protocol;
using namespace apache::thrift::transport;
using namespace apache::thrift::server;

using namespace sslchat;

class SSLChatHandler : virtual public SSLChatServiceIf {
private:
	map< string, queue< Message > > messages;
	// boost::condition_variable cond;
	// boost::shared_mutex w_lock;
	// boost::shared_mutex r_lock;
	/**
	* Send to all clients that user @name joins the chat.
	* Send user @name that he was successfully joined.
	*/
	void sendGreating(const std::string& name) {
		string join_great = "You were successfully logged in with name " + name + ".";
		string user_join = "User " + name + " joined the conversation";
		
		for (std::map<string, queue< Message >>::iterator it = messages.begin(); it != messages.end(); ++it) {
			Message server_msg;
			server_msg.name = "Server";
			if(it->first.compare(name) != 0)
				server_msg.message = user_join;
			else
				server_msg.message = join_great;
			
			it->second.push(server_msg);
		}
    		
	}

	/**
	* Out message to client
	*/
	void getMessage(Message& _return, const std::string& name) {
		// boost::thread::upgrade_lock<boost::shared_mutex> readLock(r_lock);
		// readLock.lock();
		if(!messages[name].empty()) {
			_return = messages[name].front();
			messages[name].pop();
		} else {
			Message eof;
			eof.name = "Server";
			eof.message = "EOF";
			_return = eof;
		}

		// cond.notify_all();
	}

public:
	SSLChatHandler() {}

	/**
	* Check if name is in map
	*/
	bool authorize(const std::string& name) {
		string name_lower = name;
		std::map<string, queue<Message>>::iterator it;
		std::transform(name_lower.begin(), name_lower.end(), name_lower.begin(), ::tolower);
		it = messages.find(name_lower);
  		if (it != messages.end())
			return false;

		// goes here
		queue< Message > client_messages;
		messages.insert(std::pair<string, queue<Message>>(name_lower, client_messages));
		sendGreating(name_lower);
		return true;
	}

	/**
	* Send message to all clients without the message's author
	*/
	void send(const Message& msg) {

		string name_lower = msg.name;
		std::transform(name_lower.begin(), name_lower.end(), name_lower.begin(), ::tolower);

		for (std::map<string, queue< Message >>::iterator it = messages.begin(); it != messages.end(); ++it)
			if(it->first.compare(name_lower) != 0)
				messages[name_lower].push(msg);
	}

};

int main(int argc, char const *argv[]) {

	boost::shared_ptr<SSLChatHandler> handler(new SSLChatHandler());
	boost::shared_ptr<TProcessor> processor(new SSLChatServiceProcessor(handler));
    boost::shared_ptr<TProtocolFactory> protocolFactory(new TBinaryProtocolFactory());
    boost::shared_ptr<ThreadManager> threadManager = ThreadManager::newSimpleThreadManager(THREAD_POOL_SIZE);
    boost::shared_ptr<PosixThreadFactory> threadFactory = boost::shared_ptr<PosixThreadFactory>(new PosixThreadFactory());
    threadManager->threadFactory(threadFactory);
    threadManager->start();
    TNonblockingServer server(processor, protocolFactory, PORT, threadManager);

    cout << "Starting the server..." << endl;
    server.serve();
    cout << "Done." << endl;

	return 0;
}