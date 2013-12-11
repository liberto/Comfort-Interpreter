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
def_ht make_def_ht();

unsigned long hash(char *str);
node def_ht_get(char *def_name);
void def_ht_put(char *def_name, node quot);
