#include "pack_07.h"
#include <stdint.h>
#include <fileioc.h>

#define ALCHM07_HEADER_SIZE 0

unsigned char *ALCHM07_appvar[60] =
{
    (unsigned char*)0,
    (unsigned char*)260,
    (unsigned char*)429,
    (unsigned char*)652,
    (unsigned char*)908,
    (unsigned char*)1099,
    (unsigned char*)1105,
    (unsigned char*)1127,
    (unsigned char*)1431,
    (unsigned char*)1711,
    (unsigned char*)1953,
    (unsigned char*)2253,
    (unsigned char*)2402,
    (unsigned char*)2802,
    (unsigned char*)3097,
    (unsigned char*)3251,
    (unsigned char*)3609,
    (unsigned char*)3730,
    (unsigned char*)4036,
    (unsigned char*)4249,
    (unsigned char*)4415,
    (unsigned char*)4538,
    (unsigned char*)4866,
    (unsigned char*)4987,
    (unsigned char*)5159,
    (unsigned char*)5447,
    (unsigned char*)5628,
    (unsigned char*)5852,
    (unsigned char*)6095,
    (unsigned char*)6558,
    (unsigned char*)6901,
    (unsigned char*)7133,
    (unsigned char*)7378,
    (unsigned char*)7536,
    (unsigned char*)7898,
    (unsigned char*)8187,
    (unsigned char*)8414,
    (unsigned char*)8734,
    (unsigned char*)9084,
    (unsigned char*)9245,
    (unsigned char*)9455,
    (unsigned char*)9624,
    (unsigned char*)9753,
    (unsigned char*)10018,
    (unsigned char*)10274,
    (unsigned char*)10519,
    (unsigned char*)10648,
    (unsigned char*)10841,
    (unsigned char*)11101,
    (unsigned char*)11291,
    (unsigned char*)11526,
    (unsigned char*)11824,
    (unsigned char*)12117,
    (unsigned char*)12293,
    (unsigned char*)12615,
    (unsigned char*)12908,
    (unsigned char*)13141,
    (unsigned char*)13495,
    (unsigned char*)13667,
    (unsigned char*)13888,
};

unsigned char ALCHM07_init(void)
{
    uintptr_t data;
    unsigned int i;
    uint8_t appvar;

    appvar = ti_Open("ALCHM07", "r");
    if (appvar == 0)
    {
        return 0;
    }

    data = (uintptr_t)ti_GetDataPtr(appvar) - (uintptr_t)ALCHM07_appvar[0] + ALCHM07_HEADER_SIZE;
    for (i = 0; i < 60; i++)
    {
        ALCHM07_appvar[i] += data;
    }

    ti_Close(appvar);

    return 1;
}

