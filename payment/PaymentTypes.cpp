#ifndef PAYMENT_TYPE
#define PAYMENT_TYPE

#include <iostream>
#include <string>
#include "Payment.h"

using namespace std;

class CreditCardPayment : public Payment
{
public:
	bool processPayment(double amount) {
		cout << "****** Processing Credit Card Payment of $" << amount << endl;
		cout << endl;
		return true;
	}
};

class PayPalPayment : public Payment
{
public:
	bool processPayment(double amount) {
		cout << "****** Processing PayPal Payment of $" << amount << endl;
		cout << endl;
		return true;
	}
};

class StripPayment : public Payment
{
public:
	bool processPayment(double amount) {
		cout << " ****** Processing Strip Payment of $" << amount << endl;
		cout << endl;
		return true;
	}
};

#endif // !PAYMENT_TYPE
