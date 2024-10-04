//
// Software-Defined FPGA: logic simulator
//
// last updated on Sep-26-2024 
//
#include <stdio.h>
#include "sd-fpga.h"

Event timeWheel[MAX_TIMEWHEEL][MAX_EVENT];
int front[MAX_TIMEWHEEL]; 	// init value -1
int rear[MAX_TIMEWHEEL];	// init value -1

// Function to check if the queue is full
int isFull( int p_time) {
    return (rear[p_time] + 1) % MAX_EVENT == front[ p_time];
}

// Function to check if the queue is empty
int isEmpty( int p_time) {
    return front[p_time] < 0;
}

// Function to enqueue (insert) an element
void enqueue( int p_time, Event *p_pEvent) {
	_debug( "p_time=%d, p_pEvent=", p_time);
	printEvent( p_pEvent);
	printf( "\n");
	_debug( "front =%d\n", front[ p_time]);
	_debug( "rear =%d\n", rear[ p_time]);


    if (isFull(p_time)) {
        _debug("Queue overflow\n");
        return;
    }
    if (isEmpty( p_time)) {
        front[ p_time] = 0;
    }
    rear[p_time] = (rear[p_time] + 1) % MAX_EVENT;
    timeWheel[p_time][rear[p_time]] = *p_pEvent;

}

// Function to dequeue (remove) an element
// 0: OK
// -1: NG
int dequeue( int p_time, Event *p_pEvent) {
	_debug( "p_time=%d\n", p_time);
	_debug( "front =%d\n", front[ p_time]);
	_debug( "rear =%d\n", rear[ p_time]);


    if (isEmpty( p_time)) {
        _debug("Queue underflow\n");
        return -1;  // NG
    }
    *p_pEvent = timeWheel[p_time][front[p_time]];
	_debug( "p_pEvent=");
	printEvent( p_pEvent);
	printf( "\n");


    if (front[p_time] == rear[p_time]) {
        front[p_time] = rear[p_time] = -1;
    } else {
        front[p_time] = (front[p_time] + 1) % MAX_EVENT;
    }

    return 0;   // OK
}

void printEvent( Event *p_pEvent)
{
    printf("{ line=%d, value=%d}", p_pEvent->m_line, p_pEvent->m_value);
}

// Function to display the queue elements
void display( int p_time) {
	_debug( "display() p_time=%d\n", p_time);
	_debug( "front =%d\n", front[ p_time]);
	_debug( "rear =%d\n", rear[ p_time]);

    if (isEmpty( p_time)) {
        _debug("Queue is empty\n");
        return;
    }

	int count = 0;
    int i = front[p_time];
    while (i != rear[p_time] && count++ < MAX_EVENT) {
        printf("    %d ", i);
        printEvent( &timeWheel[p_time][i]);
        printf( "\n");
        i = (i + 1) % MAX_EVENT;
    }
    printf("    %d ", i);
    printEvent( &timeWheel[p_time][rear[p_time]]);
    printf( "\n");
}


// return:
// 0	OK
// -1	NG
int signal_AND( struct LogicIC *p_pLogicIC, int p_time, int p_pinNo, int p_value)
{
    _debug( "p_time=%d, p_pinNo=%d, p_value=%d\n", p_time, p_pinNo, p_value);
    _debug( "deviceID=%d\n", p_pLogicIC->m_deviceID);
	int *pPinValue = p_pLogicIC->m_pinValue;
	_debug( "m_pinValue[]={ %d, %d, %d}\n", 
		pPinValue[ 0],
		pPinValue[ 1],
		pPinValue[ 2]);

	p_pLogicIC->m_pinValue[ p_pinNo]= p_value;
    if ( ! p_value || p_pinNo == 2) {
        return 0;   // OK
    }
    int result = p_pLogicIC->m_pinValue[ 0] & p_pLogicIC->m_pinValue[1];
    
    if ( p_pLogicIC->m_pinValue[2] == result) {
        return 0; // OK
    }
    //d p_pLogicIC->m_pinValue[2] = result;
    Event event = { 
        p_pLogicIC->m_lineOutput,
        result
    };
    enqueue( p_time+1, &event);

    return 0;   // OK
}

// return:
// 0	OK
// -1	NG
int signal_LED( struct LogicIC *p_pLogicIC, int p_time, int p_pinNo, int p_value)
{
    _debug( "p_time=%d, p_pinNo=%d, p_value=%d\n", p_time, p_pinNo, p_value);
    _debug( "deviceID=%d\n", p_pLogicIC->m_deviceID);
	int *pPinValue = p_pLogicIC->m_pinValue;
	_debug( "m_pinValue[]={ %d}\n", pPinValue[ 0]);

	if ( p_pinNo != 0) {
    	_debug( "pinNo error: p_pinNo=%d, shuild be 0\n", p_pinNo);
		return -1; // NG
	}
	int currentValue = pPinValue[ 0];
    
    if ( currentValue == p_value) {
        return 0; // OK
    }
    pPinValue[0] = p_value;

	_debug( "deviceID=%d, LED %s\n", p_pLogicIC->m_deviceID,
		p_value?"ON":"OFF");
    return 0;   // OK
}

