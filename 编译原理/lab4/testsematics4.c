int a, b, c;
float m, n;
int d[10][10];

/*
typedef struct
{
	int a;
	int b;
}TestStruct;
*/

int fibo(int a)
{
      //TestStruct tt;
    if (a == 1 || a == 2)
		return 1;
	if (a>=3)
	{
	    //tt.a = d[1][2];
	    c = d[1][2];
	    return fibo(a-1) + fibo(a-2);	
	}
    return 0;
}

int main(int argc)
{
	int i;
	for(i = 1;i<10;i++)
	{
		if(i>9)
		{
			fibo(i);
			break;
		} 
		else
		{
			fibo(i);
			continue;
		}
		i++;
	}
	return 1;
}

