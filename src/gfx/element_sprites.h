#ifndef ELEMENT_SPRITES_H
#define ELEMENT_SPRITES_H

#include "../alchemy_combos.h"

#include <graphx.h>
#include <stdbool.h>
#include <stdint.h>

bool element_sprites_init(void);
const gfx_rletsprite_t *element_sprite(AlchemyItemId item_id);
void element_sprites_set_palette(void);

#endif
