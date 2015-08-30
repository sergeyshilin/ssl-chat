#include "stdafx.h"

// #include "src/multiply.h"
#include "gen-cpp/MultiplicationService.cpp"

using namespace std;
using namespace apache::thrift;
using namespace apache::thrift::concurrency;
using namespace apache::thrift::protocol;
using namespace apache::thrift::transport;
using namespace apache::thrift::server;

using namespace test;

class MultiplicationHandler : virtual public MultiplicationServiceIf {
public:
	MultiplicationHandler() {}

	void ping() {
		cout << "ping!" << endl;
	}

	int32_t add(int32_t num1, int32_t num2) {
		return num1 + num2;
	}
};

int main(int argc, char const *argv[]) {

	boost::shared_ptr<TProtocolFactory> protocolFactory(new TBinaryProtocolFactory());
	boost::shared_ptr<MultiplicationHandler> handler(new MultiplicationHandler());
	boost::shared_ptr<TProcessor> processor(new MultiplicationServiceProcessor(handler));
	boost::shared_ptr<TServerTransport> serverTransport(new TServerSocket(9090));
	boost::shared_ptr<TTransportFactory> transportFactory(new TBufferedTransportFactory());

  	TSimpleServer server(processor, serverTransport, transportFactory, protocolFactory);

	cout << "Starting the server..." << endl;
	server.serve();
	cout << "Done." << endl;

	return 0;
}