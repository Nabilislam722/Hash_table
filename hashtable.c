#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SIZE 10

typedef struct person
{
    char *name;
    int age;
    struct person *next;
}person;


person *table[MAX_SIZE];

void init_table()
{
    for (int i = 0; i < MAX_SIZE; i++)
    {
        table[i] = NULL;
    }
    
}

void print_table()
{
    for (int i = 0; i < MAX_SIZE; i++)
    {
        if (table[i] == NULL)
        {
            printf("%d\t-----\n", i);
        }
        else
        {
            printf("%d\t", i);
              person* temp = table[i];
            while (temp != NULL) 
            {
                printf(" %s %d - ", temp->name, temp->age);
               
                temp = temp->next;
            }
            printf("\n"); 
        } 
    } 
}


int hash(char *name)
{
    int index = 0;
    for (int i = 0; i < strlen(name); i++)
    {
        index = index + name[i];
    }

    index = index % MAX_SIZE;
    return index;  
}

void insert_table(char *name, int age)
{
    person *new_person = malloc(sizeof(person));
    if (new_person == NULL)
    {
        return; // Handle allocation failure 
    }

    int index = hash(name);

    new_person->name = name;
    new_person->age = age;
    new_person->next = table[index];

    table[index] = new_person;   
}

char *lookup_inTable(char *name)
{
    int index = hash(name);
     char *noMatch = "NOT FOUND!";
     if (table[index] == NULL)
     {
        return noMatch;
     }

     person *temp = table[index];
     while (temp != NULL)
     {
        if (strcmp(temp->name, name) == 0)
        {
            char *result = malloc(strlen("Person Found: ") + strlen(temp->name));
            if (result == NULL)
            {
                return NULL; // MEmory allocation fail
            }
            
            sprintf(result, "Person Found: %s", temp->name);
            return result;          
        }
        temp = temp->next;
     }
     
     
    return noMatch;
}

char *hash_table_delete(char *name)
{
    int index = hash(name);
    char *notFound = "Not found";
    char* Found = "Deleted";
    person *previous = NULL;
    person *temp = table[index];

    while (table[index] != NULL && strncmp(name, temp->name, MAX_SIZE) != 0)
    {
       previous = temp;
       temp = temp->next;
    }
    if (temp == NULL) return notFound;
    if (previous == NULL)
    {
      table[index] = temp->next;
    }
    else
    {
      previous->next = temp ->next;
    }
    return Found;
    
}



int main()
{
     
     init_table();
     print_table();
    
    printf("\n---END---\n");

    insert_table("Nabil", 18);
    insert_table("Nayem", 22);
    insert_table("Labon", 19);
    insert_table("Rakibul", 19);
    insert_table("Ferdous", 20);
    
    print_table();

    printf("Is this Person on the table?\n %s\n", lookup_inTable("Nabil"));

    printf("%s\n", hash_table_delete("Ferdous"));
    print_table();
}
