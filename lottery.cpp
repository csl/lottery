#include <string>
#include <stdlib.h>
#include <iostream>
#include <sstream>
#include <list>

#define MAXDIGITS 49
#define MD 100
#define MDF 1000

using namespace std;

//00-99
int num[MAXDIGITS]={0};
int lotterytimes[MD]={0};
int hlotterytimes[MDF]={0};
int number=0;

char* itoa(int number, char *buffer, int divisor)
{
    char *p = buffer, *p1, *p2, tmp;
    unsigned long ud = number;
    int remainder;
       
    /* Negative decimal. */
    if (divisor == 10 && number < 0)
    {
        *p++ = '-';
        buffer++;
        ud = -number;
    }
    /* Hexadecimal. */
    else if (divisor == 16)
    {
        *p++ = '0';
        *p++ = 'x';
        buffer += 2;
    }
    /* Divide ud by the divisor, until ud == 0. */
    do
    {
        remainder = ud % divisor;
        *p++ = (remainder < 10) ? remainder + '0' : remainder + 'a' - 10;
    }
    while (ud /= divisor);
   
    /* Terminate buffer. */
    *p = 0;
   
    /* Initialize pointers. */
    p1 = buffer;
    p2 = p - 1;
   
    /* Reverse buf. */
    while (p1 < p2)
    {
        tmp = *p1;
        *p1 = *p2;
        *p2 = tmp;
        p1++;
        p2--;
    }

    return buffer;
}

void bubblesort(int *data, int n)
{
    int i, j, temp;
    for (i = n - 1; i > 0; i--)
    {
        for (j = 0; j <= i - 1; j++)
        {
            if (data[j] > data[j + 1])
            {
                temp = data[j];
                data[j] = data[j + 1];
                data[j + 1] = temp;
            }
        }
    }
}

void countTnumber(string x, const char sep)
{
	int TNum[6]={0},TtNum[5]={0}, i=0, first=0;
	int HNum[6]={0};
	int O,T;
	char temp[3]="", Htemp[4]="";
	list<string> ret;
    istringstream is(x);

 	first=0;
    while(!is.eof())
    {
        string temp;
        getline(is, temp, sep);
		//omit 1
		if (first != 0)
		{
			TNum[i] = atoi(temp.c_str());
			i++;
		}
		first=1;
    }

	//Sorting
	bubblesort(TNum, 6);
	//printf("%d %d %d %d %d %d\n", TNum[0], TNum[1], TNum[2], TNum[3], TNum[4], TNum[5]);
	//
	//fetch T
	for(int r=0; r<5;r++)
	{
		//fetch number
		T = TNum[r]%10;
		O = TNum[r+1]%10;

		//combination
		temp[0] = T + '0';
		temp[1] = O + '0';
		temp[2] = '\0';

		//count
		lotterytimes[atoi(temp)]++;
	}

	//000-999
	//fetch 3~5 number
    temp[0] = (TNum[2]%10) + '0';
    temp[1] = (TNum[3]%10) + '0';
    temp[2] = (TNum[4]%10) + '0';
    temp[3] = '\0';
	hlotterytimes[atoi(temp)]++;	
}

void combination(string x, int n, int r)
{
	char buffer[10];

	if (r==n||r==0) {
		for (int i=r;i>0;i--)
			x= x +' ' + itoa(num[i-1],buffer,10);
			
			//cout<<x<<endl;
			countTnumber(x, ' ');		
			number++;
			return;
	}

	combination(x + ' ' + itoa(num[n-1], buffer, 10), n-1, r-1);
	combination(x,n-1,r);

}

int main()
{
	FILE *fp;
	FILE *fph;

	fp = fopen("reslut.txt","w");	
	fph = fopen("resluth.txt","w");	

	for (int i=1; i<=MAXDIGITS; i++)
	{
		num[i-1] = i;
	}

	combination("", MAXDIGITS, 6);
	cout << "total = " << number << endl;

	//00-99
	for (int i=0; i<MD; i++)
	{
		if (i==0)
			fprintf(fp, "00: %d\r\n", lotterytimes[i]);
		else if (i<10)
			fprintf(fp, "0%d: %d\r\n", i, lotterytimes[i]);
		else
			fprintf(fp, "%d: %d\r\n", i, lotterytimes[i]);
	}

	//000-999
	for (int i=0; i<MDF; i++)
	{
		if (i==0)
			fprintf(fph, "000: %d\r\n", hlotterytimes[i]);
		else if (i<10)
			fprintf(fph, "00%d: %d\r\n", i, hlotterytimes[i]);
		else if (i<100)
			fprintf(fph, "0%d: %d\r\n", i, hlotterytimes[i]);
		else
			fprintf(fph, "%d: %d\r\n", i, hlotterytimes[i]);
	}

	fclose(fp);
	fclose(fph);
	return 0;
}
