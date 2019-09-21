#include "types.h"
#include "stat.h"
#include "user.h"

#define INTMAX 8192

char buf[INTMAX];
char prev[INTMAX];
char current[INTMAX];
char* fileName;
char* null = {0};
int toLower(char a)
{
    if(a>='A' && a<='Z')
        return('a' + a - 'A');
    else
        return a;
}

    int
stringcmp(char* a, char* b, int size)
{
    int j;
    for(j=0; j<size; j++)
    {
        if(a[j] != b[j])
            return -1;
    }
    return 0;
}

int stringicmp(char *a, char* b, int size){

    int i;
    char temp1, temp2;
    for(i=0; i<size; i++){

        temp1=toLower(a[i]);
        temp2=toLower(b[i]);
        if(temp1!=temp2)
            return -1;
    }
    return 0;
}

void stringcpy(char* a, char* b, int size)
{
    int j;
    for(j=0; j<size; j++)
        a[j] = b[j];
    return;
}

void reset(char* a, int size)
{
    int j;
    for(j=0; j<size; j++)
        a[j] = '\0';
    return; 
}

void uniqTemp(int fd)
{
    int i, n;
    int charCount = 0;  
    while((n = read(fd, buf, sizeof(buf))) > 0){

        for(i=0; i<n; i++){

            if(buf[i] != '\n')
            {
                current[charCount] = buf[i];
                charCount++;
            }
            else
            {
                if  (0 != stringcmp( prev, current, INTMAX))
                {
                    printf(1,"%s\n", current);
                    reset(prev,INTMAX);
                    stringcpy(prev, current, INTMAX);
                    reset(current, INTMAX);
                }
                charCount = 0;
                reset(current, INTMAX);
            }
        }
    }
    if(n < 0){
        printf(1, "uniq: read error\n");
    }
}

void 
uniq(int cflag, int dflag, int iflag, int fd){

    int i, n;
    int charCount = 0;
    int count=1;
    int d=0;
    int line_count=0;
    int a=0;
    if(iflag==0){

        if(dflag){
            while((n = read(fd, buf, sizeof(buf))) > 0){
                for(i=0; i<n; i++){
                    if(buf[i] != '\n')
                    {
                        current[charCount] = buf[i];
                        charCount++;
                    }
                    else
                    {
                        if  (0 == stringcmp( prev, current, INTMAX))
                        {   
                            count++;
                            d=1;
                        }
                        else
                        { 
                            if(d){
                                printf(1, "%s\n", prev); 
                                d=0;
                            }
                            reset(prev,INTMAX);
                            stringcpy(prev, current, INTMAX);
                            reset(current, INTMAX);
                            count=1;
                        }
                        charCount = 0;
                        reset(current, INTMAX);
                    }
                }
            }
            if(d==1){
                printf(1, "%s\n", prev);  
            }
            if(n < 0){
                printf(1, "Uniq: read error\n");
            }
        }else{

            if(cflag){

                while((n = read(fd, buf, sizeof(buf))) > 0){
                    a=1;
                    for(i=0; i<n; i++){
                        if(buf[i] != '\n')
                        {
                            current[charCount] = buf[i];
                            charCount++;
                        }
                        else
                        {   
                            line_count++;
                            if  (0 == stringcmp( prev, current, INTMAX))
                            {   
                                count++;
                            }
                            else
                            {   
                                if(line_count!=1){
                                    printf(1, "    %d %s\n", count, prev);
                                }
                                reset(prev,INTMAX);
                                stringcpy(prev, current, INTMAX);
                                reset(current, INTMAX);
                                count=1;
                            }
                            charCount = 0;
                            reset(current, INTMAX);
                        }
                    }
                }
                if(a==1){
                    printf(1, "    %d %s\n", count, prev);
                }
                if(n < 0){
                    printf(1, "Uniq: read error\n");
                }  

            }

        }
    }else{
        if(dflag){
            while((n = read(fd, buf, sizeof(buf))) > 0){
                for(i=0; i<n; i++){
                    if(buf[i] != '\n')
                    {
                        current[charCount] = buf[i];
                        charCount++;
                    }
                    else
                    {
                        if  (0 == stringicmp( prev, current, INTMAX))
                        {   
                            count++;
                            d=1;
                        }
                        else
                        { 
                            if(d){
                                printf(1, "%s\n", prev); 
                                d=0;
                            }
                            reset(prev,INTMAX);
                            stringcpy(prev, current, INTMAX);
                            reset(current, INTMAX);
                            count=1;
                        }
                        charCount = 0;
                        reset(current, INTMAX);
                    }
                }
            }
            if(d==1){
                printf(1, "%s\n", prev);  
            }
            if(n < 0){
                printf(1, "Uniq: read error\n");
            }
        }else{

            if(cflag){

                while((n = read(fd, buf, sizeof(buf))) > 0){
                    a=1;
                    for(i=0; i<n; i++){
                        if(buf[i] != '\n')
                        {
                            current[charCount] = buf[i];
                            charCount++;
                        }
                        else
                        {
                            line_count++;
                            if  (0 == stringicmp( prev, current, INTMAX))
                            {   
                                count++;
                            }
                            else
                            { 
                                if(line_count!=1){
                                    printf(1, "    %d %s\n", count, prev);
                                }
                                reset(prev,INTMAX);
                                stringcpy(prev, current, INTMAX);
                                reset(current, INTMAX);
                                count=1;
                            }
                            charCount = 0;
                            reset(current, INTMAX);
                        }
                    }
                }
                if(a==1){
                    printf(1, "    %d %s\n", count, prev);
                }
                if(n < 0){
                    printf(1, "Uniq: read error\n");
                }  

            }else{
                int i, n;
                int charCount = 0;  
                while((n = read(fd, buf, sizeof(buf))) > 0){

                    for(i=0; i<n; i++){

                        if(buf[i] != '\n')
                        {
                            current[charCount] = buf[i];
                            charCount++;
                        }
                        else
                        {
                            if  (0 == stringicmp( prev, current, INTMAX))
                            {
                            }
                            else
                            {
                                printf(1,"%s\n", current);
                                reset(prev,INTMAX);
                                stringcpy(prev, current, INTMAX);
                                reset(current, INTMAX);
                            }
                            charCount = 0;
                            reset(current, INTMAX);
                        }
                    }
                }
                if(n < 0){
                    printf(1, "Uniq: read error\n");
                }
            }
        }
    }
}


    int 
main(int argc, char *argv[])
{
    int fd, i;
    if(argc <=1)
    {
        //Handling stdin
        uniqTemp(0);
        exit();
    }

    //parsing the command for utilities
    int cflag=0, dflag=0, iflag=0;
    for(i = 1; i < argc; i++)
    {
        if(argv[i][0]=='-')
        {
            if(argv[i][1]=='c')
                cflag=1;
            else if(argv[i][1]=='d')
                dflag=1;
            else if(argv[i][1]=='i')
                iflag=1;
            else
            {
                printf(1, "Invalid flag entered");
                exit();
            }
        }
        else
            fileName = argv[i];
    }

    if(fileName != null){
        if((fd = open(fileName, 0)) < 0)
        {
            printf(1, "Uniq: cannot open %s\n", argv[i]);
            exit();
        }
    } 
    else
        fd = 0;  //Standard input

    if(cflag==0 && dflag==0 && iflag==0)
        uniqTemp(fd);
    else
        uniq(cflag, dflag, iflag, fd);

    close(fd);
    exit();
}