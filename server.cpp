#include "stdafx.h"

#include "gen-cpp/SSLChatService.h"
#include "src/SSLChatHandler.h"

#define PORT 9090
#define THREAD_POOL_SIZE 15

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

    cout << "Starting the server..." << endl;
    LOG4CXX_INFO(logger, "Starting server...");
    server.serve();
    cout << "Done." << endl;

	return 0;
}