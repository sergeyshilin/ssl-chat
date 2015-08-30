#include "../stdafx.h"

using namespace test;

class MultiplicationHandler : virtual public MultiplicationServiceIf {
public:
	MultiplicationHandler() {}

	void ping();

	int32_t add(int32_t num1, int32_t num2);
};