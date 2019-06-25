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
		for (pK; pK != NULL; pK = pK->next) { // 从空闲区表顺序查找
			if (pK->length >= pD->length) {
				p1->flag = 1;
				p1->jincheng = pD->jincheng;
				p1->duannum = pD->duannum;
				p1->addr = pK->addr;
				p1->length = pD->length;
				if (Dfenpei == NULL) {
					Dfenpei = p1;
				}
				else {
					p2->next = p1;
				}
				p2 = p1;
				p1 = new Duanbiao;
				p1->next = NULL;
				if (pK->length == pD->length){
					pK = pK->next;
					break;
				}
				else {
					pK->addr = (p2->addr) + (p2->length);
					pK->length = pK->length - pD->length;
					break;
				}
				continue;
			}
		}
	}
	Dhead = NULL;
	delete p1;
	return Khead;
}

//  回收内存函数
int huishou() {
	ch ='\0';
label2:
	space(5);
	cout << "1.回收整个进程" << endl;
	space(5);
	cout << "2.回收一个段" << endl;
	cin >> ch;
	if (ch == '1') {
		jinchenghuishou();
	}
	else if (ch == '2') {
		// 段回收
		duanhuishou();
	}
	else {
		cout << "输入错误，请重新输入" << endl;
		goto label2;
	}
	return 0;
}

// 进程回收函数
int jinchenghuishou() {
	kongxian *p; // 存放回收的节点
	kongxian *pK; // 
	Duanbiao *pf = Dfenpei;
	p = new kongxian;
	p->next = NULL;

	cout << "输入要回收的进程号" << endl;
	cin >> jinchengming;
	cout << endl;
	for (; pf != NULL; pf = pf->next) {
		if (jinchengming == Dfenpei->jincheng) {
			p->length = Dfenpei->length;
			p->addr = Dfenpei->addr;
			Dfenpei = Dfenpei->next; // 分配指针指向下一个
			pf = Dfenpei;
			if (p->addr < Khead->addr) {
				p->next = Khead;
				Khead = p;
				p = new kongxian;
				continue;
			}
			pK = Khead;
			for (; pK != NULL; pK = pK->next) {
				if (p->addr < pK->addr) {
					p->next = pK;
					pK = p;
					pf = pf->next;
					pf = Dfenpei;
					p = new kongxian;
					continue;
				}
				// continue;
			}
			if (pK == NULL) {
				pK = p;
				p = new kongxian;
				continue;
			}
		}
	}
	Khead = sort(Khead); // 将空闲的进行整理
}

// 段回收
int duanhuishou() {
	int num = 0;
	kongxian *p;
	kongxian *pK; // 
	Duanbiao *pf = Dfenpei;
	p = new kongxian;
	p->length = 0;
	p->next = NULL;

	if (Dfenpei == NULL) {
		cout << "没有已经分配的段存在" << endl;
	}
	cout << "输入要回收的进程号" << endl;
	cin >> jinchengming;
	cout << "输入要回收的段号" << endl;
	cin >> num;
	if (jinchengming == Dfenpei->jincheng&&num == Dfenpei->duannum) {
		p->length = Dfenpei->length;
		p->addr = Dfenpei->addr;
		Dfenpei = Dfenpei->next;
		goto label5;
	}
label5:
	if (true) {

	}
}