#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>

int main()
{
	int shuliang, m, a[10], i, b[10];
	int sum = 0, max = 0;
	printf("���������ָ���");
	scanf("%d", &shuliang);
	printf("���������֣��ո����");
	for (i = 0; i < shuliang; i++)
	{

		scanf("%d", &a[i]);
	}
	b[0] = a[0];
	for (i = 0; i < shuliang; i++)
	{
		if (b[i - 1] > 0)//b[i-1]�ж���һ�������Ƿ�Ϊ����
		{
			b[i] = b[i - 1] + a[i];
		}
		else
			b[i] = a[i];
		if (b[i] > max)
		{
			max = b[i];
		}
	}
	printf("%d", max);
	system("pause");
}