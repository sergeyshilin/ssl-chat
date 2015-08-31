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
	* Send to all clients that user @name joins the chat.
	* Send user @name that he was successfully joined.
	*/
	void sendGreating(1:string name),

	/**
	* Out message to client
	*/
	string getMessage(1:string msg),

	/**
	* Check if name is in map
	*/
	bool authorize(1:string name),

	/**
	* Send message to all clients without message.getClient()
	*/
	void send(1:Message message)

}