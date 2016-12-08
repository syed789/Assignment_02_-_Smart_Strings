#include <iostream>

using namespace std;

class String {

private:

	// string buffer
	char* string_buffer;
	// string size
	int size;

public:

	// default constructor
	String()
	{
		string_buffer = NULL;
		size = 0;
	}

	// destructor
	~String()
	{
		delete[size] string_buffer;
		size = 0;
	}

	// parametrized / overload constructor
	// deep copy
	String(const String& source)
	{
		string_buffer = new char[source.size];
		for (int i = 0; i < source.size; ++i)
		{
			this->string_buffer[i] = source.string_buffer[i];
		}
		this->size = source.size;
	}

	// parametrized / overload constructor
	String(char* string, int length)
	{
		string_buffer = NULL;
		size = 0;

		allocate(length);

		for (int i = 0; i < length; ++i)
		{
			string_buffer[i] = string[i];
		}
	}

	// returns character at specified index
	char char_at(int index) const
	{
		if (index < size)
			return string_buffer[index];
	}

	// returns size of string buffer
	int length() const
	{
		return size;
	}

	// allocate memory
	void allocate(int length)
	{
		delete[] string_buffer;
		string_buffer = new char[length];
		size = length;
	}

	// appends character at the end
	void append(char character)
	{
		char* new_string = new char[size + 1];
		for (int i = 0; i < size; ++i)
		{
			new_string[i] = string_buffer[i];
		}
		new_string[size] = character;
		delete[size] string_buffer;
		string_buffer = new_string;
		++size;
	}

	void print()
	{
		for (int i = 0; i < size; ++i)
		{
			cout << string_buffer[i];
		}
	}
};

int main(void)
{
	String string_1("HELLO", 5);
	String string_2(string_1);

	cout << "String 1: ";
	string_1.print();
	cout << endl << endl;

	cout << "String 2: ";
	string_2.print();
	cout << endl << endl;

	string_2.append(' ');
	string_2.append('F');
	string_2.append('A');
	string_2.append('H');
	string_2.append('A');
	string_2.append('D');
	string_2.append('!');

	cout << "After append \" FAHAD!\" in String 2" << endl << endl;

	cout << "String 1: ";
	string_1.print();
	cout << endl << endl;

	cout << "String 2: ";
	string_2.print();
	cout << endl << endl;

	return 0;
}