#include <iostream>

using namespace std;

// String Buffer class
class String_Buffer {

private:

	// string buffer
	char* string_buffer;
	// string size
	int size;

public:

	// default constructor
	String_Buffer()
	{
		string_buffer = NULL;
		size = 0;
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

		allocate(length);

		for (int i = 0; i < length; ++i)
		{
			this->string_buffer[i] = string[i];
		}
	}

	// parametrized / overload constructor
	// deep copy
	String_Buffer(String_Buffer* source)
	{
		string_buffer = NULL;
		size = 0;

		allocate(source->size);

		for (int i = 0; i < size; ++i)
		{
			string_buffer[i] = source->string_buffer[i];
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
	void append(char character)
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

};

// String  class
class String {

private:

	// string buffer
	String_Buffer* string_buffer;
	// pointers for reference linking
	String* next;
	String* previous;

public:

	// default constructor
	String()
	{
		string_buffer = NULL;
		next = this;
		previous = this;
	}

	// parametrized / overload constructor
	String(char* input_string, int length)
	{
		next = this;
		previous = this;
		string_buffer = new String_Buffer(input_string, length);
	}

	// destructor
	~String()
	{
		previous->next = next;
		next->previous = previous;
		if (this->next == this)
		{
			delete string_buffer;
		}
	}

	// parametrized / overload constructor
	// shallow copy
	String(String& source)
	{
		this->string_buffer = source.string_buffer;
		this->next = source.next;
		this->previous = &source;
		source.next = this;
		this->next->previous = this;
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
		else if (this->next != this)
		{
			String_Buffer* new_buffer = new String_Buffer(string_buffer);
			previous->next = next;
			next->previous = previous;
			next = this;
			previous = this;
			string_buffer = new_buffer;
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