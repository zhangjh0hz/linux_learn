/*************************************************************************
    > File Name: class_test.cpp
# Author: ZJH
# mail: 1098706006@qq.com
    > Created Time: 2018年11月09日 星期五 17时26分41秒
 ************************************************************************/

#include<iostream>
using namespace std;

class A
{
public:
	A(){
		cout<< "A Construct" << endl;
	}

	void func(){
		cout << "A func"<< endl;
	}
};

class B : public A
{
public:
	B(){
		cout << "B Construct" << endl;
	}

	void func(){
		cout << "B func" << endl;
	}
};

int main()
{	
	A a;
	a.func();
	B b;
	b.func();
	A* pa = new B;
	pa->func();
	return 0;
}
