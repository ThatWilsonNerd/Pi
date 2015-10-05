#include <stdio.h>
#include <wiringPi.h>

int grpAll[] = {0,1,2,3,4,5,6,7};
int grpAllCount = sizeof(grpAll)/sizeof(int);

int grp1[] = {0,1,2};
int grp1Count = sizeof(grp1)/sizeof(int);

int grp2[] = {3,4,5};
int grp2Count = sizeof(grp2)/sizeof(int);

int grp3[] = {6,7};
int grp3Count = sizeof(grp3)/sizeof(int);

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
	for(g=0;g<3;g++)
	{
		digitalWrite(grp[g],val);
	}
}

void kitt() {
	int p;
	for(p=0;p<grpAllCount;p++)
	{
		digitalWrite(grpAll[p],HIGH);delay(100);
		digitalWrite(grpAll[p],LOW);
	}
	for(p=(grpAllCount-2);p>0;p--)
	{
		digitalWrite(grpAll[p],HIGH);delay(100);
		digitalWrite(grpAll[p],LOW);
	}
}


int main() {
	wiringPiSetup();
	int p;
	printf("Light Channels: %d\n",grpAllCount);
	for(p=0;p<grpAllCount;p++)
	{
		pinMode(grpAll[p],OUTPUT);
	}


	int i;
	int loops = 5;
	for (i=1;i<=loops;i++)
	{
		printf("Loop %d/%d\n",i,loops);
		allLights(HIGH);
		delay(1000);
		allLights(LOW);
		delay(1000);
		kitt();
		kitt();
		kitt();
		groupLights(grp1,grp1Count,HIGH);
		delay(500);
		groupLights(grp3,grp3Count,HIGH);
		delay(250);
		groupLights(grp1,grp1Count,LOW);
		groupLights(grp2,grp2Count,HIGH);
		delay(1000);
		allLights(LOW);
		delay(250);
	}

	allLights(LOW);
	return 0;
}
