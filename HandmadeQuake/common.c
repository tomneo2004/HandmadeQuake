#include "quakedef.h"

//largv slot counter or pointer
int32 com_argc = 1;

//contain each command and param
uint8 *com_argv[MAX_NUM_ARGVS + 1];

void COM_ParseCmdLine(uint8 *lpCmdLine) {

	//make first command slot /0
	com_argv[0] = "";

	//if lpCmdLine is not null and argc increment count less than max args
	while (*lpCmdLine && (com_argc < MAX_NUM_ARGVS + 1)) {

		//move memory address in lpCmdLine to next if value in memeroy adress is less or equal 32 or greater 126
		while (*lpCmdLine && ((*lpCmdLine <= 32 || *lpCmdLine > 126)))
			lpCmdLine++;

		//if lpCmdLine is not null
		if (*lpCmdLine) {

			//put memory address in lpCmdLine into largv array
			com_argv[com_argc] = lpCmdLine;

			//increment count of argc
			com_argc++;

			//if value in memory address in lpCmdLine is not null and greater and less than 32 and 126 in ascii code value(Dec)
			//move memory address in lpCmdLine to next
			while (*lpCmdLine && ((*lpCmdLine > 32) && (*lpCmdLine <= 126)))
				lpCmdLine++;

			if (*lpCmdLine) {

				//make value in this memeory address to /0 
				*lpCmdLine = 0;

				//move lpCmdLine memory address to next
				lpCmdLine++;
			}
		}
	}
}

/*
* find index fo param, return 0 if not found
*/
int32 COM_CheckParm(uint8 *parm) {

	for (int32 i = 1; i < com_argc; i++) {

		if (!Q_strcmp(parm, com_argv[i]))
			return i;
	}

	return 0;
}