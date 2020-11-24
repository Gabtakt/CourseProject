int fibo(int a)
{
    if (a == 1 || a == 2)
    {
        return 1;
    }
    return fibo(a - 1) + fibo(a - 2);
}


int main(int argc)
{
    int i,j;
	i = 0;
	for(j = 2; j <= 10; j++)
	{
		i=fibo(j);
	}
    //i = fibo(9);//fibo(9) = 34
    return 0;
}