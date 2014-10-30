#include <iostream>
#include <bitset>
#include <string>

using namespace std;

int main(void)
{
	cout <<__func__<<","<<__LINE__<<endl;
	

	int p2 = 10;

	const int *p1 = &p2;
//	int *s = p1;  /* error */
	return 0;
}

