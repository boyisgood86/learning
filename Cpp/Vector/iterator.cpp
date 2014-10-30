#include <iostream>
#include <vector>


using namespace std;



int main(void)
{
	vector<int> n(10, 0x01);
	
	for(vector<int>::iterator i = n.begin(); i != n.end();++i)
		cout << *i ;
	cout << endl;

	for(vector<int>::size_type k = 0; k != n.size();++k)
		n[k] = 0;
	for(vector<int>::size_type k = 0; k != n.size();++k)
		cout << n[k] << " ";
	cout << endl;

	for(vector<int>::iterator i = n.begin(); i != n.end();++i)
		*i = 5;
	for(vector<int>::iterator i = n.begin(); i != n.end();++i)
		cout << *i;
	cout << endl;

	int l = 0;
	for(vector<int>::iterator i = n.begin(); i != n.end();i++)
	{
		*i = l;
		l++;
	}
	for(vector<int>::const_iterator i = n.begin(); i != n.end();i++)
	{
//		*i = 0x02; /*error*/
		cout << *i << " ";
	}
	cout << endl;
	

	for(vector<int>::const_iterator i = n.begin(); i != n.end(); i++)
		cout << *i;
	cout <<endl;

	vector<int>::const_iterator mid = n.begin() + n.size()/2;
	cout <<"mid value is :" << *mid << endl;

	// undefine
/*
	vector<int>::const_iterator mid_val = (n.begin()+n.end())/2;
	cout <<"mid value is :" << *mid << endl;
*/

	
	return 0;
}

