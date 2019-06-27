
/*
��ʽ�洢��ͷ�ļ�
*/

int mem = 1024; // �洢��Ϊ1024
int current_seg_num = 0; // ��ǰ�Ķκ�
// ����νṹ��
struct program
{
	int pid; // �����Ψһ��id
	program *next; // ��һ�������id

	int main_seg_num; // 
	int main_length; // main�εĳ���

	// �ӳ����
	int sub_seg_num;
	int sub_length;
	
	// ���ݶ�
	int data_seg_num;
	int data_length;

	// ��ջ��
	int stack_seg_num; // �κ�
	int stack_length;  // ����
};

program *programHead; // ����ͷ

// �α���
struct Segment_table_item
{
	int seg_num; // �κ�
	int seg_length; // �γ���
	int base_addr; // ��ַ
	Segment_table_item *next; // ��һ����ָ��
};
Segment_table_item *seg_table_head; // �α�ͷ


struct Idle_section
{
	int addr;   // ��ʼ��ַ
	int length; // ����
	Idle_section *next; // ��һ��
};

Idle_section *Idle_Head; // ����ͷ

void init();

// pid �Ƿ���Ч���Ƿ��ظ�
bool pidValified(int pid);
// �����µĳ���
program *createProgram(
	int pid, // pid
	int main_length, // main��
	int data_length // ���ݶ�
	);


// ����pid�������ڴ�
void AllocateMemById(int pid);
// Ϊ�������α�
void Allocate(program *pro);

// �Ƿ����Ϊlength1��length2�����ڴ�
bool Allocatable(int length1, int length2);
// Ϊ����Ϊlength�ķ���α�
// ���ضκ�
int allocateSeg(int length);

// Ϊ����Ϊlength�ķ����ڴ�ռ�
// ���ػ���ַ
int allocateMem(int length);

// ���ݶκŻ����ڴ�
void RecycleMem(int seg_num);

// ����pid�����ڴ�
void RecycleMemByPid(int pid);

// ���������
void sort();

// ��ʾģ��
void display(); // ��ʾ������Ϣ
void printProgram(); // ��ʾӦ����Ϣ
void printIdle();    // ��ʾ������Ϣ
void printSegment(); // ��ʾ�α���Ϣ