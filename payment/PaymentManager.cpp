#ifndef PAYMENT_MANAGER
#define PAYMENT_MANAGER

#include <memory>
#include "Payment.h"

using namespace std;

class PaymentManager
{
private:
	shared_ptr<Payment> paymentStrategy;

public:
	PaymentManager(shared_ptr<Payment> paymentstrategy)
		:paymentStrategy(paymentstrategy)
	{}

	bool makePayment(double amount) {
		return paymentStrategy->processPayment(amount);
	}
};

#endif // !PAYMENT_MANAGER