#include <iostream>
using namespace std;
class Complex //����Complex��
{
	public:
		Complex();    //���幹�캯��
		Complex(double real,double imag);  //���캯������
		~Complex();
		Complex complex_add(Complex &c2);  //����������Ӻ���
		void display( );  //�����������
	private:
		double real;  //ʵ��
		double imag;  //�鲿
};

Complex::Complex(double real, double imag)
{
	this->real = real;
	this->imag = imag;
	cout << "Complex(double, double)----------->" << endl;
}

Complex::Complex()
{
	cout << "Complex()------------------>" << endl;
}


Complex::~Complex()
{
	cout << "<---------------~Complex()------------>"<<endl;
}

Complex Complex::complex_add(Complex &c2)
{
	Complex c;
	c.real=real+c2.real;
	c.imag=imag+c2.imag;
	return c;
}

void Complex::display( ) //�����������
{
	cout<<"("<<real<<","<<imag<<"i)"<<endl;
}
int main( )
{
	Complex c1(3,4),c2(5,-10),c3;//����3����������
	c3=c1.complex_add(c2); //���ø�����Ӻ���
	cout<<"c1="; c1.display( );//���c1��ֵ
	cout<<"c2="; c2.display( );//���c2��ֵ
	cout<<"c1+c2="; c3.display( );//���c3��ֵ
	return 0;
}
