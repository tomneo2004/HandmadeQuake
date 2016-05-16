#include <windows.h>
#include <stdint.h>

typedef uint8_t uint8t;
typedef int32_t int32t;
typedef uint32_t uint32t;

//max args is 50
#define MAX_NUM_ARGVS 3

//largv slot counter or pointer
int argc = 1;

//contain each command and param
uint8t *largv[MAX_NUM_ARGVS+1];

int32t Q_strcmp(uint8t *s1, uint8t *s2) {


	while (*s1 == *s2){

		if (!*s1)
			return 0;

		++s1;
		++s2;
	}

	return ((*s1 > *s2)? -1:1);
}

int32t Q_atoi(uint8t *str) {

	int32t sign = 1;
	int32t val = 0;
	uint8t c;

	//sign
	if (*str == '-') {

		sign = -1;
		str++;
	}

	//hexdecimal
	if (str[0] == '0' && ((str[1] == 'x') || (str[1] == 'X'))) {

		str += 2;

		while (1) {

			c = *str;
			str++;

			if (c >= '0' && c <= '9')
				val = val * 16 + c - '0';
			else if (c >= 'a' && c <= 'f')
				val = val * 16 + c - 'a' + 10;
			else if (c >= 'A' && c <= 'F')
				val = val * 16 + c - 'A' + 10;
			else
				return val * sign;
		}

	}

	//decimal
	while (1){

		c = *str;

		if (c < '0' || c > '9')
			return sign * val;

		val = val * 10 + c - '0';
	}
}

/*
* find index fo param, return 0 if not found
*/
int32t COM_CheckParm(uint8t *parm) {

	for (int32t i = 1; i < argc; i++) {

		if (!Q_strcmp(parm, largv[i]))
			return i;
	}

	return 0;
}

int32t CALLBACK WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int32t hCmdShow) {

	//make first command slot /0
	largv[0] = "";

	//if lpCmdLine is not null and argc increment count less than max args
	while (*lpCmdLine && (argc < MAX_NUM_ARGVS+1)){

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


	int32t test = COM_CheckParm("-setalpha");

	//string to int atoi
	int32t value = Q_atoi((largv[test+1]));

	return 0;
}