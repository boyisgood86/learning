#include <iostream>
#include <string>

using namespace std;

char &get_val(string &str, string::size_type ix)
{
	cout << str[ix] << endl;
	return str[ix];
	//return str;
}


int main()
{
	string s("a value");
	cout << s << endl;
	get_val(s, 5) = 'A';
//	get_val(s, 5);

	cout << s << endl;

	return 0;
}

