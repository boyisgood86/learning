#include <iostream>
#include <string>

using namespace std;



class T
{
	private:
		int i;
		static int j;
};

class L
{
	private:
		int i;
};

class M
{
	private:
		int i;
		int j;
};

int main(int argc, char **argv)
{
	T t;
	cout << "t size is :" << sizeof(t) <<endl;
	L l;
	cout << "l size is :" << sizeof(l) << endl;
	M m;
	cout << "m size is :" << sizeof(m) << endl;
	return 0;
}
