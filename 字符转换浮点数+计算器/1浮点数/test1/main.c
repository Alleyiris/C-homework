#include <stdio.h>

int main()
{
    char a;
    float b;
    float c=0,d=1;
    int t=0;//标志变量，记录小数点的输入

    while((a=getchar())!='/n')
    {
        if(a=='.')//当输入小数点时，t自增
        {
            ++t;
            continue;
        }

          if(a>='0'&&a<='9'&&t==0)//a为数字并且未输入过小数点
          {
            b=(a-'0');
            c=c*10+b;
          }
          else if(a>='0'&&a<='9'&&t==1)//a为数字并且只输入过一个小数点
          {
            b=(a-'0');
            c=c*10+b;
            d*=10;
          }
          else//非法输入
           {
                c=c/d;
                printf("%f",c);
                break;
            }
              }

    return 0;
}
