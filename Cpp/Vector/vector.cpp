#include <iostream>
#include <vector>

using namespace std;

int main(void)
{
	vector<int> n;   /*ok*/
	vector< vector<int> > r;  /*ok*/
	vector<string> s(10, "hello");
	for(vector<string>::size_type i = 0; i != s.size();i++)
		cout << s[i] << " ";
	cout << endl;
	s.push_back("!");
	for(vector<string>::size_type i = 0; i != s.size();i++)
	{
		cout << s[i] << " ";
		s[i] = "hi";
	}
	cout << endl;
	if(!s.empty())
		cout << "vector<string> s size is : " << s.size() <<endl;
	else
		cout << "vector<string> s is empty !" << endl;
	
	for(vector<string>::size_type i = 0; i != s.size();i++)
		cout << s[i] << " ";
	cout << endl;

//	cout <<s[12] << endl; //Segmentation fault

	return 0;
}

