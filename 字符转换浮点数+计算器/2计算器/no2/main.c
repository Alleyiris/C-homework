#include <stdio.h>
#include <math.h>

int main()
{
    float a,b;
    char c;
    scanf("%f",&a);
    while((c=getchar())!='=')//������=��ʱ�����˳�
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
