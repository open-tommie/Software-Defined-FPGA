//
// Software-Defined FPGA: logic simulator
//
// last updated on Oct-01-2024 
//
#include <stdio.h>

//#define MAX_EVENT 20
//#define MAX_TIMEWHEEL 10
#include "sd-fpga.h"

static LogicIC logicIC[] = {
	//v--- deviceID
	//   v--- pointer of doEvent
	//               v--- pin value
	//                        v--- line output
    { 0, signal_AND, {0,0,0}, 2 },    // AND0
    { 1, signal_AND, {0,0,0}, 4 },    // AND1
    { 2, signal_LED, {0,0,0}, -1},    // LED0
};


// line connect:
//
// line0--->AND0.0
// line1--->AND0.1 AND0.2 --->line2--->AND1.0
// line3------------------------------>AND1.1 AND1.2 --->line4--->LED0.0
//
//
//
//
static LineInfo lineInfo[] = {
	//v--- lineNo
	//   # of ICs
	//       v--- &LogicIC
	//                     v--- pin
    { 0, 1, 
		{
			{ &logicIC[0], 0},   // 0
		}
	},
    { 1, 1, 
		{
			{ &logicIC[0], 1},   // 1
		}
	},
    { 2, 2, 
		{
			{ &logicIC[0], 2},   
			{ &logicIC[1], 0},  
		}
	},
    { 3, 1, 
		{
			{ &logicIC[1], 1},   // 3
		}
	},
    { 4, 2, 
		{
			{ &logicIC[1], 2},   // 
			{ &logicIC[2], 0},   // LED
		}
	}
};

//
//
void status(void)
{
	_debug( "LogicIC status\n");
	_debug( "id, {value}\n");
	for ( int i = 0; i < sizeof(logicIC)/sizeof(LogicIC); i++) {
			LogicIC *pIC = &logicIC[i];
			_debug( "%d, {%d, %d, %d}\n", pIC->m_deviceID,
				pIC->m_pinValue[0],
				pIC->m_pinValue[1],
				pIC->m_pinValue[2]);
			// for PlantUML sequence diagrams
			for ( int pin = 0; pin < 3; pin++) {
				_debug( "UML:ic%02d.pin%02d is %s\n", pIC->m_deviceID,
					pin,
					pIC->m_pinValue[ pin] ? "high": "low");
			}
	}
}

int main() {
	_debug( "main()\n");

	// init timeWheel[][], front[], rear[]
	for ( int i = 0; i < MAX_TIMEWHEEL; i++) {
		front[ i] = -1;
		rear[ i] = -1;
	}
	// init logicIC
    for ( int i = 0; i < sizeof(logicIC)/sizeof(LogicIC); i++) {
        for ( int pin = 0; pin < sizeof(logicIC[0].m_pinValue)/sizeof(int); pin++) {
            logicIC[i].m_pinValue[ pin] = 0;
        }
    }
	// for PlantUML sequence diagrams
	printf( "UML:@%d\n", 0);
	status();

    Event event[] = {
        { 0, 1},
        { 1, 1},
        { 3, 1}
    };
    for ( int i = 0; i < sizeof(event)/sizeof(Event); i++) {
        enqueue(0, &event[i]);
    }
    display(0);

//	printf( "&logicIC[0]=%p\n", &logicIC[0]);
//	printf( "lineInfo[0].m_pLogicIC=%p\n", lineInfo[0].m_pLogicIC);

//
//    LogicIC *pLogicIC = lineInfo[ 0].m_pLogicIC;
//    Event event0;
//    (*(pLogicIC->m_pDoEvent))( &logicIC[0], 0, &event0);

	_debug( "---start event process\n");

    for ( int time = 0; time < 5; time++){
		_debug( "--- for: time=%d\n", time);
        display(time);
        while ( ! isEmpty( time)) {
			//_debug( "while: time=%d\n", time);

            Event event;
            dequeue(time, &event);
			//printf( "event=");
			//printEvent( &event);
			//printf( "\n");

            int line = event.m_line;
			int value = event.m_value;
            for ( int fanout = 0; fanout < lineInfo[ line].m_connectNo; fanout++) {
            	Fanout *pFanout = &lineInfo[ line].m_fanout[ fanout];
            	LogicIC *pLogicIC = pFanout->m_pLogicIC;
				int pin = pFanout->m_pin;
            	(*pLogicIC->m_pSignal)( pLogicIC, time, pin, value);
			}
        }
		printf( "\n");
		// for PlantUML sequence diagrams
		printf( "UML:@%d\n", time+1);
		status();
    }
	_debug( "---end event process\n");

    display(2);

    return 0;
}
