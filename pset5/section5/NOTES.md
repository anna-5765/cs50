Nodes
- custom data structures in a linked list with a value and and a pointer

typedef struct node
{
    string phrase;
    struct node *next;
}
node;

Creating a list list
1. Define the list variable as a pointer to a node
    node *list = NULL;
2. Create a new node n and allocate memory for it
    node *n = malloc(sizeof(node));
3. Define the value of the node
    n->phrase = "Hi!";
4. Set the pointer to something to create the chain
    n->next = NULL;
5. Point our list toward the first node
    list = n;
6. Create a new node
    n = malloc(sizeof(node))
    n->phrase = "Hey!";
    n->next = list;
7. Update list, a linked list is tracked by it's head value, or first node in the list
    list = n;
8. Free memory alloced
    node *ptr = list->next;
    free(list);
    list = ptr;
    ptr = list->next; ...once reach null
    - do not free list first! it will orphan the rest of the list

    Hash Table
    -the hash function makes a good or bad hash table
        - a good hash function gives you the same value for the same input
        - produces a even distribution across buckets
        - uses all buckets

