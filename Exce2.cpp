#include <exception>
#include <iostream>
#include <stdexcept>
#include <string>

class ArrayException : public std::runtime_error
{
public:
	ArrayException(const std::string& error)
		: std::runtime_error(error)
	{

	}
	
	//no need to override what() since we can just use std::runtime_error::what()
};

class IntArray
{
private:
	int _data[3];

public:
	IntArray() {};

	int getLength() const { return 3; };

	int& operator[](int index)
	{
		if (index < 0 || index >= getLength())
			throw ArrayException("Invalid index");
		return _data[index];
	}
};

int main()
{
	IntArray array;

	try
	{
		int value = array[5];
	}
	catch (const ArrayException& exception)
	{
		std::cerr << "An array exception occurred: " << exception.what() << "\n";
	}
	catch (const std::exception& exception)
	{
		std::cerr << "Some other std::exception occurred: " << exception.what() << "\n";
	}
	return 0;
}



