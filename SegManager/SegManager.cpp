// SegManager.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "seg.h"
#include <iostream>

using namespace std;

int main()
{
	cout << "\t****************************************" << endl;
	cout << "\t*** 段式存储的管理分配与回收" << endl;
	cout << "********************************************" << endl;
	
	Dfenpei = NULL; // 已分配链表头指针
	Khead = NULL; // 空闲链表头指针
	Khead = creatK(); // 创建初始空闲区
	Dhead = NULL;
	do {
		cout << endl << "'请选择您要进行的操作" << endl;
		space(5);
		cout << "1.分配内存空间" << endl;
		space(5);
		cout << "2.回收存储空间" << endl;
		space(5);
		cout << "3.显示内存资源" << endl;
		space(5);
		cout << "4.退出" << endl;
		// 输入选择
		cin >> select;
		switch (select)
		{
		case 1:
			Dhead = qingqiuD(Dhead); // 创建申请链表
			Khead = zuixian(Dhead); // 为申请链表分配空间
			break;
		case 2:
			huishou();
			break;
		case 3:
			Display();
			break;
		case 4:
			cout << "退出系统" << endl;
			break;
		default:
			cout << "输入错误，请重新选择" << endl;
			break;
		}
	} while (select != 4);

	int i = 0;
	cin >> i;
    return 0;
	
}

/*
函数实现
*/

kongxian *creatK() {
	kongxian *p = new kongxian;
	p->length = neicun;
	p->addr = 0;
	p->flag = 0;
	p->next = NULL;
	return p;
}

Duanbiao* qingqiuD(Duanbiao* head) {
	Duanbiao *p1, *p2;
	p1 = p2 = new Duanbiao;
	cout << "请输入请求资源进程号" << endl;
	cin >> jinchengming;
	cout << "请输入段号和长度" << endl;
	cin >> p1->duannum >> p1->length;
	p1->next = NULL;
	if (head != NULL) {
		p2 = head;
		while (p2->next!=NULL)
		{
			p2 = p2->next; // 指向已分配表的最后一个节点
		}
	}
	while (p1->duannum != -1)
	{
		p1->jincheng = jinchengming;
		p1->flag = 0;
		if (head == NULL)
			head = p1;
		else
		{
			p2->next = p1;
		}
		p2 = p1;
		p1 = new Duanbiao;
		p1->next = NULL;
		cin >> p1->duannum >> p1->length;
	}
	delete p1;
	return head;
}

kongxian *zuixian(Duanbiao* head) {
	kongxian *pK; // 空闲链表头指针
	Duanbiao *p1, *p2; // 已分配链表节点
	Duanbiao *pD = head;// 请求段表头指针
	Duanbiao *pf = Dfenpei;
	p1 = p2 = new Duanbiao;
	p1->next = NULL;
	if (Dfenpei != NULL) {
		p2 = Dfenpei;
		while (p2->next!=NULL)
		{
			p2 = p2->next;
		}
	}
	// 
	for (pD; pD != NULL; pD = pD->next) {
		pK = Khead;
		for (pK; pK != NULL; pK = pK->next) {

		}
	}

}