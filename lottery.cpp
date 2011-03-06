#include <string>
#include <stdlib.h>
#include <iostream>

#define MAXDIGITS 49
#define MD 99

using namespace std;

int num[MAXDIGITS]={0};
int lottery[6]={0};
int lotterytimes[MD]={0};
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

void combination(string x, int n, int r)
{
	char buffer[10];

	if (r==n||r==0) {
		for (int i=r;i>0;i--)
			x= x +' ' + itoa(num[i-1],buffer,10);
			//cout<<x<<endl;
			
			number++;
			return;
	}

	combination(x + ' ' + itoa(num[n-1], buffer, 10), n-1, r-1);
	combination(x,n-1,r);

}

int main()
{
	for (int i=1; i<=MAXDIGITS; i++)
	{
		num[i-1] = i;
	}

	combination("", MAXDIGITS, 6);
	cout << "total = " << number << endl;
	return 0;
}
