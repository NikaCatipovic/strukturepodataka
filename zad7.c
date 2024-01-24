#include<stdio.h>
#include<string.h>
#include<stdlib.h>

struct Directory;
typedef struct Directory Dir;
typedef struct Directory *Node;

struct SimStack;
typedef struct SimStack *Stack;

struct Directory
{
    char name[10];
    Node next;
    Node child;
};

struct SimStack
{
    Node element;
    Stack next;
};

void displayDir(Node, char *);
Node exitDir(Node, char *, Stack);
Node enterDir(Node, char *, char *, Stack);
void createDir(Node, char *);
void push(Stack, Node);
Node pop(Stack);

void main()
{
    char command[20], name[10], action[10], path[100];
    char *i, *j;
    Dir root;
    struct SimStack stack;

    Node currentDir = &root;
    stack.next = NULL;

    printf("Enter the name of the root directory: ");
    scanf(" %s", root.name);
    root.child = NULL;
    root.next = NULL;

    path[0] = 0;
    strcat(path, root.name);
    strcat(path, ":/\\");

    system("cls");

    printf("Enter command:");
    printf("\n\tdir");
    printf("\n\tcd..");
    printf("\n\tcd directory_name");
    printf("\n\tmk directory_name");
    printf("\n\n\texit - to quit");
    printf("\n\n\t");

    fgets(command, 20, stdin);

    while (strcmp(action, "exit") != 0)
    {
        printf("\n\n\t%s", path);

        memset(name, 0, sizeof(name));
        memset(action, 0, sizeof(action));

        fgets(command, 20, stdin);

        i = strchr(command, ' ');

        if (NULL == i)
        {
            strncpy(action, command, sizeof(command));
            j = strchr(action, 10);
            *j = 0;
        }
        else
        {
            strncpy(action, command, i - command);
            action[i - command] = 0;
            strcpy(name, i + 1);
        }

        if (strcmp(action, "dir") == 0)
            displayDir(currentDir, path);
        else if (strcmp(action, "cd..") == 0)
            currentDir = exitDir(currentDir, path, &stack);
        else if (strcmp(action, "cd") == 0)
        {
            if (name[0] == 0)
                printf("Syntax error in command!\n Should be: cd directory_name");
            else
                currentDir = enterDir(currentDir, name, path, &stack);
        }
        else if (strcmp(action, "mk") == 0)
        {
            if (name[0] == 0)
                printf("Syntax error in command!\n Should be: mk directory_name");
            else
                createDir(currentDir, name);
        }
        else if (strcmp(action, "exit") != 0)
            printf("\nInvalid input!!\n");
    }
}

void displayDir(Node node, char *path)
{
    int count = 0;
    printf("\nDirectory of %s", path);

    node = node->child;

    while (node != NULL)
    {
        printf("\n\t\t %s", node->name);
        node = node->next;
        count++;
    }

    printf("\n\t\t %d Dir(s)", count);
}

Node exitDir(Node node, char *path, Stack stack)
{
    Node temp;
    char *a;

    temp = pop(stack);

    if (NULL == temp)
    {
        printf("We are in the root directory!\nCannot exit from it!");
        return node;
    }
    else
    {
        a = strrchr(path, '\\');
        *a = 0;

        a = strrchr(path, '\\');
        *(a + 1) = 0;

        return temp;
    }
}

Node enterDir(Node node, char *name, char *path, Stack stack)
{
    Node temp = node->child;
    char *a;

    while (temp != NULL && strcmp(temp->name, name) != 0)
        temp = temp->next;

    if (NULL == temp)
        printf("\nNo sub-directory with that name!");
    else
    {
        push(stack, node);
        strcat(path, temp->name);
        a = strchr(path, 10);
        *a = '\\';
        return temp;
    }

    return node;
}

void createDir(Node node, char *name)
{
    Node newDir;

    newDir = (Node)malloc(sizeof(Dir));
    newDir->child = NULL;
    newDir->next = NULL;

    strcpy(newDir->name, name);

    if (NULL == newDir)
        printf("\nMemory allocation error!!");
    else
    {
        if (NULL == node->child)
            node->child = newDir;
        else
        {
            newDir->next = node->child;
            node->child = newDir;
        }
    }
}

void push(Stack stack, Node node)
{
    Stack newStack;

    newStack = (Stack)malloc(sizeof(struct SimStack));

    if (newStack == NULL)
        printf("\nMemory allocation error!!");
    else
    {
        newStack->element = node;
        newStack->next = stack->next;

        stack->next = newStack;
    }
}

Node pop(Stack stack)
{
    Node node;
    Stack temp;

    if (NULL == stack->next)
        return NULL;
    else
    {
        node = stack->next->element;
        temp = stack->next;
        stack->next = temp->next;

        free(temp);
        return node;
    }
}