#include <stdio.h>
#include <stdlib.h>


typedef struct s_list
{
    int value;
    struct s_list *next;
} t_list;


void ft_add_front(t_list **head, t_list *new)
{
    new->next = *head;
    *head = new;
}


t_list *ft_new(int value)
{
    t_list *new = malloc(sizeof(t_list));
    if (!new)
        return (NULL);
    new->value = value;
    new->next = NULL;
    return (new);
}


t_list *ft_lst_last(t_list *head)
{
    while(head->next)
        head = head->next;
    return (head);
}

//1
//2
//3
//4




void remove_node(t_list **head, int value)
{
    t_list *tmp = *head;
    if (tmp->value == value)
    {
        *head = (*head)->next;
        free(tmp);
        return;
    }
    t_list *prev = tmp;
    tmp = tmp->next ;
    while(tmp && tmp->value != value)
    {
        prev = tmp;
        tmp = tmp->next;
    } 
    if (tmp)
    {
        prev->next = tmp->next;
        free (tmp);
    }
}

void remove_all(t_list **head)
{
    t_list *ptr;
    while (*head)
    {
        ptr = *head;
        *head = (*head)->next;
        free(ptr);
    }
}




void rra(t_list **head)
{
    t_list *prev;
    t_list *last;

    if (!head || !*head || !(*head)->next)
        return;

    prev = *head;
    while (prev->next && prev->next->next)
        prev = prev->next;
    
    last = prev->next;
    prev->next = NULL;
    last->next = *head;
    *head = last;
}


// sort_list()
// {

// }


void sort_in_tab(int *arr, int size)
{
    int i = 0;
    int tmp = 0;
    while(i < size - 1)
    {
        if (arr[i] > arr[i + 1])
        {
            tmp = arr[i];
            arr[i] = arr[i + 1];
            arr[i + 1] = tmp;
            i = 0;
        }
        else
            i++;
    }
}



//1
//2

//3
//4


void ft_swap(t_list **head)
{
    t_list *first = NULL;
    t_list *second = NULL;

    first = *head;
    second = (*head)->next;

    first->next = second->next;
    second->next = first;
    *head = second;
}


void ft_rotate(t_list **head)
{
    t_list *tmp = NULL;
    t_list *last;
    last = ft_lst_last(*head);

    tmp = *head;
    *head = (*head)->next;
    last->next = tmp;
    tmp->next = NULL;
}

int main()
{
    t_list *head = NULL;
    ft_add_front(&head,ft_new(4));
    ft_add_front(&head,ft_new(3));
    ft_add_front(&head,ft_new(2));
    ft_add_front(&head,ft_new(1));
    // ft_rotate(&head);
    // ft_swap(&head);
    // rra(&head); not check
    remove_node(&head,3); // not check
    // remove_all(&head); //check
    int i = 0;
    while(head)
    {
        printf("%d \n",head->value);
        head = head->next;
        i++;
    }

    //                        sort_int_tab
    // int arr[2] = {45,123};
    // int i = 0;
    // sort_int_tab(arr,2);
    // while(i < 2)
    // {
    //     printf("%d \n",arr[i]);
    //     i++;
    // }
}