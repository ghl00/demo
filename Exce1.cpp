#include <cstddef>
#include <exception>
#include <iostream>
#include <limits>
#include <string>
#include <stdexcept>

class ArrayException : public std::exception
{
private:
	std::string m_error;

public:
	ArrayException(std::string_view error)
		: m_error(error)
	{

	}

	const char* what() const noexcept override { return m_error.c_str(); };
};

class IntArray
{
private:
	int m_data[3];

public:
	IntArray() {};

	int getLength() const { return 3; };

	int& operator[](const int index)
	{
		if (index < 0 || index >= getLength())
			throw ArrayException("Invalid index");

		return m_data[index];
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
		std::cerr << "Some other Standard exception occurred: " << exception.what() << "\n";
	}
	return 0;
}