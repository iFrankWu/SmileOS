#define AR_TSS						    0x0089
#define AR_LDT							0x0082

#define DPL_0							0x00
#define DPL_3							0x60

#define RPL_0							0x00
#define RPL_3							0x03

#define TOTAL_PROCESS_NUM				1000
#define USER_PROCESS_NUM 				TOTAL_PROCESS_NUM-1
#define PROCESS_TABLE_ADDRESS			0x30000

#define STATUS_PROCESS_INIT 			0
#define STATUS_PROCESS_USING 			1
#define STATUS_PROCESS_RUNNING 			2

#define KERNEL_PROCESS_GDT 				1024
#define START_PROCESS_GDT 				KERNEL_PROCESS_GDT+1

#define MAX_LDT_NUM						4

#define PROCESS_NAME_LENGTH				32

typedef struct Tss
{
	int backlink, esp0, ss0, esp1, ss1, esp2, ss2, cr3;

	int eip, eflags, eax, ecx, edx, ebx, esp, ebp, esi, edi;

	int es, cs, ss, ds, fs, gs;

	int ldtr, iomap;
	
} Tss;

typedef struct Ldt
{
	LocalDescriptor descriptor[MAX_LDT_NUM];
	
} Ldt;

typedef struct Process
{
	Tss tss;

	Ldt ldt;

	short tssSelector;

	short ldtSelector;

	short status;

	int priority;

	Sheet *mainWindow;

	char name[PROCESS_NAME_LENGTH];

} Process;

typedef struct ProcessManager
{
	int running;

	int current;

	int currentPriority;

	Process coreProcess;

	Process *processList[TOTAL_PROCESS_NUM];

	Process processArray[USER_PROCESS_NUM];

} ProcessManager;

ProcessManager *processManager;

void initTssDescriptor(Tss *tss, int eip, int esp);

void initProcessManagement();

void prepareKernelProcess();

void registerKernelProcess();

Process *requestProcess();

Process *getCurrentProcess();

Process *addProcess(Process *process);

Process *removeProcess(Process *process);

Process *startRunProcess(Process *process, int priority);

void startSleepProcess(Process *process);

void startSwitchProcess();
