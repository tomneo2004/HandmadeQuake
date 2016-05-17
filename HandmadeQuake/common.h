#pragma once

//max args is 50
#define MAX_NUM_ARGVS 50

//largv slot counter or pointer
extern int32 com_argc;

//contain each command and param
extern uint8 *com_argv[MAX_NUM_ARGVS + 1];

void COM_ParseCmdLine(uint8 *lpCmdLine);
int32 COM_CheckParm(uint8 *parm);