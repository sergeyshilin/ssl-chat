namespace cpp sslchat

struct Message {
	1: string name,
	2: string message
}

service SSLChatService {

  /**
   * A method definition looks like C code. It has a return type, arguments,
   * and optionally a list of exceptions that it may throw. Note that argument
   * lists and exception lists are specified using the exact same syntax as
   * field lists in struct or exception definitions.
   */

	/**
	* Out message to client
	*/
	Message getMessage(1:string name),

	/**
	* Check if name is in map
	*/
	bool authorize(1:string name),

	/**
	* Send message to all clients without message.getClient()
	*/
	void send(1:Message msg)

}