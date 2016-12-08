#include <iostream>

using namespace std;

// String Buffer class
class String_Buffer {

private:

	// string buffer
	char* string_buffer;
	// string size
	int size;
	// reference count
	int reference_count;

public:

	// default constructor
	String_Buffer()
	{
		string_buffer = NULL;
		size = 0;
		reference_count = 1;
	}

	// destructor
	~String_Buffer()
	{
		delete[size] string_buffer;
		size = 0;
	}

	// parametrized / overload constructor
	String_Buffer(char* string, int length)
	{
		string_buffer = NULL;
		size = 0;
		reference_count = 1;

		allocate(length);

		for (int i = 0; i < length; ++i)
		{
			string_buffer[i] = string[i];
		}
	}

	// parametrized / overload constructor
	// deep copy
	String_Buffer(String_Buffer* source)
	{
		string_buffer = NULL;
		size = 0;
		reference_count = 1;

		allocate(source->size);

		for (int i = 0; i < size; ++i)
		{
			this->string_buffer[i] = source->string_buffer[i];
		}
	}

	// returns character at specified index
	char char_at(int index) const
	{
		if (index < size)
		{
			return string_buffer[index];
		}
		else
		{
			cout << "Error! Index out of bound!";
			return ' ';
		}
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
	void append(char character)                          //appends a single character at the end
	{
		char* new_string = new char[size + 1];
		for (int i = 0; i < size; i++)
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

	// increments reference count
	void add_reference() {
		++reference_count;
	}

	// decrements reference count
	void remove_reference() {
		--reference_count;
	}

	// returns reference count
	int get_references() {
		return reference_count;
	}

};

// String class
class String {

private:

	// string buffer
	String_Buffer* string_buffer;

public:

	// default constructor
	String()
	{
		string_buffer = NULL;
	}

	// parametrized / overload constructor
	String(char* input_string, int length)
	{
		string_buffer = new String_Buffer(input_string, length);
	}

	// destructor
	~String()
	{
		string_buffer->remove_reference();
		if (string_buffer->get_references() == 0)
		{
			delete string_buffer;
		}
	}

	// parametrized / overload constructor
	String(String& source)
	{
		this->string_buffer = source.string_buffer;
		this->string_buffer->add_reference();
	}

	// returns character at specified index
	char char_at(int index) const
	{
		if (string_buffer != NULL)
		{
			return string_buffer->char_at(index);
		}
		return ' ';
	}

	// returns size of string buffer
	int length() const
	{
		if (string_buffer != NULL)
		{
			return string_buffer->length();
		}
		return 0;
	}

	// appends character at the end
	void append(char character)
	{
		if (string_buffer == NULL)
		{
			string_buffer = new String_Buffer;
		}
		else if (string_buffer->get_references() > 1)
		{
			String_Buffer* newBuffer = new String_Buffer(string_buffer);
			string_buffer->remove_reference();
			string_buffer = newBuffer;
		}
		string_buffer->append(character);
	}

	void print()
	{
		if (string_buffer != NULL)
		{
			string_buffer->print();
		}
	}

};

int main(void)
{
	cout << "OUTER SCOPE" << endl << endl;

	String string_1("HELLO", 5);

	cout << "String 1: ";
	string_1.print();
	cout << endl << endl;

	{
		cout << "INNER SCOPE" << endl << endl;

		String string_2(string_1);

		cout << "String 2: ";
		string_2.print();
		cout << endl << endl;

		cout << "String 1: ";
		string_1.print();
		cout << endl << endl;

		string_1.append(' ');
		string_1.append('F');
		string_1.append('A');
		string_1.append('H');
		string_1.append('A');
		string_1.append('D');
		string_1.append('!');

		cout << "After append \" FAHAD!\" in String 1" << endl << endl;

		cout << "String 1: ";
		string_1.print();
		cout << endl << endl;

		cout << "String 2: ";
		string_2.print();
		cout << endl << endl;

	}

	cout << "OUTER SCOPE" << endl << endl;

	cout << "String 1: ";
	string_1.print();
	cout << endl << endl;

	return 0;
}