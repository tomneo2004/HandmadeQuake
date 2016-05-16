#include <windows.h>

//max args is 50
#define MAX_NUM_ARGVS 50

//largv slot counter or pointer
int argc = 1;

//contain each command and param
char *largv[MAX_NUM_ARGVS];

/*
* find index fo param, return 0 if not found
*/
int COM_CheckParm(char *parm) {

	for (int i = 1; i < argc; i++) {

		if (!strcmp(parm, largv[i]))
			return i;
	}

	return 0;
}

int CALLBACK WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int hCmdShow) {

	//make first command slot /0
	largv[0] = "";

	//if lpCmdLine is not null and argc increment count less than max args
	while (*lpCmdLine && (argc < MAX_NUM_ARGVS)){

		//move memory address in lpCmdLine to next if value in memeroy adress is less or equal 32 or greater 126
		while (*lpCmdLine && ((*lpCmdLine <= 32 || *lpCmdLine > 126)))
			lpCmdLine++;

		//if lpCmdLine is not null
		if (*lpCmdLine) {

			//put memory address in lpCmdLine into largv array
			largv[argc] = lpCmdLine;

			//increment count of argc
			argc++;

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

	largv[argc] = "";

	int test = COM_CheckParm("-setalpha");

	return 0;
}