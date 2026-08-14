#include "pack_03.h"
#include <stdint.h>
#include <fileioc.h>

#define ALCHM03_HEADER_SIZE 0

unsigned char *ALCHM03_appvar[60] =
{
    (unsigned char*)0,
    (unsigned char*)293,
    (unsigned char*)522,
    (unsigned char*)647,
    (unsigned char*)862,
    (unsigned char*)973,
    (unsigned char*)1217,
    (unsigned char*)1431,
    (unsigned char*)1637,
    (unsigned char*)1651,
    (unsigned char*)1862,
    (unsigned char*)1876,
    (unsigned char*)2192,
    (unsigned char*)2389,
    (unsigned char*)2403,
    (unsigned char*)2538,
    (unsigned char*)2799,
    (unsigned char*)2881,
    (unsigned char*)3050,
    (unsigned char*)3298,
    (unsigned char*)3448,
    (unsigned char*)3617,
    (unsigned char*)3839,
    (unsigned char*)4075,
    (unsigned char*)4240,
    (unsigned char*)4398,
    (unsigned char*)4637,
    (unsigned char*)4911,
    (unsigned char*)5132,
    (unsigned char*)5578,
    (unsigned char*)5736,
    (unsigned char*)5964,
    (unsigned char*)6069,
    (unsigned char*)6197,
    (unsigned char*)6296,
    (unsigned char*)6421,
    (unsigned char*)6554,
    (unsigned char*)6859,
    (unsigned char*)7068,
    (unsigned char*)7179,
    (unsigned char*)7320,
    (unsigned char*)7436,
    (unsigned char*)7604,
    (unsigned char*)7739,
    (unsigned char*)7915,
    (unsigned char*)8077,
    (unsigned char*)8373,
    (unsigned char*)8487,
    (unsigned char*)8587,
    (unsigned char*)8860,
    (unsigned char*)9173,
    (unsigned char*)9332,
    (unsigned char*)9506,
    (unsigned char*)9649,
    (unsigned char*)9794,
    (unsigned char*)9858,
    (unsigned char*)10102,
    (unsigned char*)10271,
    (unsigned char*)10526,
    (unsigned char*)10627,
};

unsigned char ALCHM03_init(void)
{
    uintptr_t data;
    unsigned int i;
    uint8_t appvar;

    appvar = ti_Open("ALCHM03", "r");
    if (appvar == 0)
    {
        return 0;
    }

    data = (uintptr_t)ti_GetDataPtr(appvar) - (uintptr_t)ALCHM03_appvar[0] + ALCHM03_HEADER_SIZE;
    for (i = 0; i < 60; i++)
    {
        ALCHM03_appvar[i] += data;
    }

    ti_Close(appvar);

    return 1;
}

