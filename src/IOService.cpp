#include "../stdafx.h"
#include "IOService.h"

#define MSG_SLEEP_TIME 300

void IOService::read(SSLChatServiceClient client, string name, bool * exit) {
	while(true) {

		Message msg;
		client.getMessage(msg, name);
		if(msg.message.compare("EOF") != 0)
    		cout << msg.name << ":: " << msg.message << endl;
    	std::this_thread::sleep_for(std::chrono::milliseconds(MSG_SLEEP_TIME));

    	if(*exit)
			return;
    }
}

void IOService::write(SSLChatServiceClient client, string name, bool * exit) {
	string input;
	do {
		getline(std::cin, input);

		Message send;
		send.name = name;
		send.message = input;
		client.send(send);
	} while (input.compare("exit") != 0);

	*exit = !*exit;
	return;
}