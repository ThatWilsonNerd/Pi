#include <stdio.h>
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
	for(p=0;p<grpAllCount;p++)
	{
		digitalWrite(grpAll[p],val);
	}
}

void groupLights(int grp[],int s,int val)
{
	int g;
	for(g=0;g<s;g++)
	{
		digitalWrite(grp[g],val);
	}
}

void kitt() {
	int p;
	for(p=0;p<grpAllCount;p++)
	{
		digitalWrite(grpAll[p],ON);delay(100);
		digitalWrite(grpAll[p],OFF);
	}
	for(p=(grpAllCount-2);p>0;p--)
	{
		digitalWrite(grpAll[p],ON);delay(100);
		digitalWrite(grpAll[p],OFF);
	}
}

void *beat(void *args)
{
	for(;;)
	{
		digitalWrite(0,ON);digitalWrite(1,ON);
		delay(500);
		digitalWrite(0,OFF);digitalWrite(1,OFF);
		delay(500);
	}
}

int main() {
	wiringPiSetup();
	printf("Light Beat Channels: %d\n",grpAllCount);
	setupPins();

	pthread_t tid;
	pthread_create(&tid,NULL,beat,NULL);

	int i;
	int loops = 5;
	for (i=1;i<=loops;i++)
	{
		printf("Loop %d/%d\n",i,loops);
		//allLights(HIGH);
		//delay(1000);
		//allLights(LOW);
		delay(1000);
		//kitt();
		//groupLights(grp1,grp1Count,HIGH);
		//delay(500);
		groupLights(grp3,grp3Count,ON);
		delay(1000);
		groupLights(grp3,grp1Count,OFF);
		groupLights(grp2,grp2Count,ON);
		delay(1000);
		groupLights(grp2,grp2Count,OFF);
	}
	//pthread_exit(NULL);

	allLights(OFF);
	return 0;
}
