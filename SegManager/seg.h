#include<iostream>
#include<iomanip>
#include<string>

#define neicun 1024

using namespace std;

// 段的结构体
struct kongxian {
	unsigned int length;
	unsigned int addr;
	int flag;
	kongxian *next; // 下一段的指针
};

struct Duanbiao
{
	int jincheng;
	unsigned int duannum;
	unsigned int addr;
	unsigned int length;
	int flag; // 内存或外存
	Duanbiao *next;
};

kongxian *Khead; // 空闲链表头指针
kongxian *creatK(); // 创建初始空闲区
Duanbiao *Dhead; // 请求段表头指针
Duanbiao *Dfenpei; // 已分配的链表头
Duanbiao *qingqiuD(Duanbiao *head); // 输入请求的进程及各段
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

