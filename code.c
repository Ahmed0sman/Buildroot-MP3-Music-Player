#include <stdio.h>
#include <stdlib.h>
#include <string.h> 
#include <unistd.h>
#include <wiringPi.h>
#include <stdlib.h>

const int play_pause = 1; 
const int next = 4; 
const int prev = 5; 
const int shuf = 6; 

#define BUF 128 
#define TOT 10 
 char line[TOT][BUF];
    int total = 0;

int read_txt(void)
{
    FILE *plist = NULL; 
    int i = 0;

    plist = fopen("text", "r");
    while(fgets(line[i], BUF, plist)) {
        
        line[i][strlen(line[i]) - 1] = '\0';
        i++;
    }

   return i;
}
 
 
int main(void) {

wiringPiSetup () ;
printf("hello world");

pinMode(play_pause, INPUT);     
pullUpDnControl(play_pause, PUD_DOWN); 

pinMode(next, INPUT);      
pullUpDnControl(next, PUD_DOWN); 

pinMode(prev, INPUT);      
pullUpDnControl(prev, PUD_DOWN); 

pinMode(shuf, INPUT);      
pullUpDnControl(shuf, PUD_DOWN); 

int shuffle;
int x=0;
char Load[150]="echo LOAD ";
char str[20]=" >> input &";
char Load1[150]="echo LOAD ";
system("mkfifo input");


system("mpg123 -R --fifo input &");
//system("sudo mpg123 -R --fifo input -a bluealsa:DEV=30:C7:AE:35:B1:ED,PROFILE=a2dp,HCI=hci0 &");
sleep(1);
system("echo SILENCE >> input &");
sleep(1);
total=read_txt();
printf("%d\n",total);

int i=0;
while(1)
    {
        if (digitalRead(play_pause)) 
        {
	usleep(500000);
	if(total>0)system("echo PAUSE > input");
	else system("espeak -s 80 -p 10 There_is_no_mp3_files_on_the_disk");
        }

        if (digitalRead(next)) 
        {
	sleep(1);

	if(total>0)
	{
	if(x<total){
		    strcat(Load,line[x]);
		    strcat(Load,str);
		    system(Load);
		    x++;	
		    for(i=0;i<150;i++)Load[i]='\0';
		    strcpy(Load,Load1);		
		}
	}

	else system("espeak -s 80 -p 10 There_is_no_mp3_files_on_the_disk");
        }

        if (digitalRead(prev)) 
        {
	sleep(1);

	if(total>0)
	{

	if(x>0){
		x--;
		strcat(Load,line[x]);
		strcat(Load,str);
		system(Load);
		for(i=0;i<150;i++)Load[i]='\0';
		strcpy(Load,Load1);
		}

	}
	else system("espeak -s 80 -p 10 There_is_no_mp3_files_on_the_disk");

        }

        if (digitalRead(shuf)) 
        {
	usleep(500000);
	if(total>0)
	{
	shuffle=rand() % (total);

		strcat(Load,line[shuffle]);
		strcat(Load,str);
		system(Load);

	for(i=0;i<150;i++)Load[i]='\0';
	strcpy(Load,Load1);

        }

	else system("espeak -s 80 -p 10 There_is_no_mp3_files_on_the_disk"); 
	}

   }



return 0;
}











