#include<iostream>
#include<iomanip>
#include<string>

#define neicun 1024

using namespace std;

// �εĽṹ��
struct kongxian {
	unsigned int length;
	unsigned int addr;
	int flag;
	kongxian *next; // ��һ�ε�ָ��
};

struct Duanbiao
{
	int jincheng;
	unsigned int duannum;
	unsigned int addr;
	unsigned int length;
	int flag; // �ڴ�����
	Duanbiao *next;
};

kongxian *Khead; // ��������ͷָ��
kongxian *creatK(); // ������ʼ������
Duanbiao *Dhead; // ����α�ͷָ��
Duanbiao *Dfenpei; // �ѷ��������ͷ
Duanbiao *qingqiuD(Duanbiao *head); // ��������Ľ��̼�����
kongxian *zuixian(Duanbiao *head); // 
kongxian *sort(kongxian *head);
int huishou();
int select;
char ch;
int jinchengming;
int jinchenghuishou();
int duanhuishou();
int Display();
void space(int n);

