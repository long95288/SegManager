#pragma once

// 内存模型
// int Mem[1024];

// 程序
typedef struct Program
{
	int pid; // 程序的唯一的id
	Program *next; // 下一个程序的id

	int main_seg_num; // 
	int main_length; // main段的长度

					 // 子程序段
	int sub_seg_num;
	int sub_length;

	// 数据段
	int data_seg_num;
	int data_length;

	// 堆栈段
	int stack_seg_num; // 段号
	int stack_length;  // 长度
}program;


// 段表项
typedef struct Segment_table_item
{
	int seg_num; // 段号
	int seg_length; // 段长度
	int base_addr; // 基址
	Segment_table_item *next; // 下一个段指针
}Segment_table_item;

// 空闲区块
typedef struct Idle_section
{
	int addr;   // 起始地址
	int length; // 长度
	Idle_section *next; // 下一个
}Idle_section;

// pid -> program
// 用p返回值
int getProgram(Program &p, Program head, int pid) {
	return 0;

}
/*
相关全局变量
*/
// 程序
// program *program_head; // 程序起始头

// 创建新的程序块

int createProgram(
	Program *p,
	int pid,
	int Main_length,
	int Sub_length,
	int Data_length,
	int Stack_length);
// 段表
// Segment_table_item *seg_table_head; // 头指针
// int seg_table_max_num = 0; // 段表当前最大标号

// 空闲区
// Idle_section *idle_head; // 空闲区链表头

/*
相关函数
*/

// 初始化,负责初始化空闲表和段表
void init();

// 是否可分配,输入请求长度，判断是否可分配
bool isAllocatable(int length);

// 输入程序的pid,为该程序分配内存空间
int Allocate(int pid);

// 回收内存，输入参数为段号
int RecoveredMemory(int seg_num);

// 整理空闲区,整理外碎片
void sortIdle();

// 测试
// void test();