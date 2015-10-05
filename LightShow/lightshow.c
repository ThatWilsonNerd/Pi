#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <pthread.h>
#include <wiringPi.h>

int grpAll[] = {0,1,2,3,4,5,6,7};
int grpAllCount = sizeof(grpAll)/sizeof(int);

int grp1[] = {0,1,2};
int grp1Count = sizeof(grp1)/sizeof(int);

int grp2[] = {3,4,5};
int grp2Count = sizeof(grp2)/sizeof(int);

int grp3[] = {6,7};
int grp3Count = sizeof(grp3)/sizeof(int);

int ON = LOW;
int OFF = HIGH;

void setupPins() {
	int p;
	for(p=0;p<grpAllCount;p++)
	{
		pinMode(grpAll[p],OUTPUT);
	}
}

void allLights(int val) {
	int p;
    printf("all lights %i\n",val);
	for(p=0;p<grpAllCount;p++)
	{
        digitalWrite(grpAll[p],val);
	}
}

void kitt(int l, int d) {
    printf("running kitt(%i,%i)\n",l,d);
    int p;
    int i = 0;
    while(i<l)
    {
        printf("loop %i/%i\n",i,l);
        for(p=0;p<grpAllCount;p++)
        {
            digitalWrite(grpAll[p],ON);delay(d);
            digitalWrite(grpAll[p],OFF);
        }
        for(p=(grpAllCount-2);p>0;p--)
        {
            digitalWrite(grpAll[p],ON);delay(d);
            digitalWrite(grpAll[p],OFF);
        }
        i++;
    }
}


int main(int argc, char** argv) {
	if(argc > 1) {
        wiringPiSetup();
        setupPins();
        //  get command
        char *c = argv[1];
        if(strncmp(c,"on",strlen(c))==0)
        {
            allLights(ON);
        }
        else if(strncmp(c,"off",strlen(c))==0)
        {
            allLights(OFF);
        }
        else if(strncmp(c,"kitt",strlen(c))==0)
        {
            int l = atoi(argv[2]);
            int d = atoi(argv[3]);
            kitt(l,d);
        }
        else {
            printf("invalid command '%s'",c);
        }
    }
    else {
        puts("no commands entered.");
	}
    return 0;
}
