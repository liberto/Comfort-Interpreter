/* This section is the stuff for the hash tables used for storing definitions. 
 * All of this is heavily based on lexeme-token-hash-tables.c.
 */

/* This struct pairs the function definition (which is just a quotation node)
 * with the name of the function.
 */
typedef struct 
{
  char *name;
  node function;
} name_def_pair;

/* This is the linked-list structure for our chained hash table. */
typedef struct pair_list 
{
  name_def_pair node;
  struct pair_list *next;
} *pair_list;

/* A hash table for storing quotations corresponding to user-defined functions.
 * This is kept very basic to save time; the size is a constant 150. May 
 * change this later, especially if we have time to move bits and pieces to
 * separate header files.
 */
typedef struct definition_hash_table
{  
  pair_list *table;
} def_ht;

/* The global hash table used for all hash purposes. */
def_ht global_def_ht;

/* Allocates a definition hash table with 150 spaces and returns it. */
def_ht make_def_ht()
{
  def_ht out = (def_ht) malloc(sizeof(struct definition_hash_table));
  out->table = (pair_list*) malloc(150 * sizeof(struct pair_list));
  for (unsigned int index = 0; index < 150; index ++)
    out->table[i] = NULL;
  return out;
}

/* This uses the djb2 hash function from http://www.cse.yorku.ca/~oz/hash.html 
 * to hash strings. Since the table size is always 150, this then mods by 150
 * before returning the result.
 */
unsigned long hash(char *str)
{
  unsigned long hash = 5381;
  int c;
  while (c = *str++)
    hash = ((hash << 5) + hash) + c; /* hash * 33 + c */
  return hash % 150;
}

node def_ht_get(char *def_name)
{
  pair_list match = global_def_ht->table[hash(def_name)];
  while (match)
  {
    if (strcmp(match->node.name, def_name) == 0)
      return match->node;
    match = match->next;
  }
  return (node) NULL;
}

void def_ht_put(char *def_name, node quot)
{
  unsigned int slot = hash(def_name);
  if (global_def_ht->table[slot] == NULL)
  {
    pair_list new_list = (pair_list) malloc(sizeof(struct pair_list));
    new_list->name_def_pair.name = def_name;
    new_list->name_def_pair.function = quot;
    new_list->next = NULL;
    global_def_ht->table[slot] = new_list;
    return;
  }

  pair_list matcher = global_def_ht->table[slot];
  while(matcher && strcmp(matcher->name_def_pair.name, def_name) != 0)
    matcher = matcher->next;
  if(matcher)
    matcher->name_def_pair.function = quot;
  else
  {
    pair_list new_list = (pair_list) malloc(sizeof(struct pair_list));
    new_list->name_def_pair.name = def_name;
    new_list->name_def_pair.function = quot;
    new_list->next = table[slot];
    global_def_ht->table[slot] = new_list;
  }    
}
