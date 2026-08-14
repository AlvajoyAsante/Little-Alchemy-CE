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
    (unsigned char*)1168,
    (unsigned char*)1422,
    (unsigned char*)1621,
    (unsigned char*)1773,
    (unsigned char*)1921,
    (unsigned char*)2176,
    (unsigned char*)2281,
    (unsigned char*)2671,
    (unsigned char*)2899,
    (unsigned char*)3200,
    (unsigned char*)3465,
    (unsigned char*)3798,
    (unsigned char*)4004,
    (unsigned char*)4438,
    (unsigned char*)4604,
    (unsigned char*)4780,
    (unsigned char*)5069,
    (unsigned char*)5289,
    (unsigned char*)5441,
    (unsigned char*)5646,
    (unsigned char*)5746,
    (unsigned char*)6134,
    (unsigned char*)6275,
    (unsigned char*)6545,
    (unsigned char*)6711,
    (unsigned char*)7007,
    (unsigned char*)7229,
    (unsigned char*)7535,
    (unsigned char*)7792,
    (unsigned char*)8124,
    (unsigned char*)8237,
    (unsigned char*)8412,
    (unsigned char*)8617,
    (unsigned char*)8945,
    (unsigned char*)9209,
    (unsigned char*)9668,
    (unsigned char*)9845,
    (unsigned char*)10131,
    (unsigned char*)10379,
    (unsigned char*)10551,
    (unsigned char*)10933,
    (unsigned char*)11106,
    (unsigned char*)11498,
    (unsigned char*)11699,
    (unsigned char*)11866,
    (unsigned char*)12104,
    (unsigned char*)12277,
    (unsigned char*)12459,
    (unsigned char*)12759,
    (unsigned char*)13055,
    (unsigned char*)13148,
    (unsigned char*)13375,
    (unsigned char*)13536,
    (unsigned char*)13727,
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

