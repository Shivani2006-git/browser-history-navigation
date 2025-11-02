#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node{
    char url[100];
    struct Node *prev;
    struct Node *next;
}Node;

Node *current = NULL;

Node* createNode(char *url){
    Node *newNode = (Node*)malloc(sizeof(Node));
    strcpy(newNode->url, url);
    newNode->prev = NULL;
    newNode->next = NULL;
    return newNode;
}

void visit(char *url){
    Node *newPage = createNode(url);

    // first page
    if(current == NULL){
        current = newPage;
        return;
    }

    // delete forward history
    Node *temp = current->next;
    while(temp){
        Node *temp2 = temp;
        temp = temp->next;
        free(temp2);
    }

    current->next = newPage;
    newPage->prev = current;
    current = newPage;
}

void back(){
    if(current && current->prev){
        current = current->prev;
        printf("Back to: %s\n", current->url);
    } else {
        printf("No back history!\n");
    }
}

void forward(){
    if(current && current->next){
        current = current->next;
        printf("Forward to: %s\n", current->url);
    } else {
        printf("No forward history!\n");
    }
}

void showCurrent(){
    if(current) printf("Current page: %s\n", current->url);
    else printf("No pages visited yet!\n");
}

void showHistory(){
    Node *temp = current;
    while(temp && temp->prev) temp = temp->prev; // go to first

    printf("\nFull History:\n");
    while(temp){
        if(temp==current) printf(" --> %s  (CURRENT)\n", temp->url);
        else printf("     %s\n", temp->url);
        temp = temp->next;
    }
}

int main(){
    int choice;
    char url[100];

    while(1){
        printf("\n--- Browser History Menu ---\n");
        printf("1. Visit new page\n");
        printf("2. Back\n");
        printf("3. Forward\n");
        printf("4. Show Current Page\n");
        printf("5. Show History\n");
        printf("0. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch(choice){
        case 1:
            printf("Enter URL: ");
            scanf("%s", url);
            visit(url);
            break;
        case 2:
            back();
            break;
        case 3:
            forward();
            break;
        case 4:
            showCurrent();
            break;
        case 5:
            showHistory();
            break;
        case 0:
            exit(0);
        default:
            printf("Invalid choice\n");
        }
    }
    return 0;
}