/*
Third challenge from the book "Crafting Interpreters," chap 1.4

"To get some practice with pointers, define a doubly linked list of heap-allocated strings. Write functions to insert, find, and delete items from it. Test them."

dev: Sunny (https://github.com/Sunny02021)
date: 05/11/2026
status: unfinished
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char* data;
    size_t length;
    size_t capacity;
} HpString;

typedef struct Node {
    HpString* str;
    struct Node* next;
    struct Node* prev;
} Node;

HpString* create_string(const char *str) {
    HpString *s = malloc(sizeof(HpString));
    if (s == NULL) return NULL;

    s->length = strlen(str);
    s->capacity = s->length + 1; // + 1 for the '\0' character

    s->data = malloc(s->capacity * sizeof(char));
    if (s->data == NULL) {
        free(s);
        return NULL;
    }

    strcpy(s->data, str);

    return s;
}

void free_string(HpString *s) {
    if (s != NULL) {
        free(s->data);
        free(s);
    }
}

Node* create_node(HpString* data) {
    Node* new_node = malloc(sizeof(*new_node));
    if (new_node == NULL) return NULL;

    new_node->str = data;
    new_node->next = NULL;
    new_node->prev = NULL;

    return new_node;
}

void insert_at_first(Node** head, HpString* data) {
    Node* new_node = create_node(data);
    if (new_node == NULL) return;

    if (*head == NULL) {
        *head = new_node;
        return;
    }

    new_node->next = *head;
    (*head)->prev = new_node;
    *head = new_node;
}

void insert_at_end(Node** head, HpString* data) {
    Node* new_node = create_node(data);
    if (new_node == NULL) return;

    Node* temp = *head;
    while (temp->next != NULL) {
        temp = temp->next;
    }

    temp->next = new_node;
    new_node->prev = temp;
}

void insert_at_index(Node** head, HpString* data, int index) {
    Node* new_node = create_node(data);
    if (new_node == NULL) return;

    if (index == 0) {
        insert_at_first(head, data);
        return;
    }

    Node* temp = *head;
    for (int i = 0; temp != NULL & i < index - 1; i++) {
        temp = temp->next;
    }

    if (temp == NULL) return;

    new_node->next = temp->next;
    new_node->prev = temp;
    temp->next = new_node;
}

void free_list(Node* head) {
    Node* temp = NULL;

    while (temp != NULL) {
        temp = head;
        head = head->next;

        free(temp);
    }
}

void print(Node* head) {
    Node* temp = head;
    while (temp != NULL) {
        printf("%s -> ", temp->str->data);
        temp = temp->next;
    }
    printf("NULL\n");
}

void print_full(Node* head) {
    Node* temp = head;

    while (temp != NULL) {
        printf("Current: %s | ", temp->str->data);

        if (temp->prev != NULL) {
            printf("Prev: %s | ", temp->prev->str->data);
        } else {
            printf("Prev: NULL | ");
        }

        if (temp->next != NULL) {
            printf("Next: %s\n", temp->next->str->data);
        } else {
            printf("Next: NULL\n");
        }

        temp = temp->next;
    }
}

int main() {
    HpString *my_string1 = create_string("A");
    HpString *my_string2 = create_string("B");
    HpString *my_string3 = create_string("C");
    HpString *my_string4 = create_string("D");
    HpString *my_string5 = create_string("E");

    if (my_string1 == NULL || my_string2 == NULL) {
        free_string(my_string1);
        free_string(my_string2);
        return 1;
    }

    Node* head = NULL;

    insert_at_first(&head, my_string1);
    insert_at_first(&head, my_string2);

    //print(head);

    insert_at_end(&head, my_string3);

    //print(head);

    insert_at_index(&head, my_string4, 0);
    insert_at_index(&head, my_string5, 0);

    //print(head);
    print_full(head);

    free_list(head);
    free_string(my_string1);
    free_string(my_string2);

    return 0;
}
