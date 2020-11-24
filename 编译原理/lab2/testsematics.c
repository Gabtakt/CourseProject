int a, b, c;
float m,n;
int b[10][10],d[10][10];//变量重发声明

int fibo(int a){
    test1(c);//函数未定义
	if (a == 1 || a == 2)
	    return 1;
	return fibo(a - 1) + fibo(a - 2);
	if (a > 10)
	    return fibo(a - 1, a - 2);//函数参数过多
	if (b > 100)
		return fibo(a - 1) + fibo(a - 2);
	else{
		b--;
	}
    fibo(tt);//变量未定义
    c = a[8]; //数组访问非法
    m = 0.8;
    n = 0.9;
    c = d[m][n];//数组访问下标不是int型
	break; // break语句不在循环体内
    return 0;
}
void testf(){
    return 'a';//返回值类型不对
}

int  testff(){
     int i;
     i++;
}//缺少返回值

int main(int argc){
	int m=10, n, i;
	test1 = 0;//test1未定义
	i = 1;
        n = m(); //m不是函数
        (n+1) = m; //赋值语句需要左值
        --(n+1);  //自增自减对象只能是变量
        a = m; // a未定义
        continue; //continue语句不在循环体内
	while (i <= m){
		n = fibo(i);
		i = i + 1;
        if(i>10){
			break;
		}
        else
            continue;
	}
    n = fibo; // 函数调用缺少参数
	return 1;
}

