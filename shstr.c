/**
 * @file
 * This is a simple shared strings package with a simple interface.
 * @author Kjetil T. Homme, Oslo 1992.
 */

#include "shstr.h"
#include "string.h"

/** Hash table to store our strings. */
static shared_string *hash_table[TABLESIZE];

static struct statistics {
    uint32_t calls;
    uint32_t hashed;
    uint32_t strcmps;
    uint32_t search;
    uint32_t linked;
} add_stats, add_ref_stats, free_stats, find_stats, hash_stats;

TOOLKIT_API(DEPENDS(logger));

TOOLKIT_INIT_FUNC(shstr)
{
    memset(hash_table, 0, TABLESIZE * sizeof(shared_string *));
}
TOOLKIT_INIT_FUNC_FINISH

TOOLKIT_DEINIT_FUNC(shstr)
{
    size_t i;
    shared_string *ss;

    for (i = 0; i < TABLESIZE; i++) {
        for (ss = hash_table[i]; ss != NULL; ss = ss->next) {
            LOG(ERROR, "String still has %lu references: '%s'",
                    ss->refcount & ~TOPBIT, ss->string);
        }
    }
}
TOOLKIT_DEINIT_FUNC_FINISH

/**
 * Hashing function used by the shared string library.
 *
 * @param str
 * String to hash.
 * @return
 * Hash of string, suitable for use in ::hash_table.
 */
static unsigned long
hashstr (const char *str)
{
    unsigned long hash = 0;
    int i = 0;
    unsigned int rot = 0;
    const char *p;

    TOOLKIT_PROTECT();

    hash_stats.calls++;

    for (p = str; i < MAXSTRING && *p; p++, i++) {
        hash ^= (unsigned long) *p << rot;
        rot += 2;

        if (rot >= (sizeof(unsigned long) - sizeof(char)) * CHAR_BIT) {
            rot = 0;
        }
    }

    return (hash % TABLESIZE);
}

/**
 * Allocates and initializes a new shared_string structure, containing
 * the string str.
 * @param str
 * String to store.
 * @return
 * Sharing structure.
 */
static shared_string *
new_shared_string (const char *str)
{
    shared_string *ss;
    size_t n = strlen(str);

    TOOLKIT_PROTECT();

    /* Allocate room for a struct which can hold str. Note
     * that some bytes for the string are already allocated in the
     * shared_string struct. */
    ss = emalloc(sizeof(shared_string) - PADDING + n + 1);

    ss->u.previous = NULL;
    ss->next = NULL;
    ss->refcount = 1;
    memcpy(ss->string, str, n);
    ss->string[n] = '\0';

    return ss;
}

shstr *
add_string (const char *str)
{
    shared_string *ss;
    unsigned long ind;

    TOOLKIT_PROTECT();

    add_stats.calls++;

    ind = hashstr(str);
    ss = hash_table[ind];

    /* Is there an entry for that hash? */
    if (ss) {
        /* Simple case first: See if the first pointer matches. */
        if (str != ss->string) {
            add_stats.strcmps++;

            if (strcmp(ss->string, str)) {
                /* Apparently, a string with the same hash value has this
                 * slot. We must see in the list if "str" has been
                 * registered earlier. */
                while (ss->next) {
                    add_stats.search++;
                    ss = ss->next;

                    if (ss->string != str) {
                        add_stats.strcmps++;

                        if (strcmp(ss->string, str)) {
                            /* This wasn't the right string... */
                            continue;
                        }
                    }

                    /* We found an entry for this string. Fix the
                     * refcount and exit. */
                    add_stats.linked++;
                    ++(ss->refcount);

                    return ss->string;
                }

                /* There are no occurrences of this string in the hash table. */
                {
                    shared_string *new_ss;

                    add_stats.linked++;
                    new_ss = new_shared_string(str);
                    ss->next = new_ss;
                    new_ss->u.previous = ss;

                    return new_ss->string;
                }
            }

            /* Fall through. */
        }

        add_stats.hashed++;
        ++(ss->refcount);

        return ss->string;
    } else {
        /* The string isn't registered, and the slot is empty. */

        add_stats.hashed++;
        hash_table[ind] = new_shared_string(str);

        /* One bit in refcount is used to keep track of the union. */
        hash_table[ind]->refcount |= TOPBIT;
        hash_table[ind]->u.array = &(hash_table[ind]);

        return hash_table[ind]->string;
    }
}

shstr *
add_refcount (shstr *str)
{
    TOOLKIT_PROTECT();
    add_ref_stats.calls++;
    ++(SS(str)->refcount);

    return str;
}

int
query_refcount (shstr *str)
{
    TOOLKIT_PROTECT();
    return SS(str)->refcount & ~TOPBIT;
}

shstr *
find_string (const char *str)
{
    shared_string *ss;
    unsigned long ind;

    TOOLKIT_PROTECT();

    find_stats.calls++;

    ind = hashstr(str);
    ss = hash_table[ind];

    /* Is there an entry for that hash? */
    if (ss) {
        /* Simple case first: Is the first string the right one? */
        find_stats.strcmps++;

        if (!strcmp(ss->string, str)) {
            find_stats.hashed++;
            return ss->string;
        } else {
            /* Recurse through the linked list, if there's one. */
            while (ss->next) {
                find_stats.search++;
                find_stats.strcmps++;
                ss = ss->next;

                if (!strcmp(ss->string, str)) {
                    find_stats.linked++;
                    return ss->string;
                }
            }

            /* No match. Fall through. */
        }
    }

    return NULL;
}

void
free_string_shared (shstr *str)
{
    shared_string *ss;

    TOOLKIT_PROTECT();

    free_stats.calls++;
    ss = SS(str);

    if ((--ss->refcount & ~TOPBIT) == 0) {
        /* Remove this entry. */
        if (ss->refcount & TOPBIT) {
            /* We must put a new value into the hash_table[]. */
            if (ss->next) {
                *(ss->u.array) = ss->next;
                ss->next->u.array = ss->u.array;
                ss->next->refcount |= TOPBIT;
            } else {
                *(ss->u.array) = NULL;
            }

            efree(ss);
        } else {
            /* Relink and free this struct. */
            if (ss->next) {
                ss->next->u.previous = ss->u.previous;
            }

            ss->u.previous->next = ss->next;
            efree(ss);
        }
    }
}

void
shstr_stats (char *buf, size_t size)
{
    snprintfcat(buf, size, "\n=== SHSTR ===\n");
    snprintfcat(buf, size, "\n%-13s %6s %6s %6s %6s %6s\n", "", "calls",
            "hashed", "strcmp", "search", "linked");
    snprintfcat(buf, size, "%-13s %6d %6d %6d %6d %6d\n", "add_string:",
            add_stats.calls, add_stats.hashed, add_stats.strcmps,
            add_stats.search, add_stats.linked);
    snprintfcat(buf, size, "%-13s %6d\n", "add_refcount:", add_ref_stats.calls);
    snprintfcat(buf, size, "%-13s %6d\n", "free_string:", free_stats.calls);
    snprintfcat(buf, size, "%-13s %6d %6d %6d %6d %6d\n", "find_string:",
            find_stats.calls, find_stats.hashed, find_stats.strcmps,
            find_stats.search, find_stats.linked);
    snprintfcat(buf, size, "%-13s %6d\n", "hashstr:", hash_stats.calls);
}
