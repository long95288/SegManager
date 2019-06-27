#include "stdafx.h"
#include"TestLib.h"
#include<iostream>
using namespace std;
void HelloWorld() {
	cout << "Hello World" << endl;
}
void add(int a, int b) {
	a = a + b;
}
void add2(int &a, int b) {
	a = a + b;
}