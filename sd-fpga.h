//
// Software-Defined FPGA: logic simulator
//
// last updated on Sep-26-2024 
//
#include <stdio.h>

#define MAX_EVENT 20
#define MAX_TIMEWHEEL 10
#define MAX_FANOUT 10

#define _debug(fmt,p...) 		printf( "%8s:%03d,%8s() ", __FILE__,__LINE__, __FUNCTION__);printf(fmt,##p) 

typedef struct {
    int m_line;
    int m_value;
} Event;

extern Event timeWheel[MAX_TIMEWHEEL][MAX_EVENT];
extern int front[MAX_TIMEWHEEL]; 	// init value -1
extern int rear[MAX_TIMEWHEEL];	// init value -1

void printEvent( Event *p_pEvent);

// Function to check if the queue is full
int isFull( int p_time);

// Function to check if the queue is empty
int isEmpty( int p_time);

// Function to enqueue (insert) an element
void enqueue( int p_time, Event *p_pEvent);

// Function to dequeue (remove) an element
// 0: OK
// -1: NG
int dequeue( int p_time, Event *p_pEvent);
void printEvent( Event *p_pEvent);

// Function to display the queue elements
void display( int p_time);

// 仮に1 line 1pinとする

typedef struct LogicIC {
	int	m_deviceID;
    int (*m_pSignal)( struct LogicIC *p_pLogicIC, int p_time, int p_pinNo, int p_value);
    int m_pinValue[3];
    int m_lineOutput;
} LogicIC;

// return:
// 0	OK
// -1	NG
int signal_AND( struct LogicIC *p_pLogicIC, int p_time, int p_pinNo, int p_value);

// return:
// 0	OK
// -1	NG
int signal_LED( struct LogicIC *p_pLogicIC, int p_time, int p_pinNo, int p_value);

typedef struct {
   	LogicIC *m_pLogicIC;
   	int     m_pin;
} Fanout;

typedef struct {
	int		m_lineNo;
	int		m_connectNo;	// # of connected ICs
	Fanout	m_fanout[ MAX_FANOUT];
} LineInfo;

//
//
void status(void);

//EOF
