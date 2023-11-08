
#include <stdio.h>
#include <stdlib.h>

struct Node
{
    int data;
    int priority;
    struct Node *next;
};

// Priority Queue structure
struct PriorityQueue
{
    struct Node *front;
};

// Initialize an empty priority queue
struct PriorityQueue *initPriorityQueue()
{
    struct PriorityQueue *pq = (struct PriorityQueue *)malloc(sizeof(struct PriorityQueue));
    pq->front = NULL;
    return pq;
}

// Check if the priority queue is empty
int isEmpty(struct PriorityQueue *pq)
{
    return pq->front == NULL;
}

// Enqueue an element with priority into the priority queue
//with 1 as the highest priority
void enqueue(struct PriorityQueue *pq, int data, int priority)
{
    struct Node *newNode = (struct Node *)malloc(sizeof(struct Node));
    newNode->data = data;
    newNode->priority = priority;
    newNode->next = NULL;

    if (isEmpty(pq) || priority < pq->front->priority)
    {
        newNode->next = pq->front;
        pq->front = newNode;
    }
    else
    {
        struct Node *current = pq->front;
        while (current->next != NULL && priority >= current->next->priority)
        {
            current = current->next;
        }
        newNode->next = current->next;
        current->next = newNode;
    }
}

// Dequeue the highest priority element from the priority queue
int dequeue(struct PriorityQueue *pq)
{
    if (isEmpty(pq))
    {
        printf("Priority Queue is empty.\n");
        return -1;
    }
    struct Node *temp = pq->front;
    int data = temp->data;
    pq->front = pq->front->next;
    free(temp);
    return data;
}

// Display the elements and priorities in the priority queue
void display(struct PriorityQueue *pq)
{
    struct Node *current = pq->front;
    while (current != NULL)
    {
        printf("Data: %d, Priority: %d\n", current->data, current->priority);
        current = current->next;
    }
}

int main()
{
    struct PriorityQueue *pq = initPriorityQueue();
    enqueue(pq, 10, 3);
    enqueue(pq, 20, 4);
    enqueue(pq, 30, 3);
    enqueue(pq, 70, 1);

    printf("Priority Queue:\n");
    display(pq);

    printf("\nDequeue:\n");
    // while (!isEmpty(pq)) {
    printf("%d\n", dequeue(pq));
    // }

    return 0;
}
