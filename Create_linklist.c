#include<stdio.h>
#include<stdlib.h>

struct node {
    int data;
    struct node * next;
};
void Traverse(struct node *ptr){
    while(ptr != NULL){
        printf("%d\n", ptr->data);
        ptr = ptr->next;
    }
    //  printf("%d\n", ptr->data);
}
struct node *create(struct node *head){
    int data;
    printf("Enter the value you want to link\n");
    scanf("%d",&data);
    struct node *ptr = (struct node *)malloc(sizeof(struct node));
    ptr->data = data;

        struct node *p;
        if(head == NULL){
            head = ptr;
            p = head;
            head->next = NULL;
        }
        else{
            p ->next = ptr;
            p=ptr;
            p->next = NULL;

        }
        return head;

}

int main(){
    
    int i,n;
    struct node *head = NULL;
    printf("Enter the number of elements you want in the first linklist\n");
    scanf("%d", &n);
    for ( i = 0; i < n; i++)
    {
        head = create(head);
    }
    Traverse(head);
    
    int a,b;
     struct node *head1 = NULL;
    printf("Enter the number of elements you want in the second linklist\n");
    scanf("%d", &b);
    for ( a = 0; a < b; a++)
    {
        head1 = create(head1);
    }
    Traverse(head1);

}