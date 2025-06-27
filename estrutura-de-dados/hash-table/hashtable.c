#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define CAPACITY 5000

/* Structs */
typedef struct {
    char* key;
    void* value;
} Ht_item;

typedef struct Linked_list {
    Ht_item* item;
    struct Linked_list *next;
} Linked_list;

typedef struct {
    Ht_item** items;
    Linked_list** overflow_buckets;
    int size;
    int count;
} Hash_table;

/* Function declarations */
uint64_t hash_function(char* str);
Linked_list* allocate_list();
Linked_list* linkedlist_insert(Linked_list* list, Ht_item* item);
Ht_item* linkedlist_remove(Linked_list* list, char* key);
Linked_list** create_overflow_buckets(Hash_table* table);
Ht_item* create_item(char* key, void* value, size_t value_size);
Hash_table* create_table(int size);
void handle_collision(Hash_table* table, int index, Ht_item* item);
void ht_insert(Hash_table* table, char* key, void* value, size_t value_size);
Ht_item* ht_erase(Hash_table* table, char* key);
void* ht_search(Hash_table* table, char* key);
void destroy_item(Ht_item* item);
void destroy_table(Hash_table* table);
void destroy_linkedlist(Linked_list* list);
void destroy_overflow_buckets(Hash_table* table);

/* Function implementations */
uint64_t
hash_function(char* str)
{
    uint64_t hash = 5381;

    for (int j = 0; str[j]; j++) {
        hash = ((hash << 5) + hash) + str[j]; /* shift left */ }
    return hash % CAPACITY;
}

Linked_list*
allocate_list()
{
    Linked_list* list = malloc(sizeof(Linked_list));
    if (!list) {
        fprintf(stderr, "Collision Chain Error: failed to alloc memory\n");
        return NULL;
    }
    list->item = NULL;
    list->next = NULL;
    return list;
}

/* Collision chain functions */
Linked_list*
linkedlist_insert(Linked_list* list, Ht_item* item)
{
    if (!list) {
        Linked_list* head = allocate_list();
        head->item = item;
        head->next = NULL;
        return head;
    }
    Linked_list* node = allocate_list();
    node->item = item;
    node->next = list;
    return node;
}

Ht_item*
linkedlist_remove(Linked_list* list, char* key)
{
    if (!list) {
        return NULL;
    }
    if (!list->next) {
        Ht_item* item = list->item;
        free(list);
        return item;
    }
    Linked_list* temp = list;
    while (temp->next->item->key!= key) {
        temp = temp->next;
    }
    Linked_list* node = temp->next;
    temp->next = node->next;
    Ht_item* item = node->item;
    free(node);
    return item;
}

/* Creation functions */
Linked_list**
create_overflow_buckets(Hash_table* table)
{
    Linked_list** buckets = calloc(table->size, sizeof(Linked_list*));
    if (!buckets) {
        fprintf(stderr, "Buckets Error: failed to alloc memory\n");
        return NULL;
    }
    return buckets;
}

Ht_item*
create_item(char* key, void* value, size_t value_size)
{
    Ht_item* item = malloc(sizeof(Ht_item));
    if (!item) {
        fprintf(stderr, "Table Item Error: failed to alloc memory\n");
        return NULL;
    }
    item->key = malloc(strlen(key) + 1);
    if (!item->key) {
        fprintf(stderr, "Table Item Error: failed to alloc key\n");
        return NULL;
    }
    strcpy(item->key, key);
    item->value = malloc(value_size);
    if (!item->value) {
        fprintf(stderr, "Table Item Error: failed to alloc value\n");
        return NULL;
    }
    memcpy(item->value, value, value_size);
    return item;
}

Hash_table*
create_table(int size)
{
    Hash_table* table = malloc(sizeof(Hash_table));
    if (!table) {
        fprintf(stderr, "Hash Table Error: failed to alloc memory\n");
        return NULL;
    }
    table->size = size;
    table->overflow_buckets = create_overflow_buckets(table);
    table->count = 0;
    table->items = calloc(table->size, sizeof(Ht_item*));
    if (!table->items) {
        fprintf(stderr, "Hash Table Error: failed to alloc items\n");
    }
    return table;
}


void
handle_collision(Hash_table* table, int index, Ht_item* item)
{
    Linked_list* head = table->overflow_buckets[index];
    if (head == NULL) {
        head = allocate_list();
        head->item = item;
        table->overflow_buckets[index] = head;
        return;
    } else {
        table->overflow_buckets[index] = linkedlist_insert(head, item);
        return;
    }
}

void
ht_insert(Hash_table* table, char* key, void* value, size_t value_size)
{
    Ht_item* item = create_item(key, value, value_size);
    int index = hash_function(key);
    Ht_item* current_item = table->items[index];

    if (current_item == NULL) {
        if (table->count == table->size) {
            fprintf(stderr, "Insert Error: Hash table is full\n");
            free(item);
            return;
        }
        table->items[index] = item;
        table->count++;
    } else {
        if (memcmp(table->items[index]->value, value, value_size)) {
             return;
        } else {
            handle_collision(table, index, item);
            return;
        }
    }
}

void*
ht_search(Hash_table* table, char* key)
{
    int index = hash_function(key);
    Ht_item* item = table->items[index];
    Linked_list* head = table->overflow_buckets[index];

    if (!item) {
        fprintf(stderr, "Search Error: Item does not exist\n");
        return NULL;
    }
    if (head == NULL && strcmp(item->key, key) == 0) {
        return item->value;
    }
    while (!head) {
        if (strcmp(head->item->key, key) == 0) {
            return head->item->value;
        }
        head = head->next;
    }
    return NULL;
}

Ht_item*
ht_erase(Hash_table* table, char* key)
{
    int index = hash_function(key);
    Ht_item* item = table->items[index];
    Linked_list* head = table->overflow_buckets[index];
    if (!item) {
        fprintf(stderr, "Erase Error: Item does not exist\n");
        return NULL;
    }
    if (head == NULL && strcmp(item->key, key) == 0) {
        table->items[index] = NULL;
        table->count--;
        return item;
    }
    if (strcmp(head->item->key, key) == 0) {
        Ht_item* item = head->item;
        free(head);
        table->overflow_buckets[index] = NULL;
        return item;
    }

    Linked_list* temp = head->next;
    while (!temp) {
        if (strcmp(temp->item->key, key) == 0) {
            Ht_item* item = temp->item;
            head->next = temp->next;
            free(temp);
            return item;
        }
        head = head->next;
        temp = temp->next;
    }
    return NULL;
}


/* Destruction functions */
void
destroy_item(Ht_item* item)
{
    free(item->key);
    free(item->value);
    free(item);
}

void
destroy_table(Hash_table* table)
{
    for (int i = 0; i < table->size; i++) {
        Ht_item* item = table->items[i];
        if (item != NULL) {
            destroy_item(item);
        }
    }
    destroy_overflow_buckets(table);
    free(table->items);
    free(table);
}

void
destroy_linkedlist(Linked_list* list)
{
    Linked_list* temp;
    while (list) {
        temp = list;
        list = list->next;
        destroy_item(temp->item);
        free(temp);
    }
}

void
destroy_overflow_buckets(Hash_table* table)
{
    Linked_list** buckets = table->overflow_buckets;
    for (int i = 0; i < table->size; i++) {
        destroy_linkedlist(buckets[i]);
    }
    free(buckets);
}

void print_table(Hash_table *table)
{
    printf("\nHash Table\n-------------------\n");

    for (int i = 0; i < table -> size; i++)
    {
        if (table -> items[i])
        {
            printf("Index:%d, Key:%s, Value:%d\n", i, table->items[i]->key, *(int*)table->items[i]->value);
        }
    }

    printf("-------------------\n\n");
}

int
main(int argc, char* argv[])
{
    Hash_table* ht = create_table(CAPACITY);
    char buffer[512];
    for (int i = 2; i < 40; i *= 2) {
        scanf("%s", buffer);
        ht_insert(ht, buffer, &i, sizeof(int));
    }
    print_table(ht);
    return 0;
}
