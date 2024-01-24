#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_BUFFER 1024

typedef struct CityTreeNode* CityTreePointer;
struct CityTreeNode {
    char name[MAX_BUFFER];
    int population;
    CityTreePointer left;
    CityTreePointer right;
};

struct StateList;
typedef struct StateList* StateListPointer;
typedef struct StateList {
    char stateName[MAX_BUFFER];
    CityTreePointer cityTreeRoot;
    StateListPointer next;
} StateListNode;

CityTreePointer CreateCityTreeRoot();
StateListPointer CreateStateList();
int IspisStateList(StateListPointer);
int InsertInStateList(StateListPointer, StateListPointer);
StateListPointer CreateStateListNode(char[]);
int ReadStateDataFromFile(char[], StateListPointer);
int ReadCityDataFromFile(StateListPointer, char[]);
int IspisInorderCityTree(CityTreePointer);
CityTreePointer CreateCityTreeNode(char[], int);
StateListPointer FindStateInList(StateListPointer, char[]);
CityTreePointer InsertInCityTree(CityTreePointer, char[], int);
int IspisCitiesLargerThan(CityTreePointer, int);
int UserMenu(StateListPointer);

int main() {
    StateListPointer stateList = CreateStateList();
    ReadStateDataFromFile("drzave.txt", stateList);
    // IspisStateList(stateList);
    UserMenu(stateList);
    return 0;
}

CityTreePointer CreateCityTreeRoot() {
    CityTreePointer root = NULL;
    root = malloc(sizeof(struct CityTreeNode));

    if (!root) {
        printf("Memory allocation error!\n");
        return NULL;
    }

    strcpy(root->name, "");
    root->left = NULL;
    root->right = NULL;
    root->population = 0;

    return root;
}

int InsertInStateList(StateListPointer newStateNode, StateListPointer head) {
    if (head->next == NULL) {
        head->next = newStateNode;
        newStateNode->next = NULL;
    } else {
        while (head->next != NULL && (strcmp(head->next->stateName, newStateNode->stateName) < 0))
            head = head->next;

        newStateNode->next = head->next;
        head->next = newStateNode;
    }

    return 0;
}

StateListPointer CreateStateListNode(char stateName[]) {
    StateListPointer newStateNode = NULL;
    newStateNode = (StateListPointer)malloc(sizeof(struct StateList));

    if (!newStateNode) {
        printf("Memory allocation error!\n");
        return NULL;
    }

    strcpy(newStateNode->stateName, stateName);
    newStateNode->next = NULL;
    newStateNode->cityTreeRoot = CreateCityTreeRoot();

    return newStateNode;
}

int ReadStateDataFromFile(char stateFile[], StateListPointer stateList) {
    FILE* fp = NULL;
    char stateName[MAX_BUFFER] = {0};
    char cityFile[MAX_BUFFER] = {0};
    StateListPointer newStateNode = NULL;
    StateListPointer current = stateList->next;

    newStateNode = (StateListPointer)malloc(sizeof(struct StateList));

    if (!newStateNode) {
        printf("Memory allocation error!\n");
        return 0;
    }

    fp = fopen(stateFile, "r");

    if (!fp) {
        printf("Unable to open file %s!\n", stateFile);
        return EXIT_FAILURE;
    }

    while (!feof(fp)) {
        fscanf(fp, "%[^,],%s\n", stateName, cityFile);
        newStateNode = CreateStateListNode(stateName);
        InsertInStateList(newStateNode, stateList);
        ReadCityDataFromFile(newStateNode, cityFile);
    }

    fclose(fp);
    return 0;
}

int ReadCityDataFromFile(StateListPointer stateNode, char cityFile[]) {
    FILE* fp = NULL;
    char cityName[MAX_BUFFER] = {0};
    int population = 0;
    CityTreePointer newCityNode = NULL;
    CityTreePointer root = stateNode->cityTreeRoot;

    fp = fopen(cityFile, "r");

    if (!fp) {
        printf("Unable to open file %s!\n", cityFile);
        return EXIT_FAILURE;
    }

    while (!feof(fp)) {
        fscanf(fp, "%[^,],%d\n", cityName, &population);
        newCityNode = CreateCityTreeRoot();
        newCityNode = InsertInCityTree(root, cityName, population);
    }

    fclose(fp);

    return 0;
}

int IspisInorderCityTree(CityTreePointer root) {
    if (root == NULL)
        return 0;

    IspisInorderCityTree(root->left);
    if (root->population != 0)
        printf("    %s (%d population)\n", root->name, root->population);
    IspisInorderCityTree(root->right);
    return 0;
}

CityTreePointer CreateCityTreeNode(char cityName[], int population) {
    CityTreePointer newCityNode = NULL;
    newCityNode = (CityTreePointer)malloc(sizeof(struct CityTreeNode));

    if (!newCityNode) {
        printf("Memory allocation error!\n");
        return NULL;
    }

    strcpy(newCityNode->name, cityName);
    newCityNode->population = population;
    newCityNode->left = NULL;
    newCityNode->right = NULL;

    return newCityNode;
}

StateListPointer FindStateInList(StateListPointer stateList, char stateName[]) {
    StateListPointer current = NULL;
    current = (StateListPointer)malloc(sizeof(struct StateList));

    if (!current) {
        printf("Memory allocation error!\n");
        return NULL;
    }

    current = stateList->next;

    while (current->next != NULL && (strcmp(current->next->stateName, stateName)))
        current = current->next;

    if ((current->next == NULL || strcmp(stateName, current->next->stateName))) {
        return NULL;
    }

    current = current->next;
    return current;
}

int UserMenu(StateListPointer stateList) {
    int choice = 0;
    int population = 0;
    char stateName[MAX_BUFFER] = {0};
    char cityName[MAX_BUFFER] = {0};
    StateListPointer currentStateNode = NULL;
    CityTreePointer currentCityTree = NULL;
    CityTreePointer tempCityNode = NULL;

    currentStateNode = (StateListPointer)malloc(sizeof(struct StateList));

    if (!currentStateNode) {
        printf("Memory allocation error!\n");
        return EXIT_FAILURE;
    }

    currentCityTree = (CityTreePointer)malloc(sizeof(struct CityTreeNode));

    if (!currentCityTree) {
        printf("Memory allocation error!\n");
        return EXIT_FAILURE;
    }

    tempCityNode = (CityTreePointer)malloc(sizeof(struct CityTreeNode));

    if (!tempCityNode) {
        printf("Memory allocation error!\n");
        return EXIT_FAILURE;
    }

    while (1) {
        printf("---------------------------------\n");
        printf("1 - Start the program\n");
        printf("2 - Exit the program\n");
        printf("---------------------------------\n");
        printf("Choice:");
        scanf(" %d", &choice);

        if (choice == 1) {
            printf("Enter the name of the state: ");
            scanf(" %s", stateName);
            currentStateNode = FindStateInList(stateList, stateName);

            if (!currentStateNode) {
                printf("Data for the entered state does not exist!\n");
            } else {
                printf("Data for the state %s has been found!\n", currentStateNode->stateName);
                printf("Cities of the state are:\n");
                IspisInorderCityTree(currentStateNode->cityTreeRoot);

                tempCityNode = currentStateNode->cityTreeRoot;
                printf("\nEnter the number of inhabitants in the city: ");
                scanf(" %d", &population);
                printf("Cities with more than %d inhabitants in the state %s are:\n", population, stateName);
                IspisCitiesLargerThan(tempCityNode, population);
            }
            printf("\n");
        } else if (choice == 2) {
            printf("Successful program exit!\n\n\n");
            break;
        } else {
            printf("Input error, possible choices are 1 and 2!\n\n");
        }
    }

    return 0;
}

CityTreePointer InsertInCityTree(CityTreePointer root, char cityName[], int population) {
    if (root == NULL) {
        root = (CityTreePointer)malloc(sizeof(struct CityTreeNode));
        strcpy(root->name, cityName);
        root->population = population;
        root->left = NULL;
        root->right = NULL;
    }

    if (root->population > population)
        root->left = InsertInCityTree(root->left, cityName, population);
    else if (root->population < population)
        root->right = InsertInCityTree(root->right, cityName, population);
    else if (strcmp(root->name, cityName) > 0)
        root->left = InsertInCityTree(root->left, cityName, population);
    else if (strcmp(root->name, cityName) < 0)
        root->right = InsertInCityTree(root->right, cityName, population);

    return root;
}

StateListPointer CreateStateList() {
    StateListPointer head = NULL;
    head = (StateListPointer)malloc(sizeof(struct StateList));

    if (!head) {
        printf("Memory allocation error!\n");
        return NULL;
    }

    strcpy(head->stateName, "");
    head->next = NULL;
    head->cityTreeRoot = NULL;

    return head;
}

int IspisStateList(StateListPointer stateList) {
    StateListPointer current = stateList->next;

    while (current->next != NULL) {
        current = current->next;
        printf("State: %s \nCities:\n", current->stateName);
        IspisInorderCityTree(current->cityTreeRoot);
        printf("\n");
    }

    return 0;
}

int IspisCitiesLargerThan(CityTreePointer current, int population) {
    if (current == NULL) {
        return 0;
    }

    IspisCitiesLargerThan(current->left, population);

    if (current->population >= population)
        printf("    %s (%d population)\n", current->name, current->population);

    IspisCitiesLargerThan(current->right, population);
    return 0;
}
