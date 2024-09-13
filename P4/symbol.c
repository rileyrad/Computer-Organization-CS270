#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>

#include "Debug.h"
#include "symbol.h"

/** @file symbol.c
 * @author Riley Radici
 */

/** size of LC3 memory */
#define LC3_MEMORY_SIZE  (1 << 16)

/** Provide prototype for strdup() */
char *strdup(const char *s);

/** defines data structure used to store nodes in hash table */
typedef struct node {
  struct node* next;     /**< linked list of symbols at same index */
  int          hash;     /**< hash value - makes searching faster  */
  symbol_t     symbol;   /**< the data the user is interested in   */
} node_t;

/** defines the data structure for the hash table */
struct sym_table {
  int      capacity;    /**< length of hast_table array                  */
  int      size;        /**< number of symbols (may exceed capacity)     */
  node_t** hash_table;  /**< array of head of linked list for this index */
  char**   addr_table;  /**< look up symbols by addr                     */
};

/** djb hash - found at http://www.cse.yorku.ca/~oz/hash.html
 * tolower() call to make case insensitive.
 */

static int symbol_hash (const char* name) {
  unsigned char* str  = (unsigned char*) name;
  unsigned long  hash = 5381;
  int c;

  while ((c = *str++))
    hash = ((hash << 5) + hash) + tolower(c); /* hash * 33 + c */

  c = hash & 0x7FFFFFFF; /* keep 31 bits - avoid negative values */

  return c;
}

/** @todo implement this function

    Initializing the symbol table. Make a constructor that initializes capacity, size, address table & hash table
 */
sym_table_t* symbol_init (int capacity) {
    sym_table_t* symTable = (sym_table_t*)malloc(sizeof(sym_table_t));
    symTable -> capacity = capacity;
    symTable -> size = 0;
    symTable -> hash_table = (node_t**)calloc(capacity, sizeof(node_t*));
    symTable -> addr_table = (char**)calloc(LC3_MEMORY_SIZE, sizeof(char*));
    return symTable;
}

/** @todo implement this function

    Terminating the symbol table. Make a deconstructor to free the data structure.
 */
void symbol_term (sym_table_t* symTab) {
    symbol_reset(symTab);
    free(symTab->hash_table);
    free(symTab->addr_table);
    free(symTab);
}

/** @todo implement this function

    Use in symbol_term, resets the elements?
 */
void symbol_reset(sym_table_t* symTab) {
    node_t* currentNode; node_t* nextNode;
    for(int i = 0; i < symTab->capacity; i++){
        currentNode = symTab->hash_table[i];
        while(currentNode != NULL){
            nextNode = currentNode->next;
            free(currentNode->symbol.name);
            free(currentNode);
            currentNode = nextNode;
        }
    }
}

/** @todo implement this function

    Calculate the hash so you know where to put it. Then insert into the head of the linked list. If the entry already exists, return 0 (so use symbol search).
    Use strdup when grabbing the name.
 */
int symbol_add (sym_table_t* symTab, const char* name, int addr) {
    int hash, index;
    if(symbol_search(symTab, name, &hash, &index) == NULL){
        node_t* node = symTab->hash_table[index];
        node_t* newNode = (node_t*)calloc(3, sizeof(node_t));
        newNode->hash = hash;
        newNode->next = node;
        struct symbol newSym;
        newSym.name = strdup(name);
        newSym.addr = addr;
        newNode->symbol = newSym;
        symTab->hash_table[index] = newNode;
        symTab->addr_table[addr] = newSym.name;
        symTab->size++;
        return 1;
    }
    return 0;
}

/** @todo implement this function

    Search the hash table. Search the bucket in the hash table specified by the hash.
 */
struct node* symbol_search (sym_table_t* symTab, const char* name, int* hash, int* index) {
    *hash = symbol_hash(name);
    *index = *hash % symTab->capacity;
    node_t* current = symTab->hash_table[*index];
    while(current != NULL){
        if(*hash == current->hash){
            char* symName = current->symbol.name;
            if(strcasecmp(name, symName) == 0){
                return current;
            }
        }
        current = current->next;
    }
    return NULL;
}

/** @todo implement this function

    call symbol_search and return the symbol. symbol_search returns a node so grab the corresponding symbol.
*/
symbol_t* symbol_find_by_name (sym_table_t* symTab, const char* name) {
    int hash, index;
    node_t* node = symbol_search(symTab, name, &hash, &index);
    if(node == NULL){
        return NULL;
    }else{
        return &node->symbol;
    }
}

/** @todo implement this function

    access the index inside the address table.
 */
char* symbol_find_by_addr (sym_table_t* symTab, int addr) {
    char* name = symTab->addr_table[addr];
    if(name == NULL){
        return NULL;
    }
    else{
        return name;
    }
}

/** @todo implement this function

    for(capacity){
        while(current != null){
            (*fnc)(&current.symbol, data);
        }
    }

    Argument fnc is a function pointer, it is called by (*fnc)(&symbol, data)
 */
void symbol_iterate (sym_table_t* symTab, iterate_fnc_t fnc, void* data) {
    node_t* currentNode;
    for(int i = 0; i < symTab->capacity; i++){
        currentNode = symTab->hash_table[i];
        while(currentNode != NULL){
            symbol_t sym = currentNode->symbol;
            (*fnc)(&sym, data);
            currentNode = currentNode->next;
        }
    }
}

/** @todo implement this function

    Return size of symbol table.
 */
int symbol_size (sym_table_t* symTab) {
  return symTab->size;
}

/** @todo implement this function

    Compares names. Parameters are void pointers so they can be any type. Malloc/calloc returns void*.
*/
int compare_names (const void* vp1, const void* vp2) {
    symbol_t* sym1 = *((symbol_t**) vp1); // study qsort to understand this
    symbol_t* sym2 = *((symbol_t**) vp2);
    return strcasecmp(sym1->name, sym2->name);
}

/** @todo implement this function

    use strcasecmp to compare addresses and return the value it returns.
 */
int compare_addresses (const void* vp1, const void* vp2) {
    symbol_t* sym1 = *((symbol_t**) vp1);
    symbol_t* sym2 = *((symbol_t**) vp2);
    if(sym1->addr == sym2->addr){
        return compare_names(vp1, vp2);
    }
    return sym1->addr-sym2->addr;
}

/** @todo implement this function

    Creates a dynamic array of type symbol_t* and fils it with the symbols in the nodes that are in the hash table. Then call qsort
 */
symbol_t** symbol_order (sym_table_t* symTab, int order) {
    symbol_t** new_Sym_Table = (symbol_t**)calloc(symTab->size, sizeof(symbol_t*));
    int i = 0;
    for(int j = 0; j < symTab->capacity; j++){
        node_t* node = symTab->hash_table[j];
        while(node != NULL){
            new_Sym_Table[i] = &node->symbol;
            node = node->next;
            i += 1;
        }
    }
    if(order == NAME){
        debug("DEBUG: ENTER NAME CONDITIONAL");
        qsort(new_Sym_Table, symTab->size, sizeof(symbol_t*), compare_names);
    }
    else if(order == ADDR){
        debug("DEBUG: ENTER ADDRESS CONDITIONAL");
        qsort(new_Sym_Table, symTab->size, sizeof(symbol_t*), compare_addresses);
    }
    return new_Sym_Table;
}

