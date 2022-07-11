#include <stdio.h>
/*将整数拆分为连续整数之和*/
int sum_judge(int n)
{
    int n1, n2 ,t;
    int flag=0;

    for(n1=1; n1<=n/2; n1++)// n1为最开头的数
    {
        for(n2=n1+1; n2<n; n2++)// n2为最末尾的数
        {
            if((n1+n2)*(n2-n1+1)/2 == n)// 用等差数列公式算和
            {
                flag = 1;
                //如果相等就输出结果
                for(t=n1; t<=n2; t++)
                    printf("%d ", t);

                printf("\n");
            }
        }
    }
    return (flag);
}

int main()
{
    int n;
    printf("请输入要拆分的正整数：");
    scanf("%d",&n);

    int i=sum_judge(n);
    printf("返回值为：%d\n",i);

    return 0;
}
