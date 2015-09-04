#include "../stdafx.h"
#include "../gen-cpp/SSLChatService.h"

using namespace sslchat;
using namespace std;
using namespace log4cxx;
using namespace log4cxx::helpers;

class SSLChatHandler : virtual public SSLChatServiceIf {
private:
	enum notification {JOIN, EXIT};
	map< string, queue< Message > > messages;
	LoggerPtr logger = log4cxx::Logger::getLogger("SSLChat");

	/**
	* Send to all clients that user @name joins the chat.
	* Send user @name that he was successfully joined.
	*/
	void debugMap();

	/**
	* Send server message to client
	*/
	void sendNotification(string name, notification type);

	/**
	* Out message to client
	*/
	void getMessage(Message& _return, const std::string& name);

public:
	SSLChatHandler() {}

	/**
	* Check if name is in map
	*/
	bool authorize(const std::string& name);

	/**
	* Send message to all clients without the message's author
	*/
	void send(const Message& msg);

};