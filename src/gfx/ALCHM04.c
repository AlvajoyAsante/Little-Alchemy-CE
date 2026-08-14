#include "pack_04.h"
#include <stdint.h>
#include <fileioc.h>

#define ALCHM04_HEADER_SIZE 0

unsigned char *ALCHM04_appvar[60] =
{
    (unsigned char*)0,
    (unsigned char*)172,
    (unsigned char*)460,
    (unsigned char*)601,
    (unsigned char*)719,
    (unsigned char*)907,
    (unsigned char*)1100,
    (unsigned char*)1362,
    (unsigned char*)1548,
    (unsigned char*)1711,
    (unsigned char*)1846,
    (unsigned char*)2086,
    (unsigned char*)2171,
    (unsigned char*)2526,
    (unsigned char*)2755,
    (unsigned char*)3048,
    (unsigned char*)3310,
    (unsigned char*)3624,
    (unsigned char*)3809,
    (unsigned char*)4260,
    (unsigned char*)4433,
    (unsigned char*)4581,
    (unsigned char*)4851,
    (unsigned char*)5064,
    (unsigned char*)5206,
    (unsigned char*)5374,
    (unsigned char*)5465,
    (unsigned char*)5842,
    (unsigned char*)5968,
    (unsigned char*)6218,
    (unsigned char*)6389,
    (unsigned char*)6674,
    (unsigned char*)6878,
    (unsigned char*)7167,
    (unsigned char*)7398,
    (unsigned char*)7717,
    (unsigned char*)7828,
    (unsigned char*)7994,
    (unsigned char*)8182,
    (unsigned char*)8498,
    (unsigned char*)8760,
    (unsigned char*)9204,
    (unsigned char*)9394,
    (unsigned char*)9658,
    (unsigned char*)9878,
    (unsigned char*)10048,
    (unsigned char*)10427,
    (unsigned char*)10597,
    (unsigned char*)11003,
    (unsigned char*)11203,
    (unsigned char*)11366,
    (unsigned char*)11584,
    (unsigned char*)11763,
    (unsigned char*)11951,
    (unsigned char*)12246,
    (unsigned char*)12539,
    (unsigned char*)12632,
    (unsigned char*)12851,
    (unsigned char*)13003,
    (unsigned char*)13181,
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

