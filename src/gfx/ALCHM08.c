#include "pack_08.h"
#include <stdint.h>
#include <fileioc.h>

#define ALCHM08_HEADER_SIZE 0

unsigned char *ALCHM08_appvar[60] =
{
    (unsigned char*)0,
    (unsigned char*)174,
    (unsigned char*)414,
    (unsigned char*)805,
    (unsigned char*)905,
    (unsigned char*)1310,
    (unsigned char*)1436,
    (unsigned char*)1791,
    (unsigned char*)1909,
    (unsigned char*)2014,
    (unsigned char*)2227,
    (unsigned char*)2614,
    (unsigned char*)3131,
    (unsigned char*)3335,
    (unsigned char*)3572,
    (unsigned char*)3859,
    (unsigned char*)4114,
    (unsigned char*)4431,
    (unsigned char*)4904,
    (unsigned char*)5333,
    (unsigned char*)5570,
    (unsigned char*)5876,
    (unsigned char*)6149,
    (unsigned char*)6675,
    (unsigned char*)6850,
    (unsigned char*)7347,
    (unsigned char*)7538,
    (unsigned char*)7864,
    (unsigned char*)8127,
    (unsigned char*)8689,
    (unsigned char*)8962,
    (unsigned char*)9183,
    (unsigned char*)9462,
    (unsigned char*)9774,
    (unsigned char*)9918,
    (unsigned char*)10044,
    (unsigned char*)10336,
    (unsigned char*)10601,
    (unsigned char*)10716,
    (unsigned char*)10895,
    (unsigned char*)11289,
    (unsigned char*)11614,
    (unsigned char*)11958,
    (unsigned char*)12092,
    (unsigned char*)12477,
    (unsigned char*)12772,
    (unsigned char*)13173,
    (unsigned char*)13517,
    (unsigned char*)13702,
    (unsigned char*)13892,
    (unsigned char*)14212,
    (unsigned char*)14437,
    (unsigned char*)14715,
    (unsigned char*)14858,
    (unsigned char*)15108,
    (unsigned char*)15575,
    (unsigned char*)15776,
    (unsigned char*)16031,
    (unsigned char*)16366,
    (unsigned char*)16634,
};

unsigned char ALCHM08_init(void)
{
    uintptr_t data;
    unsigned int i;
    uint8_t appvar;

    appvar = ti_Open("ALCHM08", "r");
    if (appvar == 0)
    {
        return 0;
    }

    data = (uintptr_t)ti_GetDataPtr(appvar) - (uintptr_t)ALCHM08_appvar[0] + ALCHM08_HEADER_SIZE;
    for (i = 0; i < 60; i++)
    {
        ALCHM08_appvar[i] += data;
    }

    ti_Close(appvar);

    return 1;
}

