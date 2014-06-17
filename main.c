/**
 * \file main.c
 * \brief Brain Fuck Interpreter.
 * \author Nicolas Fleurot & Hassan El Azzouzi
 * \version 0.0.5
 * \date 17/06/2014
 *
 * A simple Brain Fuck Interpreter in C.
 *
*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <ctype.h>
#include <string.h>

#define SIZE_BUFF 256

#define TOKEN_INF   '<'
#define TOKEN_SUP   '>'
#define TOKEN_WB    '['
#define TOKEN_WE    ']'
#define TOKEN_PRINT '.'
#define TOKEN_GET   ','
#define TOKEN_MINUS '-'
#define TOKEN_PLUS  '+'

#define VERSION_FINAL 0
#define VERSION_SUB 0
#define VERSION_WIP 5
#define STABLE 1

#define AUTHOR "Hassan El Azzouzi & Nicolas Fleurot"

void Parse(const char* a_sInput);
void IBF(void);
void getVersion(void);

int main(int argc, char** argv)
{
    //TODO File input/output arguments
    //flag 0 : interpreter command line
    //flag 1 : get version
    int flags[2]={0};
    int c;
    char *stringOpt = NULL;
    opterr = 0;
    while((c = getopt(argc, argv, "r:iv"))!=-1)
    {
        switch(c)
        {
        case 'r':
            stringOpt=optarg;
            break;
        case 'i':
            flags[0]=1;
            break;
        case 'v':
            flags[1]=1;
            break;
        case '?':
            if(optopt=='r')
                fprintf(stderr,"Option -%c requires an argument [String].\n",optopt);
            else if(isprint(optopt))
                fprintf(stderr,"Unknown option %c.\n",optopt);
            else
                fprintf(stderr,"Unknown option character %c.\n",optopt);
            return 1;
        default:
            exit(EXIT_FAILURE);
              break;
        }
    }

    printf ("flags[0] = %d, stringOpt = %s\n",
               flags[0], stringOpt);

    if(stringOpt!=NULL)
        Parse(stringOpt);
    else if(flags[1]==1)
        getVersion();
    else if(flags[0]==1)
        IBF();

    return EXIT_SUCCESS;
}

/**
 * \fn void Parse(const char* a_sInput)
 * \brief Parsing a string.
 * \param a_sInput (String)
*/
void Parse(const char* a_sInput)
{
    int i=0;
    int t_iIndex = 0;
    int t_iPosIndex = 0;
    int t_iFactor = 1;
    unsigned int* t_Buffer = (unsigned int*)calloc(SIZE_BUFF, sizeof(unsigned int));
	if(t_Buffer==NULL)
		perror("calloc");
    int t_iNbCondition = 0;
    int t_iPosCondition[50] = { 0 };
    int t_iIndexCondition = -1;
    while(a_sInput[t_iIndex] != '\0')
    {
        switch (a_sInput[t_iIndex])
        {
            case TOKEN_PLUS:
            {
                t_Buffer[t_iPosIndex] += 1;
                break;
            }
            case TOKEN_MINUS:
            {
                t_Buffer[t_iPosIndex] -= 1;
                break;
            }
            case TOKEN_SUP:
            {
                t_iPosIndex += 1;
                if(t_iPosIndex > (t_iFactor * SIZE_BUFF)){
                    t_iFactor += 1;
                    unsigned int* t_NewBuffer = (unsigned int *)calloc(t_iFactor * SIZE_BUFF, sizeof(unsigned int));

					if(t_NewBuffer==NULL)
						perror("calloc");
                    i=0;
                    for(i=0 ; i < ((t_iFactor - 1) * SIZE_BUFF) ; i++){
                        t_NewBuffer[i] = t_Buffer[i];
                    }
                    free(t_Buffer);
                    t_Buffer = t_NewBuffer;
                }
                break;
            }
            case TOKEN_INF:
            {
                t_iPosIndex -= 1;
                break;
            }
            case TOKEN_PRINT:
            {
                putchar(t_Buffer[t_iPosIndex]);
                break;
            }
            case TOKEN_GET:
            {
                t_Buffer[t_iPosIndex] = getchar();
                break;
            }
            case TOKEN_WB:
            {
				//TODO [-] ne fonctionne pas
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
            case TOKEN_WE:
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

/**
 * \fn void IBF(void)
 * \brief Dirty interpreter.
 * \param void
*/
void IBF(void)
{
    char* brainCode=(char *)calloc((size_t)SIZE_BUFF,sizeof(char));
	if(brainCode==NULL)
		perror("calloc");
    int tmpFree=0;
    do{
        printf(">>");
        char *posRet=NULL;
        if(fgets(brainCode,(SIZE_BUFF*sizeof(unsigned char)),stdin)!=NULL)
            posRet=strchr(brainCode,'\n');
            if(posRet!=NULL)
                *posRet='\0';
            else
                while(tmpFree=0,tmpFree!='\n' && tmpFree!=EOF) tmpFree=getchar();
        puts("\n\n\t\t-----------------------");
        Parse(brainCode);
        puts("");
    }while(strchr(brainCode,'e')==NULL);
getVersion();
    free(brainCode);
}

/**
 * \fn void getVersion(void)
 * \brief Print the version.
 * \param void
*/
void getVersion(void)
{
	puts("\t\t ___  ________  ________ ");
	puts("\t\t|\\  \\|\\   __  \\|\\  _____\\");
	puts("\t\t\\ \\  \\ \\  \\|\\ /\\ \\  \\__/");
	puts("\t\t\\ \\  \\ \\   __  \\ \\   __\\");
	puts("\t\t\\ \\  \\ \\  \\|\\  \\ \\  \\_|");
	puts("\t\t\\ \\__\\ \\_______\\ \\__\\");
    puts("\t\t\\|__|\\|_______|\\|__|");
    printf("IBrainFuck version %s %d.%d.%d by %s %s\n",(STABLE)? "STABLE" : "NOT STABLE",
                                                        VERSION_FINAL,VERSION_SUB,VERSION_WIP,AUTHOR,__DATE__);
}

