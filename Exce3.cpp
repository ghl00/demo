#include <iostream>

class Base
{
public:
	Base() {};
};

class Derived : public Base
{
public:
	Derived() {};
	Derived(const Derived&) = delete;
};

int main()
{
	Derived d;
	try
	{
		//throw d; // compile error
	}
	catch (const Derived& derived)
	{
		std::cerr << "caught Derived";
	}
	catch (const Base& base)
	{
		std::cerr << "caught Base";
	}
	return 0;
}