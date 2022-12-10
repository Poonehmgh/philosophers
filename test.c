
#include<stdio.h>
#include<stdlib.h>
typedef struct a
{
    int i;
    char *s;
} t_test;

void fun(t_test *data)
{
    data->i = 5;
}

int main()
{
    t_test *data = malloc(sizeof(data) * 2);
    data->i = 3;
    fun(data + 1);
    printf("%d\n", data[1].i);
}
