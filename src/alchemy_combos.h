#ifndef ALCHEMY_COMBOS_H
#define ALCHEMY_COMBOS_H

#include <stddef.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

/* An item ID is its PNG number: item ID 5 uses 5.png. */
typedef uint16_t AlchemyItemId;

#define ALCHEMY_INVALID_ITEM UINT16_MAX

typedef struct {
    const char *name;
} AlchemyItem;

typedef struct {
    AlchemyItemId ingredient1;
    AlchemyItemId ingredient2;
    AlchemyItemId result;
} AlchemyRecipe;

size_t alchemy_item_count(void);
size_t alchemy_item_table_size(void);
const AlchemyItem *alchemy_item(AlchemyItemId id);
AlchemyItemId alchemy_find_item(const char *name);

/* Returns the total match count and writes at most capacity result IDs. */
size_t alchemy_combine(
    AlchemyItemId first,
    AlchemyItemId second,
    AlchemyItemId *results,
    size_t capacity
);

size_t alchemy_combine_names(
    const char *first,
    const char *second,
    AlchemyItemId *results,
    size_t capacity
);

/* Returns all recipes that create result, writing at most capacity recipes. */
size_t alchemy_recipes_for(
    AlchemyItemId result,
    AlchemyRecipe *recipes,
    size_t capacity
);

#ifdef __cplusplus
}
#endif

#endif
