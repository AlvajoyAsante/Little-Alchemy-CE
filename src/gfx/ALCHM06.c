#include "pack_06.h"
#include <stdint.h>
#include <fileioc.h>

#define ALCHM06_HEADER_SIZE 0

unsigned char *ALCHM06_appvar[60] =
{
    (unsigned char*)0,
    (unsigned char*)142,
    (unsigned char*)259,
    (unsigned char*)367,
    (unsigned char*)506,
    (unsigned char*)689,
    (unsigned char*)856,
    (unsigned char*)969,
    (unsigned char*)1059,
    (unsigned char*)1256,
    (unsigned char*)1430,
    (unsigned char*)1549,
    (unsigned char*)1777,
    (unsigned char*)1949,
    (unsigned char*)2129,
    (unsigned char*)2530,
    (unsigned char*)2664,
    (unsigned char*)2755,
    (unsigned char*)2936,
    (unsigned char*)3213,
    (unsigned char*)3519,
    (unsigned char*)3741,
    (unsigned char*)3909,
    (unsigned char*)4091,
    (unsigned char*)4334,
    (unsigned char*)4447,
    (unsigned char*)4582,
    (unsigned char*)4921,
    (unsigned char*)5095,
    (unsigned char*)5326,
    (unsigned char*)5640,
    (unsigned char*)5945,
    (unsigned char*)6158,
    (unsigned char*)6356,
    (unsigned char*)6627,
    (unsigned char*)7044,
    (unsigned char*)7301,
    (unsigned char*)7554,
    (unsigned char*)7753,
    (unsigned char*)8103,
    (unsigned char*)8305,
    (unsigned char*)8483,
    (unsigned char*)8855,
    (unsigned char*)9078,
    (unsigned char*)9183,
    (unsigned char*)9516,
    (unsigned char*)9725,
    (unsigned char*)9850,
    (unsigned char*)10096,
    (unsigned char*)10238,
    (unsigned char*)10456,
    (unsigned char*)10580,
    (unsigned char*)10845,
    (unsigned char*)10991,
    (unsigned char*)11245,
    (unsigned char*)11402,
    (unsigned char*)11680,
    (unsigned char*)12241,
    (unsigned char*)12657,
    (unsigned char*)12693,
};

unsigned char ALCHM06_init(void)
{
    uintptr_t data;
    unsigned int i;
    uint8_t appvar;

    appvar = ti_Open("ALCHM06", "r");
    if (appvar == 0)
    {
        return 0;
    }

    data = (uintptr_t)ti_GetDataPtr(appvar) - (uintptr_t)ALCHM06_appvar[0] + ALCHM06_HEADER_SIZE;
    for (i = 0; i < 60; i++)
    {
        ALCHM06_appvar[i] += data;
    }

    ti_Close(appvar);

    return 1;
}

