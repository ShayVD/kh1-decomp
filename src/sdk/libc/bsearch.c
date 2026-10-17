/* newlib stdlib/bsearch.c. sdk segment. */
#include "reent.h"

void *bsearch(const void *key, const void *base, size_t nmemb, size_t size,
              int (*compar)(const void *, const void *)) {
    void *current;
    size_t lower = 0;
    size_t upper = nmemb;
    size_t index;
    int result;

    if (nmemb == 0 || size == 0)
        return 0;

    while (lower < upper) {
        index = (lower + upper) / 2;
        current = (void *) (((char *) base) + (index * size));

        result = compar(key, current);

        if (result < 0)
            upper = index;
        else if (result > 0)
            lower = index + 1;
        else
            return current;
    }

    return 0;
}
