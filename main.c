#include <stdio.h>
#include <stdlib.h>

#define SIZE_BUFF 256

void Parse(const char* a_sInput);

int main(int argc, char** argv)
{
    if(argc != 2)
    {
        printf("BF : BF input\n");
        return EXIT_FAILURE;
    }
    Parse(argv[1]);

    return EXIT_SUCCESS;
}

void Parse(const char* a_sInput)
{
    int t_iIndex = 0;
    int t_iPosIndex = 0;
    int t_iFactor = 1;
    unsigned int* t_Buffer = (unsigned int*)calloc(SIZE_BUFF, sizeof(unsigned int));
    int t_iNbCondition = 0;
    int t_iPosCondition[50] = { 0 };
    int t_iIndexCondition = -1;
    while(a_sInput[t_iIndex] != '\0')
    {
        switch (a_sInput[t_iIndex])
        {
            case '+':
            {
                t_Buffer[t_iPosIndex] += 1;
                break;
            }
            case '-':
            {
                t_Buffer[t_iPosIndex] -= 1;
                break;
            }
            case '>':
            {
                t_iPosIndex += 1;
                if(t_iPosIndex > (t_iFactor * SIZE_BUFF)){
                    t_iFactor += 1;
                    unsigned int* t_NewBuffer = calloc(t_iFactor * SIZE_BUFF, sizeof(unsigned int));
                    int i=0;
                    for(i=0 ; i < ((t_iFactor - 1) * SIZE_BUFF) ; i++){
                        t_NewBuffer[i] = t_Buffer[i];
                    }
                    free(t_Buffer);
                    t_Buffer = t_NewBuffer;
                }
                break;
            }
            case '<':
            {
                t_iPosIndex -= 1;
                break;
            }
            case '.':
            {
                putchar(t_Buffer[t_iPosIndex]);
                break;
            }
            case ',':
            {
                t_Buffer[t_iPosIndex] = getchar();
                break;
            }
            case '[':
            {
                if(t_Buffer[t_iPosIndex] == 0){
                    t_iNbCondition += 1;
                    while(t_iNbCondition > 0){
                        t_iIndex += 1;
                        if(a_sInput[t_iIndex] == '['){
                            t_iNbCondition += 1;
                        }else if(a_sInput[t_iIndex] == ']'){
                            t_iNbCondition -= 1;
                        }
                    }
                }else{
                    t_iIndexCondition += 1;
                    t_iPosCondition[t_iIndexCondition] = t_iIndex;
                }
                break;
            }
            case ']':
            {
                if(t_Buffer[t_iPosIndex] > 0){
                    t_iIndex = (t_iPosCondition[t_iIndexCondition] - 1);
                    t_iIndexCondition -= 1;
                }
                break;
            }
            default:
            {
                break;
            }
        }
        t_iIndex += 1;
    } // While
    free(t_Buffer);
}
