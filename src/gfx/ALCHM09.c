#include "pack_09.h"
#include <stdint.h>
#include <fileioc.h>

#define ALCHM09_HEADER_SIZE 0

unsigned char *ALCHM09_appvar[40] =
{
    (unsigned char*)0,
    (unsigned char*)309,
    (unsigned char*)676,
    (unsigned char*)1075,
    (unsigned char*)1284,
    (unsigned char*)1454,
    (unsigned char*)1968,
    (unsigned char*)2210,
    (unsigned char*)2402,
    (unsigned char*)2870,
    (unsigned char*)3035,
    (unsigned char*)3381,
    (unsigned char*)3774,
    (unsigned char*)4012,
    (unsigned char*)4208,
    (unsigned char*)4387,
    (unsigned char*)4606,
    (unsigned char*)4967,
    (unsigned char*)5252,
    (unsigned char*)5421,
    (unsigned char*)6015,
    (unsigned char*)6440,
    (unsigned char*)6744,
    (unsigned char*)7144,
    (unsigned char*)7595,
    (unsigned char*)7934,
    (unsigned char*)8487,
    (unsigned char*)8791,
    (unsigned char*)9097,
    (unsigned char*)9316,
    (unsigned char*)9543,
    (unsigned char*)9945,
    (unsigned char*)10323,
    (unsigned char*)10490,
    (unsigned char*)10666,
    (unsigned char*)10938,
    (unsigned char*)11386,
    (unsigned char*)11757,
    (unsigned char*)12121,
    (unsigned char*)12391,
};

unsigned char ALCHM09_init(void)
{
    uintptr_t data;
    unsigned int i;
    uint8_t appvar;

    appvar = ti_Open("ALCHM09", "r");
    if (appvar == 0)
    {
        return 0;
    }

    data = (uintptr_t)ti_GetDataPtr(appvar) - (uintptr_t)ALCHM09_appvar[0] + ALCHM09_HEADER_SIZE;
    for (i = 0; i < 40; i++)
    {
        ALCHM09_appvar[i] += data;
    }

    ti_Close(appvar);

    return 1;
}

