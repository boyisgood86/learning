#include <iostream>

using namespace std;


class F
{
	public:
		int i;
};

class C:public F
{
	public:
		int j;
};




int main(int argc, char **argv)
{
	F f;
    C c;

 	cout << "f size is :" << sizeof(f)<<endl;
	cout << "c size is :" << sizeof(c) << endl;

	return 0;
}


