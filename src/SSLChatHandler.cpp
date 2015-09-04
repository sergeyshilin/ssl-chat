#include "../stdafx.h"
#include "SSLChatHandler.h"

using namespace sslchat;
using namespace std;

void SSLChatHandler::debugMap() {
	cout << "users in map:\t" << messages.size() << endl;
	for (std::map<string, queue< Message >>::iterator it = messages.begin(); it != messages.end(); ++it) {
		cout << "messages for " << it->first << ":\t" << it->second.size() << endl;
	}
}

void SSLChatHandler::sendNotification(string name, notification type) {
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

	// LOG4CXX_INFO(logger, log_msg);
}

void SSLChatHandler::getMessage(Message& _return, const std::string& name) {
	if(!messages[name].empty()) {
		_return = messages[name].front();
		messages[name].pop();
	} else {
		Message eof;
		eof.name = "Server";
		eof.message = "EOF";
		_return = eof;
	}
}

bool SSLChatHandler::authorize(const std::string& name) {
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

void SSLChatHandler::send(const Message& msg) {
	std::map<string, queue< Message >>::iterator it;

	string name_lower = msg.name;
	std::transform(name_lower.begin(), name_lower.end(), name_lower.begin(), ::tolower);

	// LOG4CXX_INFO(logger, "Got message from " << msg.name);

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