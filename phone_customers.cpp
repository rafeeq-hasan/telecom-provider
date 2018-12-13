#include <map>
#include <set>
#include <list>
#include <cmath>
#include <ctime>
#include <deque>
#include <queue>
#include <stack>
#include <string>
#include <bitset>
#include <cstdio>
#include <limits>
#include <vector>
#include <climits>
#include <cstring>
#include <cstdlib>
#include <fstream>
#include <numeric>
#include <sstream>
#include <iostream>
#include <algorithm>
#include <unordered_map>

using namespace std;

// We need 3 APIs:
// - Get all phone numbers
// - Get all phone numbers of a single customer
// - Activate a phone number

class Customer
{
private:
	long customerId;
	string fullName;
	vector<string> phoneNumbers;

public:
	Customer(long id, string name, vector<string> numbers)
	: customerId(id),
	  fullName(name)
	{
		for (auto num : numbers)
			phoneNumbers.push_back(num);
	}

	long getCustomerId() { return customerId; }
	
	string getCustomerName() { return fullName; }
	
	vector<string> getCustomerPhoneNumbers()
	{
		vector<string> res;
		for (auto num : phoneNumbers)
			res.push_back(num);

		return res;
	}

	void addPhoneNumber(string phoneNumber)
	{
		phoneNumbers.push_back(phoneNumber);
	}

	void printCustomer()
	{
		cout << "ID: " << customerId << endl;
		cout << "Name: " << fullName << endl;
		cout << "Phone num/s:\n";
		for (auto num : phoneNumbers)
			cout << "  " << num << endl;
	}
};

class CustomerBase
{
private:
	vector<Customer> allCustomers;

public:
	vector<vector<string>> getAllPhoneNumbers()
	{
		vector<vector<string>> res;

		for (auto cust : allCustomers)
			res.push_back(cust.getCustomerPhoneNumbers());
			
		return res;
	};

	vector<string> getCustomerPhoneNumbers(long custId)
	{
		vector<string> res;

		for (auto cust : allCustomers)
		{
			if (cust.getCustomerId() == custId)
			{
				res = cust.getCustomerPhoneNumbers();
			}
		}

		return res;
	}

	void activatePhoneNumber(long custId, string number)
	{
		for (int i = 0; i < allCustomers.size(); ++i)
		{
			if (allCustomers[i].getCustomerId() == custId)
			{
				Customer c = allCustomers[i];
				allCustomers.erase(allCustomers.begin() + i);
				c.addPhoneNumber(number);
				allCustomers.push_back(c);
			}
		}
	}

	void addCustomer(Customer &cust)
	{
		allCustomers.push_back(cust);
	}

	void printCustomer(long custId)
	{
		for (auto cust : allCustomers)
		{
			if (cust.getCustomerId() == custId)
			{
				cust.printCustomer();
			}
		}
	}

	void printAllCustomers()
	{
		for (auto cust : allCustomers)
		{
			cust.printCustomer();
			cout << endl;
		}
	}
};

int main()
{
	CustomerBase custs;

	Customer c1(123, "John Smith", {"02345678901"});
	Customer c2(555, "Alice Jones", {"02221160606"});
	Customer c3(642, "Dr Chris Brown", {"07428160996", "01435434642"});

	custs.addCustomer(c1);
	custs.addCustomer(c2);
	custs.addCustomer(c3);

	cout << "ALL CUSTOMERS" << endl;
	cout << "-------------" << endl;
	custs.printAllCustomers();

	cout << "\nACTIVATE A NUMBER FOR ALICE" << endl;
	cout << "---------------------------" << endl;

	custs.activatePhoneNumber(555, "01615141312");
	custs.printCustomer(555);

	cout << "\nALL CUSTOMERS" << endl;
	cout << "-------------" << endl;
	custs.printAllCustomers();

	return 0;
}