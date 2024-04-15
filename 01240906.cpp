#include <iostream>

class A
{
private:
	int _x;

public:
	A(int x) : _x(x)
	{
		if (x <= 0)
			throw 1;
	}
};

class B : public A
{
public:
	B(int x) : A(x)
	{

	}
};

int main()
{
	try
	{
		B b(0);
	}
	catch (int)
	{
		std::cout << "Oops\n";
	}
	return 0;
}