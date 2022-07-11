#include <stdio.h>
#include <math.h>

int main()
{
    float a,b;
    char c;
    scanf("%f",&a);
    while((c=getchar())!='=')//当输入=号时程序退出
    {
        if(c==' '||c=='\t'||c=='\n')
            continue;
        scanf("%f",&b);
        switch(c)
        {
        case '+':
            a+=b;
            break;
        case '-':
            a-=b;
            break;
        case '*':
            a*=b;
            break;
        case '/':
            a/=b;
            break;
        case '%':
            a=fmod(a,b);
            break;
        }
    }
    printf("%f",a);
    return 0;
}
