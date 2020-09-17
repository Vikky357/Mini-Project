#include<stdio.h>
#include<stdlib.h>
#include<Windows.h>
#define True TRUE
int hh,mm,ss;
int keycheck(int);
int main()
{
    hh=mm=ss=0;
    printf("\t\t\t\t\tStopWatch\n\n\n\n");
    printf("\n\n\n\n");
    printf("\t\t\tPress the following keys to perform stopwatch functions\n");
    printf("\t\t\t\t\tR->Reset\n\t\t\t\t\tP->Pause\n\t\t\t\t\tS->Stop");
    printf("\n\n\n\n");
    while(True)
    {
        printf("\r\t\t\t\t%d%5c%10d%5c%10d",hh,':',mm,':',ss);
        sleep(1);
        ss++;
        if(ss==60)
        {
            mm++;
            ss=0;
        }
        if( mm==60)
        {
            hh++;
            mm=0;
            ss=0;
        }
        if(hh==24)
        {
            hh=0;
            ss=0;
            mm=0;
        }
        if(kbhit())
        {
            int c=getch();
            keycheck(c);

        }

    }

}
int keycheck(int c)
{
    if(c=='r')
            {
                hh=mm=ss=0;
                return;
            }
    if(c=='p')
            {
                while(True)
                {
                    sleep(1);
                    c=getch();
                    if(c=='p')
                        break;
                    return keycheck(c);
                }
            }
    if(c=='s')
            exit(0);

    return ;
}
