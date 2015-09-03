#include "stdafx.h"

#include "gen-cpp/SSLChatService.h"

#define PORT 9090
#define THREAD_POOL_SIZE 15
#define LOG4CXX_OUTPUT "log/SSLChat.log"

using namespace std;
using namespace apache::thrift;
using namespace apache::thrift::concurrency;
using namespace apache::thrift::protocol;
using namespace apache::thrift::transport;
using namespace apache::thrift::server;
using namespace log4cxx;
using namespace log4cxx::helpers;

using namespace sslchat;

LoggerPtr logger = log4cxx::Logger::getLogger("SSLChat");

class SSLChatHandler : virtual public SSLChatServiceIf {
private:
	enum notification {JOIN, EXIT};
	map< string, queue< Message > > messages;
	// boost::condition_variable cond;
	// boost::shared_mutex w_lock;
	// boost::shared_mutex r_lock;
	/**
	* Send to all clients that user @name joins the chat.
	* Send user @name that he was successfully joined.
	*/
	void debugMap() {
		cout << "users in map:\t" << messages.size() << endl;
		for (std::map<string, queue< Message >>::iterator it = messages.begin(); it != messages.end(); ++it) {
			cout << "messages for " << it->first << ":\t" << it->second.size() << endl;
		}
	}

	void sendNotification(string name, notification type) {
		string log_msg = "User " + name + " ";

		for (std::map<string, queue< Message >>::iterator it = messages.begin(); it != messages.end(); ++it) {
			Message server_msg;
			server_msg.name = "Server";
			if(it->first.compare(name) != 0)
				server_msg.message = "User " + name + " ";
			else
				server_msg.message = "You ";

			switch(type) {
				case JOIN:
					server_msg.message += "joined the conversation.";
					log_msg += "joined the conversation.";
					break;
				case EXIT:
					server_msg.message += "left out the conversation.";
					log_msg += "left out the conversation.";
					break;
				default:
					break;
			}

			it->second.push(server_msg);
		}

		// cout << log_msg << endl;
		LOG4CXX_INFO(logger, log_msg);
		// debugMap();
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

		queue< Message > client_messages;
		messages.insert(std::pair<string, queue<Message>>(name_lower, client_messages));

		sendNotification(name_lower, notification::JOIN);
		return true;
	}

	/**
	* Send message to all clients without the message's author
	*/
	void send(const Message& msg) {
		std::map<string, queue< Message >>::iterator it;

		// cout << "got message from " << msg.name << endl;

		string name_lower = msg.name;
		std::transform(name_lower.begin(), name_lower.end(), name_lower.begin(), ::tolower);

		LOG4CXX_INFO(logger, "Got message from " << msg.name);

		if(msg.message.compare("exit") == 0) {
			sendNotification(name_lower, notification::EXIT);

			while(!messages[name_lower].empty()) {
				messages[name_lower].pop();
			}

			it = messages.find(name_lower);
			if (it != messages.end())
				messages.erase(it);
			return;
		}

		for (it = messages.begin(); it != messages.end(); ++it)
			if(it->first.compare(name_lower) != 0)
				messages[name_lower].push(msg);
	}

};

boost::shared_ptr<TSSLSocketFactory> getSSLSocketFactory() {
	boost::shared_ptr<TSSLSocketFactory> factory(new TSSLSocketFactory());
	factory->loadPrivateKey("/home/snape/programming/cpp/ssl-chat/ssl/server-key.pem");
	factory->loadCertificate("/home/snape/programming/cpp/ssl-chat/ssl/server-cert.pem");
	factory->server(true);
    factory->ciphers("ALL:!ADH:!LOW:!EXP:!MD5:@STRENGTH");

    return factory;
}

int main(int argc, char const *argv[]) {

	signal(SIGPIPE, SIG_IGN); 
	PropertyConfigurator::configure("log/config.props");

	boost::shared_ptr<SSLChatHandler> handler(new SSLChatHandler());
	boost::shared_ptr<TProcessor> processor(new SSLChatServiceProcessor(handler));
	boost::shared_ptr<TSSLSocketFactory> factory = getSSLSocketFactory();
	boost::shared_ptr<TSSLServerSocket> socket(new TSSLServerSocket(PORT, factory));
	boost::shared_ptr<TTransportFactory> transportFactory(new TBufferedTransportFactory());
	boost::shared_ptr<TProtocolFactory> protocolFactory(new TBinaryProtocolFactory());
  	boost::shared_ptr<ThreadManager> threadManager = ThreadManager::newSimpleThreadManager(THREAD_POOL_SIZE);
  	boost::shared_ptr<PosixThreadFactory> threadFactory = boost::shared_ptr<PosixThreadFactory>(new PosixThreadFactory());

  	threadManager->threadFactory(threadFactory);
  	threadManager->start();

  	TThreadPoolServer server(processor, socket, transportFactory, protocolFactory, threadManager);
	// TThreadedServer server(processor, socket, transportFactory, protocolFactory);

    cout << "Starting the server..." << endl;
    LOG4CXX_INFO(logger, "Starting server...");
    server.serve();
    cout << "Done." << endl;

	return 0;
}