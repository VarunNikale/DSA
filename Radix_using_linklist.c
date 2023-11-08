
//  the time complexity of the provided radix sort implementation 
// is O(d * (n + b)), where d is the maximum number of digits, n is the
//  number of input elements, and b is the base (in this case, 10).

#include <stdio.h>//Q2 
#include <stdlib.h>
#include <math.h>

struct Node {
    int data;
    struct Node* next;
};

void append(struct Node** head_ref, int data) {
    struct Node* new_node = (struct Node*)malloc(sizeof(struct Node));
    new_node->data = data;
    new_node->next = NULL;

    if (*head_ref == NULL) {
        *head_ref = new_node;
    } 
    else {
        struct Node* current = *head_ref;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = new_node;
    }
}

int getMaxDigits(struct Node* head) {
    int maxDigits = 0;
    struct Node* current = head;
    while (current != NULL) {
        int digits = 0;
        int num = current->data;
        while (num > 0) {
            num /= 10;
            digits++;
        }
        if (digits > maxDigits) {
            maxDigits = digits;
        }
        current = current->next;
    }
    return maxDigits;
}


void printList(struct Node* head) {
    struct Node* current = head;
    while (current != NULL) {
        printf("%d ", current->data);
        current = current->next;
    }
    printf("\n");
}

void radixSort(struct Node** head_ref) {
    int maxDigits = getMaxDigits(*head_ref);

    for (int digitPosition = 1; digitPosition <= maxDigits; digitPosition++) {
        struct Node* buckets[10] = {NULL};
        struct Node* end_buckets[10] = {NULL};

       // Distribute elements into buckets based on the current digit
        struct Node* current = *head_ref;
        while (current != NULL) {
            int digit = (current->data / (int)pow(10, digitPosition - 1)) % 10;
            if (buckets[digit] == NULL) {
                buckets[digit] = current;
                end_buckets[digit] = current;
            } else {
                end_buckets[digit]->next = current;
                end_buckets[digit] = current;
            }
            current = current->next;
        }

        // Collect elements from buckets back into the linked list
        struct Node* new_head = NULL;
        struct Node* new_tail = NULL;
        for (int i = 0; i < 10; i++) {
            if (buckets[i] != NULL) {
                if (new_head == NULL) {
                    new_head = buckets[i]; 
                    new_tail = end_buckets[i];
                } else {
                    new_tail->next = buckets[i];
                    new_tail = end_buckets[i];
                }
            }
        }

        new_tail->next = NULL;
        *head_ref = new_head;
    }
}


int main() {
    struct Node* head = NULL;
    append(&head, 136);
    append(&head, 487);
    append(&head, 358);
    append(&head, 570);
    append(&head, 247);
    append(&head, 598);
    append(&head, 639);
    append(&head, 205);
    append(&head, 609);

    printf("Original Linked List: ");
    printList(head);

    radixSort(&head);

    printf("Sorted Linked List: ");
    printList(head);

    return 0;
}
