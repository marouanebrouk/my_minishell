#include <stdio.h>
#include <stdlib.h>


typedef struct s_list
{
    int value;
    void *next;
} t_list;

int main()
{

t_list node1;
t_list node2;
t_list node3;
t_list node4;
t_list *head = &node1;

node1.value = 20;
node1.next = &node2;

node2.value = 30;
node2.next = &node3;

node3.value = 40;
node3.next = &node4;

node4.value = 50;
node4.next = NULL;

printf("size = %ld \n",sizeof(void *));
printf("size = %ld \n",sizeof(t_list *));

while(head)
{
    printf("%d ",(*head).value);
    head = (*head).next;
}
}