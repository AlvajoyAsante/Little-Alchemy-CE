#include "pack_04.h"
#include <stdint.h>
#include <fileioc.h>

#define ALCHM04_HEADER_SIZE 0

unsigned char *ALCHM04_appvar[60] =
{
    (unsigned char*)0,
    (unsigned char*)179,
    (unsigned char*)492,
    (unsigned char*)628,
    (unsigned char*)774,
    (unsigned char*)951,
    (unsigned char*)1175,
    (unsigned char*)1438,
    (unsigned char*)1637,
    (unsigned char*)1789,
    (unsigned char*)1934,
    (unsigned char*)2189,
    (unsigned char*)2294,
    (unsigned char*)2697,
    (unsigned char*)2925,
    (unsigned char*)3226,
    (unsigned char*)3491,
    (unsigned char*)3820,
    (unsigned char*)4026,
    (unsigned char*)4460,
    (unsigned char*)4626,
    (unsigned char*)4795,
    (unsigned char*)5080,
    (unsigned char*)5300,
    (unsigned char*)5457,
    (unsigned char*)5662,
    (unsigned char*)5796,
    (unsigned char*)6184,
    (unsigned char*)6325,
    (unsigned char*)6593,
    (unsigned char*)6759,
    (unsigned char*)7055,
    (unsigned char*)7277,
    (unsigned char*)7583,
    (unsigned char*)7835,
    (unsigned char*)8167,
    (unsigned char*)8280,
    (unsigned char*)8455,
    (unsigned char*)8660,
    (unsigned char*)8988,
    (unsigned char*)9253,
    (unsigned char*)9712,
    (unsigned char*)9889,
    (unsigned char*)10169,
    (unsigned char*)10416,
    (unsigned char*)10588,
    (unsigned char*)10969,
    (unsigned char*)11142,
    (unsigned char*)11534,
    (unsigned char*)11744,
    (unsigned char*)11911,
    (unsigned char*)12148,
    (unsigned char*)12321,
    (unsigned char*)12501,
    (unsigned char*)12801,
    (unsigned char*)13097,
    (unsigned char*)13190,
    (unsigned char*)13417,
    (unsigned char*)13581,
    (unsigned char*)13772,
};

unsigned char ALCHM04_init(void)
{
    uintptr_t data;
    unsigned int i;
    uint8_t appvar;

    appvar = ti_Open("ALCHM04", "r");
    if (appvar == 0)
    {
        return 0;
    }

    data = (uintptr_t)ti_GetDataPtr(appvar) - (uintptr_t)ALCHM04_appvar[0] + ALCHM04_HEADER_SIZE;
    for (i = 0; i < 60; i++)
    {
        ALCHM04_appvar[i] += data;
    }

    ti_Close(appvar);

    return 1;
}

