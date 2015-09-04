#include "../stdafx.h"
#include "../gen-cpp/SSLChatService.h"

using namespace sslchat;
using namespace std;

class IOService {
public:
	static bool EXIT_TRIGGER;

	static void read(SSLChatServiceClient client, string name, bool * exit);

	static void write(SSLChatServiceClient client, string name, bool * exit);
};