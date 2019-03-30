#include <stdio.h>
#include <stdlib.h>
#include <string.h> 
#include <unistd.h>
#include <wiringPi.h>
#include <stdlib.h>
//gcc p.c -o a -lwiringPi -lcrypt -lpthread -lm -lrt


/* Defining the pin numbers                                      */
const int play_pause = 1; 
const int next = 4; 
const int prev = 5; 
const int shuf = 6; 

/*Creating an array to hold the name of the songs on the device  */
/*The max length of the file name is 128                         */
/*The max number of files is 10                                  */
#define BUF 128 
#define TOT 10 
char line[TOT][BUF];

/*Total holds the number of music files read                     */
int total = 0;

/*The read the file with the mp3 files' names and write them in  */
/*array and adds a terminator at the end of each line            */
/*Inputs: None                                                   */
/*Return: The number of mp3 files in the device                  */
int read_txt(void)
{
    FILE *plist = NULL; 
    int i = 0;
    /*Opens the file as read only                                */
    plist = fopen("text", "r");
    /*Writes the name of the mp3 files in the array (line)       */
    while(fgets(line[i], BUF, plist)) {
        /*ends each line with a terminator                       */
        line[i][strlen(line[i]) - 1] = '\0';
        i++;
    }

   return i;
}
 


//gcc -Wall -o blink blink.c -lwiringPi
 
int main(void) {
    /*Configure the GPIO                                              */
    wiringPiSetup();
    printf("hello world");
    
    /*Configure the pins on the RP for the push buttons as input      */
    /*and pull down */
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
    /*create strings for concatenating commands                        */
    char Load[150]="echo LOAD ";
    char str[20]=" >> input &";
    /*This string saves the string of the first variable to make sure  */
    /*We still have the string after the concatenation                 */
    char Load1[150]="echo LOAD ";
  
    system("mkfifo input");

    /*create strings for concatenating commands 		       */
    char st1[150]="echo ";
    char st2[150]=" | wall";

    /*This string saves the string of the first variable to make sure  */
    /*We still have the string after the concatenation                 */
    char st3[150]="echo ";

    
    /*Play music using mpg123 on the bluetooth device using its MAC    */
    /*address and by using the internal bluetooth on the RP (HCI0)     */
    system("sudo mpg123 -R --fifo input -a bluealsa:DEV=30:C7:AE:35:B1:ED,PROFILE=sco,HCI=hci0 &");
    sleep(1);
    /*Stop the printing on the terminal                                */
    system("echo SILENCE >> input &");
    sleep(1);
    /*Read the file                                                    */
    total=read_txt();
    /*Print the number of songs for checking                           */
    printf("%d\n",total);

    int i=0;
    while(1)
        {
            /*Check if the play_pause button is pressed                 */
            if (digitalRead(play_pause)) 
            {
                /*Delay for debouncing                                  */
                usleep(500000);
                
                /*Checks if the number of files is greater than 0       */
                if(total>0)
                {
                    /*Pause the musics */
                    system("echo PAUSE > input");
                }
                else 
                {
                    /*Speaks that there is no mp3 files                  */
                    system("espeak -s 80 -p 10 There_is_no_mp3_files_on_the_disk");
                }
				
		/*Concatenate the string to form the command    	 */
                /*The command is "echo (song) | wall"		         */
		strcat(st1,line[x]);
		strcat(st1,st2);
				
		/*Call the command 	                                 */
		system(st1);
				
		/*Clears the string	                                 */
		for(i=0;i<150;i++)
		{
			st1[i]='\0';
		}
		/*return the string to its original state  	         */
		strcpy(st1,st3);
				
            }

            /*Check if the next button is pressed                        */
            if (digitalRead(next)) 
            {
                /*Delay for debouncing                                   */
                sleep(1);
                /*Checks if the number of files is greater than 0        */
                if(total>0)
                {
                    /*Check if reached the last song wasn't reached      */
                    if(x<total)
                    {
                        /*Concatenate the string to form the command     */
                        /*The command is "echo LOAD (song) >> input &"   */
                        strcat(Load,line[x]);
                        strcat(Load,str);
                        
                        /*Call the command                               */
                        system(Load);
                        
                        /*Print the name of the played song and its      */
                        /*position in the list                           */
                        printf("%s   %d\n",Load,x);
                        
                        /*Increment the index of the song                */
                        x++;	
                        
                        /*Clears the string                              */
                        for(i=0;i<150;i++)
                        {
                            Load[i]='\0';
                        }
                        
                        /*return the string to its original state        */
                        strcpy(Load,Load1);

			/*Concatenate the string to form the command     */
		        /*The command is "echo (song) | wall"	         */
			strcat(st1,line[x]);
			strcat(st1,st2);
					
			/*Call the command 	                         */
			system(st1);
					
			/*Clears the string	                         */
			for(i=0;i<150;i++)
			{
				st1[i]='\0';
			}
			/*return the string to its original state  	 */
			strcpy(st1,st3);		
                    }
                }
                else 
                {
                    /*Speaks that there is no mp3 files                  */
                    system("espeak -s 80 -p 10 There_is_no_mp3_files_on_the_disk");
                }
            }
            
            /*Check if the previous button is pressed                    */
            if (digitalRead(prev)) 
            {
                /*Delay for debouncing                                   */
                sleep(1);
 
                /*Checks if the number of files is greater than 0        */
                if(total>0)
                {
                    /*Check if reached the first song wasn't reached     */
                    if(x>0)
                    {
                        /*Decrement the index of the song                */
                        x--;
                        
                        /*Concatenate the string to form the command     */
                        /*The command is "echo LOAD (song) >> input &"   */
                        strcat(Load,line[x]);
                        strcat(Load,str);
                        
                        /*Call the command                               */
                        system(Load);
                        
                        /*Print the name of the played song and its      */
                        /*position in the list                           */
                        printf("%s   %d\n",Load,x);
                        
                        /*Clears the string                              */
                        for(i=0;i<150;i++)
                        {
                            Load[i]='\0';
                        }
                        
                        /*return the string to its original state         */
                        strcpy(Load,Load1);

			/*Concatenate the string to form the command      */
		        /*The command is "echo (song) | wall"	          */
			strcat(st1,line[x]);
			strcat(st1,st2);
					
			/*Call the command 	                          */
			system(st1);
					
			/*Clears the string	                          */
			for(i=0;i<150;i++)
			{
				st1[i]='\0';
			}
			/*return the string to its original state        */
			strcpy(st1,st3);
                    }

                }
                else 
                {
                    /*Speaks that there is no mp3 files                   */
                    system("espeak -s 80 -p 10 There_is_no_mp3_files_on_the_disk");
                }

            }
            
            /*Check if the shuffle button is pressed                      */
            if (digitalRead(shuf)) 
            {
                /*Delay for debouncing                                   */
                usleep(500000);
                
                /*Checks if the number of files is greater than 0        */
                if(total>0)
                {
                    /*Generates number number from to total              */
                    shuffle=rand() % (total);
                    
                    /*Concatenate the string to form the command     */
                    /*The command is "echo LOAD (song) >> input &"   */
                    strcat(Load,line[shuffle]);
                    strcat(Load,str);
                    
                    /*Call the command                               */
                    system(Load);
                    
                    /*Print the name of the played song and its      */
                    /*position in the list                           */
                    printf("%s   %d\n",Load,x);
                    
                    /*Clears the string                              */
                    for(i=0;i<150;i++)
                    {
                        Load[i]='\0';
                    }
                    
                    /*return the string to its original state        */                    
                    strcpy(Load,Load1);
                    printf("     %d\n",shuffle);

		   /*Concatenate the string to form the command      */
                   /*The command is "echo (song) | wall"             */
		   strcat(st1,line[x]);
		   strcat(st1,st2);
				
		   /*Call the command 	                             */
		   system(st1);
				
		   /*Clears the string	                             */
		   for(i=0;i<150;i++)
		   {
			st1[i]='\0';
		   }
		   /*return the string to its original state         */
		   strcpy(st1,st3);
                }
            }
            else 
            {
                /*Speaks that there is no mp3 files                   */
                system("espeak -s 80 -p 10 There_is_no_mp3_files_on_the_disk");
            }                
        }
    return 0;
}
