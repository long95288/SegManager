// SegManager.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include "seg.h"
#include <iostream>

using namespace std;

int main()
{
	cout << "\t****************************************" << endl;
	cout << "\t*** ��ʽ�洢�Ĺ�����������" << endl;
	cout << "********************************************" << endl;
	
	Dfenpei = NULL; // �ѷ�������ͷָ��
	Khead = NULL; // ��������ͷָ��
	Khead = creatK(); // ������ʼ������
	Dhead = NULL;
	do {
		cout << endl << "'��ѡ����Ҫ���еĲ���" << endl;
		space(5);
		cout << "1.�����ڴ�ռ�" << endl;
		space(5);
		cout << "2.���մ洢�ռ�" << endl;
		space(5);
		cout << "3.��ʾ�ڴ���Դ" << endl;
		space(5);
		cout << "4.�˳�" << endl;
		// ����ѡ��
		cin >> select;
		switch (select)
		{
		case 1:
			Dhead = qingqiuD(Dhead); // ������������
			Khead = zuixian(Dhead); // Ϊ�����������ռ�
			break;
		case 2:
			huishou();
			break;
		case 3:
			Display();
			break;
		case 4:
			cout << "�˳�ϵͳ" << endl;
			break;
		default:
			cout << "�������������ѡ��" << endl;
			break;
		}
	} while (select != 4);

	int i = 0;
	cin >> i;
    return 0;
	
}

/*
����ʵ��
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
	cout << "������������Դ���̺�" << endl;
	cin >> jinchengming;
	cout << "������κźͳ���" << endl;
	cin >> p1->duannum >> p1->length;
	p1->next = NULL;
	if (head != NULL) {
		p2 = head;
		while (p2->next!=NULL)
		{
			p2 = p2->next; // ָ���ѷ��������һ���ڵ�
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
	kongxian *pK; // ��������ͷָ��
	Duanbiao *p1, *p2; // �ѷ�������ڵ�
	Duanbiao *pD = head;// ����α�ͷָ��
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