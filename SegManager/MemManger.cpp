#include"stdafx.h"
#include<iostream>
// 引入静态库
// #include"../MemLib/TestLib.h"
#include"../MemLib/Mem.h"
using namespace std;

int main(void) {
	init(); // 初始化后
	int select = 0;
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
		cout << ">>你的选项:";
		cin >> select;
		int pid = 0;
		int main_length = 0;
		int data_length = 0;
		program *p;
		switch (select)
		{
		case 1:
			cout << "请输入程序的pid,main段长度,data段长度" << endl;
			cout << "pid" << "   " << "main" << "    " << "data" << endl;
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
	} while (select != 5);
	return 0;

}