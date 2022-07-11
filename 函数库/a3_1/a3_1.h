#ifndef _sort_
#define _sort_
void bubble_sort(int * a, int n);//冒泡排序
void insert_sort(int * a, int n);//插入排序
void select_sort(int * a, int n);//选择排序
int seq_search(int *a, int cnt, int x, int front);//顺序查找
int bin_search(int *a, int cnt,int x, int asc); //二分查找
void insertAt(int *a, int cnt, int pos, int x);//插入数组
void insert(int *a, int cnt, int x, int asc);//将数字有序插入数组
int replace(int *a, int cnt, int x, int y);//替换指定元素
int* merge(int *a, int n, int *b, int m); //拼接数组
#endif // _sort_


