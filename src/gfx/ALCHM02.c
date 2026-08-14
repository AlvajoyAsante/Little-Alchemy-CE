#include "pack_02.h"
#include <stdint.h>
#include <fileioc.h>

#define ALCHM02_HEADER_SIZE 0

unsigned char *ALCHM02_appvar[60] =
{
    (unsigned char*)0,
    (unsigned char*)224,
    (unsigned char*)242,
    (unsigned char*)398,
    (unsigned char*)746,
    (unsigned char*)876,
    (unsigned char*)1168,
    (unsigned char*)1370,
    (unsigned char*)1660,
    (unsigned char*)1855,
    (unsigned char*)2019,
    (unsigned char*)2211,
    (unsigned char*)2443,
    (unsigned char*)2673,
    (unsigned char*)2679,
    (unsigned char*)2808,
    (unsigned char*)2991,
    (unsigned char*)3189,
    (unsigned char*)3356,
    (unsigned char*)3529,
    (unsigned char*)3745,
    (unsigned char*)4010,
    (unsigned char*)4091,
    (unsigned char*)4479,
    (unsigned char*)4635,
    (unsigned char*)4765,
    (unsigned char*)4979,
    (unsigned char*)5169,
    (unsigned char*)5375,
    (unsigned char*)5530,
    (unsigned char*)5783,
    (unsigned char*)6063,
    (unsigned char*)6247,
    (unsigned char*)6583,
    (unsigned char*)6797,
    (unsigned char*)6957,
    (unsigned char*)7013,
    (unsigned char*)7375,
    (unsigned char*)7689,
    (unsigned char*)7970,
    (unsigned char*)8279,
    (unsigned char*)8473,
    (unsigned char*)8831,
    (unsigned char*)8992,
    (unsigned char*)9209,
    (unsigned char*)9419,
    (unsigned char*)9576,
    (unsigned char*)9866,
    (unsigned char*)10047,
    (unsigned char*)10229,
    (unsigned char*)10357,
    (unsigned char*)10599,
    (unsigned char*)10741,
    (unsigned char*)10933,
    (unsigned char*)11169,
    (unsigned char*)11406,
    (unsigned char*)11579,
    (unsigned char*)11767,
    (unsigned char*)12178,
    (unsigned char*)12456,
};

unsigned char ALCHM02_init(void)
{
    uintptr_t data;
    unsigned int i;
    uint8_t appvar;

    appvar = ti_Open("ALCHM02", "r");
    if (appvar == 0)
    {
        return 0;
    }

    data = (uintptr_t)ti_GetDataPtr(appvar) - (uintptr_t)ALCHM02_appvar[0] + ALCHM02_HEADER_SIZE;
    for (i = 0; i < 60; i++)
    {
        ALCHM02_appvar[i] += data;
    }

    ti_Close(appvar);

    return 1;
}

