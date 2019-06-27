
/*
段式存储的头文件
*/

int mem = 1024; // 存储区为1024
int current_seg_num = 0; // 当前的段号
// 程序段结构体
struct program
{
	int pid; // 程序的唯一的id
	program *next; // 下一个程序的id

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
};

program *programHead; // 程序头

// 段表项
struct Segment_table_item
{
	int seg_num; // 段号
	int seg_length; // 段长度
	int base_addr; // 基址
	Segment_table_item *next; // 下一个段指针
};
Segment_table_item *seg_table_head; // 段表头


struct Idle_section
{
	int addr;   // 起始地址
	int length; // 长度
	Idle_section *next; // 下一个
};

Idle_section *Idle_Head; // 空闲头

void init();

// pid 是否有效，是否重复
bool pidValified(int pid);
// 创建新的程序
program *createProgram(
	int pid, // pid
	int main_length, // main段
	int data_length // 数据段
	);


// 根据pid来分配内存
void AllocateMemById(int pid);
// 为程序分配段表
void Allocate(program *pro);

// 是否可以为length1和length2分配内存
bool Allocatable(int length1, int length2);
// 为长度为length的分配段表
// 返回段号
int allocateSeg(int length);

// 为长度为length的分配内存空间
// 返回基地址
int allocateMem(int length);

// 根据段号回收内存
void RecycleMem(int seg_num);

// 根据pid回收内存
void RecycleMemByPid(int pid);

// 整理空闲区
void sort();

// 显示模块
void display(); // 显示整体信息
void printProgram(); // 显示应用信息
void printIdle();    // 显示空闲信息
void printSegment(); // 显示段表信息