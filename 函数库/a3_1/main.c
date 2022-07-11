/*冒泡排序*/
void bubble_sort(int * a, int n)
{
    int i=0,j=0;
    int t=0;

    for(i=1; i<n; i++)//循环趟数
        for(j=0; j<n-i; j++)//每趟循环
            if(a[j] > a[j+1])
            {
                t = a[j];
                a[j] = a[j+1];
                a[j+1] = t;
            }
}
/*插入排序*/
void insert_sort(int * a, int n)
{
    int i=0,j=0;
    int t=0;

    for(i=1; i<n; i++)
    {
        t=a[i];
        j=i-1;
        for(; j>=0&&a[j]>t; j--)
            a[j+1]=a[j];
        a[j+1]=t;
    }
}
/*选择排序*/
void select_sort(int * a, int n)
{
    int i=0,j=0,k=0;
    int t=0;

    for(i=0; i<n-1; i++)
    {
        k=i;//假设a[k]最小
        for(j=i+1; j<n; j++)
            if(a[j]<a[k])
            {
                t=a[k];
                a[k]=a[j];
                a[j]=t;
            }
    }
}
/*顺序查找*/
int seq_search(int *a, int cnt, int x, int front)
{
    int i=0;
    if(front==1)
        for(i=0; i<cnt; i++)
            if(a[i]==x)
                break;

    if(front==0)
        for(i=cnt-1; i>=0; i--)
            if(a[i]==x)
                break;

    if(i==cnt||i==(-1))
        return (-1);
    else
        return (i+1);
}
/*二分查找*/
int bin_search(int *a, int cnt, int x, int asc)
{
    int left=0;
    int right=cnt-1;
    int mid=0;

    if(asc==1)//升序
    {
        while (left <= right)
        {
            mid = (left + right) / 2;
            if (x > a[mid])
                left = mid + 1;
            else if (x < a[mid])
                right = mid - 1;
            else
                return (mid+1);//在数组中是第几个元素
        }
    }

    if(asc==0)//降序
    {
        while (left <= right)
        {
            mid = (left + right) / 2;
            if (x > a[mid])
                right = mid - 1;
            else if (x < a[mid])
                left = mid + 1;
            else
                return (mid+1);//在数组中是第几个元素
        }
    }
    if (left > right)
        return (-1);
}
/*将数字插入数组(数组需有空位)*/
void insertAt(int *a, int cnt, int pos, int x)
{
    int i=0;
    for(i=cnt; i>pos-1; i--)
        a[i]=a[i-1];
    a[pos-1]=x;
}
/*将数字有序插入数组(数组需有空位)*/
void insert(int *a, int cnt, int x, int asc)
{
    int i=0,j=0;

    if(asc==1)//升序
    {
        for(i=0; i<cnt; i++)
        {
            if(x <= a[i+1]&& x >= a[i])
            {
                for(j=cnt; j>i+1; j--)
                    a[j]=a[j-1];

                break;
            }
        }
        a[i+1] = x;
    }

    if(asc==0)//降序
    {
        for(i=0; i<cnt; i++)
        {
            if(x >= a[i+1]&& x <= a[i])
            {
                for(j=cnt; j>i+1; j--)
                    a[j]=a[j-1];

                break;
            }
        }
        a[i+1] = x;
    }
}
/*替换指定元素*/
int replace(int *a, int cnt, int x, int y)
{
    int i=0;
    int flag=0;

    for(i=0 ; i<cnt; i++)
    {
        if(a[i]==x)
        {
            a[i]=y;
            flag=1;
        }
    }

    if(flag==1)
        return 1;
    else
        return 0;
}
/*拼接数组*/
int* merge(int *a, int n, int *b, int m)
{
    int i=0,j=0;

    int * p =(int *)malloc(n*sizeof(int)+m*sizeof(int));

    for(i=0; i<n; i++)
        p[i]=a[i];
    for(j=0; j<m; j++)
        p[i+j]=b[j];

    free(a);
    return p;
}
