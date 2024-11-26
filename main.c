/*
	A simple Currency Converter from doller value written in Japanese language to yen value.
	This is a small program to help my own work.
*/
#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "tk_string.h" // my own snipets for string related functions. This is for string replacement.

#define MAX_TEXT_LEN 100

typedef enum{
    ERROR_INVALID_UNIT, // Unknown unit specifier passed
	ERROR_INVALID_CR, 	// invalid currency rate
} error_type;

enum{
    UNIT_N = 0,
	UNIT_M,
    UNIT_O,
    UNIT_C,
};

/* Function prototypes */
void show_error(error_type error);
void ask_and_set_currency_rate(float *rate);

int main(char argc, char** argv){
    float currency_rate = 0.0;
    
    ask_and_set_currency_rate(&currency_rate);
    
    if (currency_rate != 0.0){
        unsigned int dollar;
		unsigned int yen;
            
		char input[MAX_TEXT_LEN] = {0}; 	// User input string
		char output[MAX_TEXT_LEN] = {0}; 	// Output string
		char *temp; 						// The cooked string bt tkstr lib
		int unit; 							// The unit that user specify
		int chou, oku, man, nashi; 			// These are Japanese number unit.
		
		for (;;){
			chou = 0;
			oku = 0;
			man = 0;
			nashi = 0;
            
			/*Shows "how to" on screen */
            system("cls");
			printf("\n");
			printf("==== Currency Converter v1.0�@==== \n");
			printf("\n");
            printf("�ݒ背�[�g = %.2f�@�ł��B\n", currency_rate);
			printf("\n");
            printf("�h���\�L�̋��z����͂��Ă��������B\n");
			printf("\n");
			printf("��F�@1���h�� -> '1c' | 230���h���@-> '230o' | 3000���h�� -> '3000m | 1500�h�� -> '1500n'\n");
			printf("\n");
            printf("�A�v���P�[�V�������I������ɂ́uQ�v����͂��Ă��������B\n");
			printf("\n");
			printf("�ݒ背�[�g���I������ɂ́uR�v����͂��Ă��������B\n");
			printf("\n");
			
			/* Shows a last output on screen if any */
			if (output[0] != 0){
				printf("%s\n", output);
				printf("\n");               
				printf("��L���N���b�v�{�[�h�ɃR�s�[���܂����B\n");
                printf("\n");
				memset(output, 0, sizeof(output));
			}
			
            printf(">: ");
            scanf_s("%s", input, MAX_TEXT_LEN);
			
            if (strcmp(input, "Q") == 0) // note: strcmp returns 0 when matches.
                break;
			else if (strcmp(input, "R") == 0){
				ask_and_set_currency_rate(&currency_rate);
				continue;
			}
            
			/* Replace the character that shows a unit to blank, and set an appropriate unit.*/
            if (strchr(input, (int)'c') != 0){
                unit = UNIT_C;
                temp = tkstr_replace(input, "c", "");
            }
            else if (strchr(input, (int)'o') != 0){
                unit = UNIT_O;
                temp = tkstr_replace(input, "o", "");
            }
            else if (strchr(input, (int)'m') != 0){
                unit = UNIT_M;
                temp = tkstr_replace(input, "m", "");
            }
			else if (strchr(input, (int)'n') != 0){
				unit = UNIT_N;
                temp = tkstr_replace(input, "n", "");
			}
            else{
                show_error(ERROR_INVALID_UNIT);
                continue;
            }
            
            dollar = atoi(temp);
			free(temp); // free memory address that passed from tkstr library.
            
            float quotient, remainder;
			float n; // This contains the value which will be separated into quotient & remaidner later
			int count = unit;
			
			yen = dollar * currency_rate;
			n = yen / 10000.0;
            
			do{
				/* Separate n into quotient & remainder*/
				quotient = floor((double)n);
                remainder = n - quotient;
                
				switch (count){
					case UNIT_N:{
						nashi = (int)(remainder * 10000.0f);
					}break;
					
					case UNIT_M:{
                        man = (int)(remainder * 10000.0f);
                    }break;
                    
                    case UNIT_O:{
                        oku = (int)(remainder * 10000.0f);
                    }break;
                    
                    case UNIT_C:{
                        chou = (int)(remainder * 10000.0f);
                    }break;
                }
				
				n = n / 10000.0f;
                count++;
				
            }while(quotient > 9999);
            
			/* After setting remainders to appropriate units, 
			set remained quotient to the biggest unit.*/
			switch (count){
                    case UNIT_M:{
						man = (int)quotient;
					}break;
					
					case UNIT_O:{
                        oku = (int)quotient;
                    }break;
                    
                    case UNIT_C:{
                        chou = (int)quotient;
                    }break;
                }
			
			/* Creating an output string */
			if (unit == UNIT_N)
			{
                if (chou !=0 && oku != 0 && man != 0 && nashi != 0){
					sprintf_s(output, MAX_TEXT_LEN * sizeof(char), "�i��%d��%d��%d��%d�~�j",chou, oku, man, nashi);
				}
				else if (oku != 0 && man != 0 && nashi != 0){
					sprintf_s(output, MAX_TEXT_LEN * sizeof(char), "�i��%d��%d��%d�~�j",oku, man, nashi);
				}
				else if (man != 0 && nashi != 0){
					sprintf_s(output, MAX_TEXT_LEN * sizeof(char), "�i��%d��%d�~�j",man, nashi);
				}
				else{
					sprintf_s(output, MAX_TEXT_LEN * sizeof(char), "�i��%d�~�j", nashi);
				}
			}
            else if (unit == UNIT_M){
                if (chou !=0 && oku != 0 && man != 0){
					sprintf_s(output, MAX_TEXT_LEN * sizeof(char), "�i��%d��%d��%d���~�j",chou, oku, man);
				}
				else if (oku != 0 && man != 0){
					sprintf_s(output, MAX_TEXT_LEN * sizeof(char), "�i��%d��%d���~�j",oku, man);
				}
				else{
					sprintf_s(output, MAX_TEXT_LEN * sizeof(char), "�i��%d���~�j",man);
				}
            }
            else if (unit == UNIT_O){
				if (chou !=0 && oku != 0){
					sprintf_s(output, MAX_TEXT_LEN * sizeof(char), "�i��%d��%d���~�j",chou, oku);
				}
				else{
					sprintf_s(output, MAX_TEXT_LEN * sizeof(char), "�i��%d���~�j", oku);
				}
            }
            else if (unit == UNIT_C){
                sprintf_s(output, MAX_TEXT_LEN * sizeof(char), "�i��%d���~�j", chou);
            }
            
            /*Copying output string to clipboard*/
			const size_t output_len = strlen(output) + 1;
			HGLOBAL hMem =  GlobalAlloc(GMEM_MOVEABLE, output_len);
			memcpy(GlobalLock(hMem), output, output_len);
			GlobalUnlock(hMem);
			OpenClipboard(0);
			EmptyClipboard();
			SetClipboardData(CF_TEXT, hMem);
			CloseClipboard();
        }
    }
	
    return (0);
}

/*
This function shows what type of error is on the screen, wait user to hit Enter to continue.
*/
void show_error(error_type error){
    int c; 
    
    do{
        c = getchar();
    }
    while (c != '\n' && c != EOF);
    
    if (c == EOF) {
        exit(0);
    } else {
        switch (error){
            case ERROR_INVALID_UNIT:{
                printf("\n");
				printf("�w�肵���P�ʂ��Ԉ���Ă��܂��B�uc�v�uo�v�um�v�̂ǂꂩ���g�p���Ă��������B\n");
				printf("\n");
				printf("�u�G���^�[�v�ł�蒼��\n");
                getchar();
            }break;
			
			case ERROR_INVALID_CR:{
				printf("\n");
				printf("�בփ��[�g�Ƀ}�C�i�X�̒l�͓��͂ł��܂���B\n");
				printf("\n");
				printf("�u�G���^�[�v�ł�蒼��\n");
                getchar();
			}break;
		}
    }
}

/*
This function asks user to put a currency rate, and stores in the adress given as a parameter.
*/
void ask_and_set_currency_rate(float *rate)
{
	for (;;){
		system("cls");
		printf("\n");
		printf("==== Currency Converter v1.0 ==== \n");
		printf("\n");
		printf("�בփ��[�g����͂��Ă��������B\n");
		printf(">: ");
		
		scanf_s("%f", rate);
		
		// the Currency Rate must be a positive value.
		if (*rate < 0.0){
			show_error(ERROR_INVALID_CR);
			continue;
		}
		else{
			break;
		}
	}
}