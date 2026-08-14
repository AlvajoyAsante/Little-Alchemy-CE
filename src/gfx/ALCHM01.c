#include "pack_01.h"
#include <stdint.h>
#include <fileioc.h>

#define ALCHM01_HEADER_SIZE 0

unsigned char *ALCHM01_appvar[60] =
{
    (unsigned char*)0,
    (unsigned char*)218,
    (unsigned char*)406,
    (unsigned char*)592,
    (unsigned char*)743,
    (unsigned char*)915,
    (unsigned char*)1110,
    (unsigned char*)1271,
    (unsigned char*)1363,
    (unsigned char*)1458,
    (unsigned char*)1656,
    (unsigned char*)1870,
    (unsigned char*)2080,
    (unsigned char*)2184,
    (unsigned char*)2391,
    (unsigned char*)2529,
    (unsigned char*)2949,
    (unsigned char*)3128,
    (unsigned char*)3274,
    (unsigned char*)3479,
    (unsigned char*)3662,
    (unsigned char*)3776,
    (unsigned char*)4081,
    (unsigned char*)4319,
    (unsigned char*)4487,
    (unsigned char*)4697,
    (unsigned char*)4977,
    (unsigned char*)5225,
    (unsigned char*)5411,
    (unsigned char*)5609,
    (unsigned char*)5873,
    (unsigned char*)6070,
    (unsigned char*)6277,
    (unsigned char*)6393,
    (unsigned char*)6577,
    (unsigned char*)6716,
    (unsigned char*)6915,
    (unsigned char*)7036,
    (unsigned char*)7167,
    (unsigned char*)7391,
    (unsigned char*)7503,
    (unsigned char*)7583,
    (unsigned char*)7705,
    (unsigned char*)8059,
    (unsigned char*)8197,
    (unsigned char*)8311,
    (unsigned char*)8562,
    (unsigned char*)8695,
    (unsigned char*)8770,
    (unsigned char*)8898,
    (unsigned char*)8912,
    (unsigned char*)9062,
    (unsigned char*)9180,
    (unsigned char*)9413,
    (unsigned char*)9535,
    (unsigned char*)9738,
    (unsigned char*)9997,
    (unsigned char*)10214,
    (unsigned char*)10283,
    (unsigned char*)10417,
};

unsigned char ALCHM01_init(void)
{
    uintptr_t data;
    unsigned int i;
    uint8_t appvar;

    appvar = ti_Open("ALCHM01", "r");
    if (appvar == 0)
    {
        return 0;
    }

    data = (uintptr_t)ti_GetDataPtr(appvar) - (uintptr_t)ALCHM01_appvar[0] + ALCHM01_HEADER_SIZE;
    for (i = 0; i < 60; i++)
    {
        ALCHM01_appvar[i] += data;
    }

    ti_Close(appvar);

    return 1;
}

