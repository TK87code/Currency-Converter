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
			printf("==== Currency Converter v1.0　==== \n");
			printf("\n");
            printf("設定レート = %.2f　です。\n", currency_rate);
			printf("\n");
            printf("ドル表記の金額を入力してください。\n");
			printf("\n");
			printf("例：　1兆ドル -> '1c' | 230億ドル　-> '230o' | 3000万ドル -> '3000m | 1500ドル -> '1500n'\n");
			printf("\n");
            printf("アプリケーションを終了するには「Q」を入力してください。\n");
			printf("\n");
			printf("設定レートを終了するには「R」を入力してください。\n");
			printf("\n");
			
			/* Shows a last output on screen if any */
			if (output[0] != 0){
				printf("%s\n", output);
				printf("\n");               
				printf("上記をクリップボードにコピーしました。\n");
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
					sprintf_s(output, MAX_TEXT_LEN * sizeof(char), "（約%d兆%d億%d万%d円）",chou, oku, man, nashi);
				}
				else if (oku != 0 && man != 0 && nashi != 0){
					sprintf_s(output, MAX_TEXT_LEN * sizeof(char), "（約%d億%d万%d円）",oku, man, nashi);
				}
				else if (man != 0 && nashi != 0){
					sprintf_s(output, MAX_TEXT_LEN * sizeof(char), "（約%d万%d円）",man, nashi);
				}
				else{
					sprintf_s(output, MAX_TEXT_LEN * sizeof(char), "（約%d円）", nashi);
				}
			}
            else if (unit == UNIT_M){
                if (chou !=0 && oku != 0 && man != 0){
					sprintf_s(output, MAX_TEXT_LEN * sizeof(char), "（約%d兆%d億%d万円）",chou, oku, man);
				}
				else if (oku != 0 && man != 0){
					sprintf_s(output, MAX_TEXT_LEN * sizeof(char), "（約%d億%d万円）",oku, man);
				}
				else{
					sprintf_s(output, MAX_TEXT_LEN * sizeof(char), "（約%d万円）",man);
				}
            }
            else if (unit == UNIT_O){
				if (chou !=0 && oku != 0){
					sprintf_s(output, MAX_TEXT_LEN * sizeof(char), "（約%d兆%d億円）",chou, oku);
				}
				else{
					sprintf_s(output, MAX_TEXT_LEN * sizeof(char), "（約%d億円）", oku);
				}
            }
            else if (unit == UNIT_C){
                sprintf_s(output, MAX_TEXT_LEN * sizeof(char), "（約%d兆円）", chou);
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
				printf("指定した単位が間違っています。「c」「o」「m」のどれかを使用してください。\n");
				printf("\n");
				printf("「エンター」でやり直し\n");
                getchar();
            }break;
			
			case ERROR_INVALID_CR:{
				printf("\n");
				printf("為替レートにマイナスの値は入力できません。\n");
				printf("\n");
				printf("「エンター」でやり直し\n");
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
		printf("為替レートを入力してください。\n");
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