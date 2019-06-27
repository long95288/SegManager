// MemManager.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include<iostream>
#include"Segment.h" // 引入自定义头文件
#include<iomanip>
using namespace std;

int main()
{
	init(); // 初始化后
	int select=0;
	do
	{
		cout << "******段式存储管理系统********" << endl;
		cout << endl;
		cout << "    1、新建程序" << endl;
		cout << "    2、将程序载入内存" << endl;
		cout << "    3、根据PID释放内存" << endl;
		cout << "    4、打印信息" << endl;
		cout << "    5、退出" << endl;
		cout << endl;
		cout << ">>你的选项:" ;
		cin >> select;
		int pid = 0;
		int main_length = 0;
		int data_length = 0;
		program *p;
		switch (select)
		{
		case 1:
			cout << "请输入程序的pid,main段长度,data段长度" << endl;
			cout << "pid" <<"   " << "main" << "    " << "data" << endl;
			cin >> pid >> main_length >> data_length;
			// 输入有效
			if (pidValified(pid)) {
				p = createProgram(pid, main_length, data_length);
				p->next = programHead;
				programHead = p;
				p = NULL;
			}
			else {
				cout << "!!!!该pid已经被使用!!!!" << endl;
			}
			break;
		case 2:
			cout << ">>请输入程序的pid:";
			cin >> pid;
			// 调用分配内存函数
			AllocateMemById(pid);
			break;
		case 3:
			cout << ">>请输入要释放程序的pid:";
			cin >> pid;
			RecycleMemByPid(pid);
			break;
		case 4:
			display();
			break;
		case 5:
			break;
		default:
			cout << "没有该选项，重新选择" << endl;
			select = 0;
			break;
		}
	} while (select!=5);

	return 0;
}

// 

void init() {
	// 初始化
	// 1.生成空闲区，空闲长度为1024，开始地址为0
	Idle_section *idle;
	idle = new Idle_section;
	idle->addr = 0;
	idle->length = mem; 
	idle->next = NULL;
	Idle_Head = idle;
	// 段表
	seg_table_head = NULL;
	// 
	programHead = NULL;
}

// pid 是否有效重复
bool pidValified(int pid) {
	program *index;
	bool flag = true;
	index = programHead;
	if (index != NULL) {
		for (; index != NULL; index = index->next) {
			if (pid == index->pid) {
				// 重复了,不能创建
				flag = false;
			}
		}
	}
	return flag;
}

// 新建程序
program *createProgram(int pid, int main_length, int data_length) {
	program *newPro;
	newPro = new program;
	newPro->pid = pid;
	newPro->main_length = main_length;
	newPro->main_seg_num = -1; // 初始化
	newPro->data_seg_num = -1; // 初始化
	newPro->data_length = data_length;
	// 其他段暂时不用
	newPro->sub_length = 0;
	newPro->stack_length = 0;
	newPro->next = NULL;
	return newPro;
}

// 根据pid来分配内存
void AllocateMemById(int pid) {
	program *index;
	index = programHead;
	if (index != NULL) {
		for (; index != NULL; index = index->next) {
			if (index->pid == pid) {
				if (index->main_seg_num == -1) {
					// 分配内存
					Allocate(index);
				}
				else {
					cout << "已经分配过了" << endl;
				}
			}
		}
	}
}

// 为程序分配内存
void Allocate(program *pro) {
	program *tmp;
	tmp = pro;
	// 1、得到程序的main段长度
	int main_length = tmp->main_length;
	int data_length = tmp->data_length;
	// 可以分配
	if (Allocatable(main_length, data_length)) {
		if (main_length > 0) {
			// 大于0才分配
			int main_num = allocateSeg(main_length);
			tmp->main_seg_num = main_num; // 更新
		}
		
		if (data_length > 0) {
			// 大于0才分配
			int data_num = allocateSeg(data_length);
			tmp->data_seg_num = data_num;
		}
		
	}
	else {
		cout << "无法分配" << endl;
	}
}
// 可分配
bool Allocatable(int length1, int length2) {
	bool flag = false;
	bool alloc1 = false; // 分配length1标记
	bool alloc2 = false; // 分配length2 标记
	Idle_section *index;
	index = Idle_Head;
	// 可以分配的条件
	// 1.空闲区大小大于等于length1
	int selected_addr = -1; // 已经选择了的节点
	for (; index != NULL; index = index->next) {
		// 先考虑分配length1
		if (index->length >= length1) {
			// 可以分配length1
			alloc1 = true;
			// 该空闲区减去length1之后还大于等于length2则可以分配length2
			int sub = 0;
			sub = index->length - length1;
			if (sub >= length2 && !alloc2) {
				// 剩下的可以分配给2
				alloc2 = true;
				break; // 退出循环
			}
			else {
				// 记录该结点的地址
				selected_addr = index->addr; // 该地址已经分配给length1了
				break; // 退出循环
			}
		}
	}

	// length2分配问题
	if (!alloc2) { // 在步骤1没有判断出是否可以分配给length2
		index = Idle_Head;
		for (; index != NULL; index = index->next) {
			if (index->length >= length2 && index->addr != selected_addr) {
				// 空闲块大于length2且没有被length1预定
				alloc2 = true;
				break;
			}
		}
	}

	// 只有成功分配了length1 和length2 才能返回true
	if (alloc1 && alloc2) {
		flag = true;
	}
	return flag;
}

// 根据长度分配段表
int allocateSeg(int length) {
	Segment_table_item *item;
	item = new Segment_table_item;
	item->seg_length = length;
	// TODO 基地址的产生，真正的分配内存
	item->base_addr = allocateMem(length);
	item->seg_num = current_seg_num;
	item->next = NULL;
	int renum = -1; // 返回值
	current_seg_num += 1; // 段号加一
	// 将该段加入链表中
	Segment_table_item *p;
	bool flag = false; // 分配的标记
	p = seg_table_head;
	if (p == NULL) {
		// 还没有分配过，分配一个
		seg_table_head = item;
		renum = item->seg_num;
	}
	else { // 插入尾部

		// 寻找值为-1的进行分配
		for (; p != NULL; p = p->next) {
			if (p->seg_length == -1) {
				// 该条没有使用
				renum = p->seg_num;
				p->base_addr = item->base_addr;
				p->seg_length = item->seg_length;
				current_seg_num -= 1;
				delete item; // 删除该节点
				flag = true; // 已经分配好段表
				break;
			}
		}
		// 如果上述都未分配,则在尾部添加一个节点
		p = seg_table_head;
		if (!flag) {
		// 找到尾部
			if (p->next == NULL) {
				p->next = item; // 插入尾部
				renum = item->seg_num;
			}
			else {
				// 定位到尾部
				for (; p->next != NULL; p = p->next) { continue;}
				p->next = item;
				renum = item->seg_num;
			}
		}
	}
	return renum; // 返回段表段号
}

// 根据长度分配内存,会影响到空闲链表
int allocateMem(int length) {
	// 1.遍历空闲链表，找到第一个大小大于等于length的空闲项
	Idle_section *idle,*pre;
	idle = Idle_Head;
	pre = Idle_Head; // 前驱指针
	int base_addr; // 起始地址
	// 获得列表
	for (; (idle->length < length) && idle!=NULL;idle=idle->next){
		pre = idle; // 保留前驱指针
	}
	if (idle == NULL) {
		cout << "无法分配" << endl;
	}
	else {
	// 2.更新空闲链表
		if (idle->length == length) {
			// 空闲块刚好放置，删除该空闲块
			pre->next = idle->next;
			base_addr = idle->length;
			delete idle; // 删除节点
		}
		else {
			// 更新空闲块
			base_addr = idle->addr;
			idle->addr = base_addr + length;
			idle->length = idle->length - length; // 空闲块更小
		}
	}
	return base_addr; // 返回基地址
}

// 根据pid回收内存
void RecycleMemByPid(int pid) {
	// 
	program *index;
	index = programHead;
	for (; index != NULL; index = index->next) {
		if (index->pid == pid) {
			// 找到程序的节点
			// 1、获得Main_seg_num
			int main_seg_num = index->main_seg_num;
			int data_seg_num = index->data_seg_num;
			if (main_seg_num != -1 && data_seg_num != -1) {
				// 调用按段号回收内存
				RecycleMem(main_seg_num); // 按照段号回收内存
				index->main_seg_num = -1; // 恢复成初始化
				RecycleMem(data_seg_num); // 按照段号回收内存
				index->data_seg_num = -1; // 恢复成初始化
			}
		}
	}
}

// 根据段号回收内存
void RecycleMem(int seg_num) {
	// 1.找到对应的段表
	Segment_table_item *item;
	item = seg_table_head;
	// 定位
	for (; item != NULL; item = item->next) {
		if (item->seg_num == seg_num) {
			// 定位成功
			break;
		}
	}
	// 2.将段表长度和基地址置为-1
	int base_addr;
	int seg_length;
	if (item != NULL) {
		base_addr = item->base_addr;
		seg_length = item->seg_length;
		item->base_addr = -1;
		item->seg_length = -1;
// 3.释放出来的内存形成新的空闲区
		Idle_section *idle;
		idle = new Idle_section;
		idle->addr = base_addr;
		idle->length = seg_length;
		// 寻找插入位置
		Idle_section *index;
		index = Idle_Head;
		if (base_addr < index->addr) {
			// 插入头部
			idle->next = index;
			Idle_Head = idle;
		}
		else {
			// 寻找中间值插入
			for (; index != NULL; index = index->next) {
				if (index->next == NULL) {
					index->next = idle;
					// 插入尾部
				}
				else {
					int pre_addr = index->addr + index->length;
					int next_addr = index->next->addr;
					// 处于两者之间的话要插入中间
					// pre_addr <= base_addr <= next_addr
					if (base_addr >= pre_addr && base_addr <= next_addr) {
						// 找见中间值，插入中间中
						idle->next = index->next;
						index->next = idle;
						// 结束循环
						break;
					}
				}
			}
		}

	}
	// 整理空闲区
	sort();
}

// 整理空闲区函数
void sort() {
	// 逻辑，两个相邻的空闲区。
	// 如果第一个空闲区的尾地址和第二个空闲区首地址相等。
	// 合并区
	Idle_section *index; // 索引
	index = Idle_Head;
	while (index != NULL && index->next != NULL) {
		// 区块一尾地址
		int tear_addr = index->addr + index->length;
		// 区块二首地址
		int head_addr = index->next->addr;
		if (tear_addr == head_addr) {
			// 合并区块
			Idle_section *tmp;
			tmp = index->next;
			// 两者空间之和
			index->length = index->length + tmp->length;
			// 指针转向
			index->next = tmp->next; // 跳过被合并的节点
			// 删除节点
			delete tmp;
			// 停留在该节点,跳过index->next模块
			continue;
		}
		// 下一个
		index = index->next;
	}
	index = NULL;// 清空
}

void display() {
	cout << "***********整体信息**************" << endl;
	cout << "1、应用信息" << endl;
	printProgram(); // 
	cout << "2、段表信息" << endl;
	printSegment();
	cout << "3、空闲块信息" << endl;
	printIdle();
	cout << "*********************************" << endl;
}

// 显示应用链表信息
void printProgram() {
	program *t;
	t = programHead;
	if (t == NULL) {
		cout << "没有加载任何应用" << endl;
	}
	else {
		cout << setw(10) << "pid" << setw(20) << "MAIN_length" <<setw(20)<<"Main_seg_num" <<setw(20)<<"Data_length" << setw(20)<<"Data_seg_num"<<endl;;
		for (; t != NULL; t = t->next) {
			cout<<setw(10)<< t->pid <<setw(20)<<t->main_length<<setw(20)<<t->main_seg_num<<setw(20)<<t->data_length <<setw(20)<<t->data_seg_num<< endl;
		}
	}
}

// 显示段表信息
void printSegment() {
	Segment_table_item *item;
	item = seg_table_head; // 
	if (item == NULL) {
		cout << "未分配任何段表" << endl;
	}
	else {
		cout <<setw(10)<< "段号" << setw(10) << "基址" << setw(10) << "段长" << setw(10) << endl;
		for (; item != NULL; item = item->next) {
			cout << item->seg_num << setw(10) << item->base_addr << setw(10) << item->seg_length << setw(10) << endl;
		}
	}
}

// 显示空闲信息
void printIdle() {
	Idle_section *idle;
	idle = Idle_Head;
	cout <<setw(10) << "始址" << setw(10) << "长度" << endl;
	while (idle!=NULL)
	{
		cout << setw(10) << idle->addr << setw(10) << idle->length << endl;
		idle = idle->next;
	}
}