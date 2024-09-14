#ifndef PAYMENT
#define PAYMENT

using namespace std;

class Payment
{
public:
	virtual bool processPayment(double amount) = 0;
	virtual ~Payment() = default;

};

#endif // !1