#include <stdio.h>

int main()
{
    char a;
    float b;
    float c=0,d=1;
    int t=0;//��־��������¼С���������

    while((a=getchar())!='/n')
    {
        if(a=='.')//������С����ʱ��t����
        {
            ++t;
            continue;
        }

          if(a>='0'&&a<='9'&&t==0)//aΪ���ֲ���δ�����С����
          {
            b=(a-'0');
            c=c*10+b;
          }
          else if(a>='0'&&a<='9'&&t==1)//aΪ���ֲ���ֻ�����һ��С����
          {
            b=(a-'0');
            c=c*10+b;
            d*=10;
          }
          else//�Ƿ�����
           {
                c=c/d;
                printf("%f",c);
                break;
            }
              }

    return 0;
}
