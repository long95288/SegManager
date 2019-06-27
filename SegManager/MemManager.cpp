// MemManager.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include<iostream>
#include"Segment.h" // �����Զ���ͷ�ļ�
#include<iomanip>
using namespace std;

int main()
{
	init(); // ��ʼ����
	int select=0;
	do
	{
		cout << "******��ʽ�洢����ϵͳ********" << endl;
		cout << endl;
		cout << "    1���½�����" << endl;
		cout << "    2�������������ڴ�" << endl;
		cout << "    3������PID�ͷ��ڴ�" << endl;
		cout << "    4����ӡ��Ϣ" << endl;
		cout << "    5���˳�" << endl;
		cout << endl;
		cout << ">>���ѡ��:" ;
		cin >> select;
		int pid = 0;
		int main_length = 0;
		int data_length = 0;
		program *p;
		switch (select)
		{
		case 1:
			cout << "����������pid,main�γ���,data�γ���" << endl;
			cout << "pid" <<"   " << "main" << "    " << "data" << endl;
			cin >> pid >> main_length >> data_length;
			// ������Ч
			if (pidValified(pid)) {
				p = createProgram(pid, main_length, data_length);
				p->next = programHead;
				programHead = p;
				p = NULL;
			}
			else {
				cout << "!!!!��pid�Ѿ���ʹ��!!!!" << endl;
			}
			break;
		case 2:
			cout << ">>����������pid:";
			cin >> pid;
			// ���÷����ڴ溯��
			AllocateMemById(pid);
			break;
		case 3:
			cout << ">>������Ҫ�ͷų����pid:";
			cin >> pid;
			RecycleMemByPid(pid);
			break;
		case 4:
			display();
			break;
		case 5:
			break;
		default:
			cout << "û�и�ѡ�����ѡ��" << endl;
			select = 0;
			break;
		}
	} while (select!=5);

	return 0;
}

// 

void init() {
	// ��ʼ��
	// 1.���ɿ����������г���Ϊ1024����ʼ��ַΪ0
	Idle_section *idle;
	idle = new Idle_section;
	idle->addr = 0;
	idle->length = mem; 
	idle->next = NULL;
	Idle_Head = idle;
	// �α�
	seg_table_head = NULL;
	// 
	programHead = NULL;
}

// pid �Ƿ���Ч�ظ�
bool pidValified(int pid) {
	program *index;
	bool flag = true;
	index = programHead;
	if (index != NULL) {
		for (; index != NULL; index = index->next) {
			if (pid == index->pid) {
				// �ظ���,���ܴ���
				flag = false;
			}
		}
	}
	return flag;
}

// �½�����
program *createProgram(int pid, int main_length, int data_length) {
	program *newPro;
	newPro = new program;
	newPro->pid = pid;
	newPro->main_length = main_length;
	newPro->main_seg_num = -1; // ��ʼ��
	newPro->data_seg_num = -1; // ��ʼ��
	newPro->data_length = data_length;
	// ��������ʱ����
	newPro->sub_length = 0;
	newPro->stack_length = 0;
	newPro->next = NULL;
	return newPro;
}

// ����pid�������ڴ�
void AllocateMemById(int pid) {
	program *index;
	index = programHead;
	if (index != NULL) {
		for (; index != NULL; index = index->next) {
			if (index->pid == pid) {
				if (index->main_seg_num == -1) {
					// �����ڴ�
					Allocate(index);
				}
				else {
					cout << "�Ѿ��������" << endl;
				}
			}
		}
	}
}

// Ϊ��������ڴ�
void Allocate(program *pro) {
	program *tmp;
	tmp = pro;
	// 1���õ������main�γ���
	int main_length = tmp->main_length;
	int data_length = tmp->data_length;
	// ���Է���
	if (Allocatable(main_length, data_length)) {
		if (main_length > 0) {
			// ����0�ŷ���
			int main_num = allocateSeg(main_length);
			tmp->main_seg_num = main_num; // ����
		}
		
		if (data_length > 0) {
			// ����0�ŷ���
			int data_num = allocateSeg(data_length);
			tmp->data_seg_num = data_num;
		}
		
	}
	else {
		cout << "�޷�����" << endl;
	}
}
// �ɷ���
bool Allocatable(int length1, int length2) {
	bool flag = false;
	bool alloc1 = false; // ����length1���
	bool alloc2 = false; // ����length2 ���
	Idle_section *index;
	index = Idle_Head;
	// ���Է��������
	// 1.��������С���ڵ���length1
	int selected_addr = -1; // �Ѿ�ѡ���˵Ľڵ�
	for (; index != NULL; index = index->next) {
		// �ȿ��Ƿ���length1
		if (index->length >= length1) {
			// ���Է���length1
			alloc1 = true;
			// �ÿ�������ȥlength1֮�󻹴��ڵ���length2����Է���length2
			int sub = 0;
			sub = index->length - length1;
			if (sub >= length2 && !alloc2) {
				// ʣ�µĿ��Է����2
				alloc2 = true;
				break; // �˳�ѭ��
			}
			else {
				// ��¼�ý��ĵ�ַ
				selected_addr = index->addr; // �õ�ַ�Ѿ������length1��
				break; // �˳�ѭ��
			}
		}
	}

	// length2��������
	if (!alloc2) { // �ڲ���1û���жϳ��Ƿ���Է����length2
		index = Idle_Head;
		for (; index != NULL; index = index->next) {
			if (index->length >= length2 && index->addr != selected_addr) {
				// ���п����length2��û�б�length1Ԥ��
				alloc2 = true;
				break;
			}
		}
	}

	// ֻ�гɹ�������length1 ��length2 ���ܷ���true
	if (alloc1 && alloc2) {
		flag = true;
	}
	return flag;
}

// ���ݳ��ȷ���α�
int allocateSeg(int length) {
	Segment_table_item *item;
	item = new Segment_table_item;
	item->seg_length = length;
	// TODO ����ַ�Ĳ����������ķ����ڴ�
	item->base_addr = allocateMem(length);
	item->seg_num = current_seg_num;
	item->next = NULL;
	int renum = -1; // ����ֵ
	current_seg_num += 1; // �κż�һ
	// ���öμ���������
	Segment_table_item *p;
	bool flag = false; // ����ı��
	p = seg_table_head;
	if (p == NULL) {
		// ��û�з����������һ��
		seg_table_head = item;
		renum = item->seg_num;
	}
	else { // ����β��

		// Ѱ��ֵΪ-1�Ľ��з���
		for (; p != NULL; p = p->next) {
			if (p->seg_length == -1) {
				// ����û��ʹ��
				renum = p->seg_num;
				p->base_addr = item->base_addr;
				p->seg_length = item->seg_length;
				current_seg_num -= 1;
				delete item; // ɾ���ýڵ�
				flag = true; // �Ѿ�����öα�
				break;
			}
		}
		// ���������δ����,����β�����һ���ڵ�
		p = seg_table_head;
		if (!flag) {
		// �ҵ�β��
			if (p->next == NULL) {
				p->next = item; // ����β��
				renum = item->seg_num;
			}
			else {
				// ��λ��β��
				for (; p->next != NULL; p = p->next) { continue;}
				p->next = item;
				renum = item->seg_num;
			}
		}
	}
	return renum; // ���ضα�κ�
}

// ���ݳ��ȷ����ڴ�,��Ӱ�쵽��������
int allocateMem(int length) {
	// 1.�������������ҵ���һ����С���ڵ���length�Ŀ�����
	Idle_section *idle,*pre;
	idle = Idle_Head;
	pre = Idle_Head; // ǰ��ָ��
	int base_addr; // ��ʼ��ַ
	// ����б�
	for (; (idle->length < length) && idle!=NULL;idle=idle->next){
		pre = idle; // ����ǰ��ָ��
	}
	if (idle == NULL) {
		cout << "�޷�����" << endl;
	}
	else {
	// 2.���¿�������
		if (idle->length == length) {
			// ���п�պ÷��ã�ɾ���ÿ��п�
			pre->next = idle->next;
			base_addr = idle->length;
			delete idle; // ɾ���ڵ�
		}
		else {
			// ���¿��п�
			base_addr = idle->addr;
			idle->addr = base_addr + length;
			idle->length = idle->length - length; // ���п��С
		}
	}
	return base_addr; // ���ػ���ַ
}

// ����pid�����ڴ�
void RecycleMemByPid(int pid) {
	// 
	program *index;
	index = programHead;
	for (; index != NULL; index = index->next) {
		if (index->pid == pid) {
			// �ҵ�����Ľڵ�
			// 1�����Main_seg_num
			int main_seg_num = index->main_seg_num;
			int data_seg_num = index->data_seg_num;
			if (main_seg_num != -1 && data_seg_num != -1) {
				// ���ð��κŻ����ڴ�
				RecycleMem(main_seg_num); // ���նκŻ����ڴ�
				index->main_seg_num = -1; // �ָ��ɳ�ʼ��
				RecycleMem(data_seg_num); // ���նκŻ����ڴ�
				index->data_seg_num = -1; // �ָ��ɳ�ʼ��
			}
		}
	}
}

// ���ݶκŻ����ڴ�
void RecycleMem(int seg_num) {
	// 1.�ҵ���Ӧ�Ķα�
	Segment_table_item *item;
	item = seg_table_head;
	// ��λ
	for (; item != NULL; item = item->next) {
		if (item->seg_num == seg_num) {
			// ��λ�ɹ�
			break;
		}
	}
	// 2.���α��Ⱥͻ���ַ��Ϊ-1
	int base_addr;
	int seg_length;
	if (item != NULL) {
		base_addr = item->base_addr;
		seg_length = item->seg_length;
		item->base_addr = -1;
		item->seg_length = -1;
// 3.�ͷų������ڴ��γ��µĿ�����
		Idle_section *idle;
		idle = new Idle_section;
		idle->addr = base_addr;
		idle->length = seg_length;
		// Ѱ�Ҳ���λ��
		Idle_section *index;
		index = Idle_Head;
		if (base_addr < index->addr) {
			// ����ͷ��
			idle->next = index;
			Idle_Head = idle;
		}
		else {
			// Ѱ���м�ֵ����
			for (; index != NULL; index = index->next) {
				if (index->next == NULL) {
					index->next = idle;
					// ����β��
				}
				else {
					int pre_addr = index->addr + index->length;
					int next_addr = index->next->addr;
					// ��������֮��Ļ�Ҫ�����м�
					// pre_addr <= base_addr <= next_addr
					if (base_addr >= pre_addr && base_addr <= next_addr) {
						// �Ҽ��м�ֵ�������м���
						idle->next = index->next;
						index->next = idle;
						// ����ѭ��
						break;
					}
				}
			}
		}

	}
	// ���������
	sort();
}

// �������������
void sort() {
	// �߼����������ڵĿ�������
	// �����һ����������β��ַ�͵ڶ����������׵�ַ��ȡ�
	// �ϲ���
	Idle_section *index; // ����
	index = Idle_Head;
	while (index != NULL && index->next != NULL) {
		// ����һβ��ַ
		int tear_addr = index->addr + index->length;
		// ������׵�ַ
		int head_addr = index->next->addr;
		if (tear_addr == head_addr) {
			// �ϲ�����
			Idle_section *tmp;
			tmp = index->next;
			// ���߿ռ�֮��
			index->length = index->length + tmp->length;
			// ָ��ת��
			index->next = tmp->next; // �������ϲ��Ľڵ�
			// ɾ���ڵ�
			delete tmp;
			// ͣ���ڸýڵ�,����index->nextģ��
			continue;
		}
		// ��һ��
		index = index->next;
	}
	index = NULL;// ���
}

void display() {
	cout << "***********������Ϣ**************" << endl;
	cout << "1��Ӧ����Ϣ" << endl;
	printProgram(); // 
	cout << "2���α���Ϣ" << endl;
	printSegment();
	cout << "3�����п���Ϣ" << endl;
	printIdle();
	cout << "*********************************" << endl;
}

// ��ʾӦ��������Ϣ
void printProgram() {
	program *t;
	t = programHead;
	if (t == NULL) {
		cout << "û�м����κ�Ӧ��" << endl;
	}
	else {
		cout << setw(10) << "pid" << setw(20) << "MAIN_length" <<setw(20)<<"Main_seg_num" <<setw(20)<<"Data_length" << setw(20)<<"Data_seg_num"<<endl;;
		for (; t != NULL; t = t->next) {
			cout<<setw(10)<< t->pid <<setw(20)<<t->main_length<<setw(20)<<t->main_seg_num<<setw(20)<<t->data_length <<setw(20)<<t->data_seg_num<< endl;
		}
	}
}

// ��ʾ�α���Ϣ
void printSegment() {
	Segment_table_item *item;
	item = seg_table_head; // 
	if (item == NULL) {
		cout << "δ�����κζα�" << endl;
	}
	else {
		cout <<setw(10)<< "�κ�" << setw(10) << "��ַ" << setw(10) << "�γ�" << setw(10) << endl;
		for (; item != NULL; item = item->next) {
			cout << item->seg_num << setw(10) << item->base_addr << setw(10) << item->seg_length << setw(10) << endl;
		}
	}
}

// ��ʾ������Ϣ
void printIdle() {
	Idle_section *idle;
	idle = Idle_Head;
	cout <<setw(10) << "ʼַ" << setw(10) << "����" << endl;
	while (idle!=NULL)
	{
		cout << setw(10) << idle->addr << setw(10) << idle->length << endl;
		idle = idle->next;
	}
}