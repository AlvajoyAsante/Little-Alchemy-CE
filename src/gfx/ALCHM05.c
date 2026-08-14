#include "pack_05.h"
#include <stdint.h>
#include <fileioc.h>

#define ALCHM05_HEADER_SIZE 0

unsigned char *ALCHM05_appvar[60] =
{
    (unsigned char*)0,
    (unsigned char*)121,
    (unsigned char*)305,
    (unsigned char*)533,
    (unsigned char*)898,
    (unsigned char*)1156,
    (unsigned char*)1354,
    (unsigned char*)1625,
    (unsigned char*)1825,
    (unsigned char*)1961,
    (unsigned char*)2259,
    (unsigned char*)2500,
    (unsigned char*)2595,
    (unsigned char*)2837,
    (unsigned char*)3107,
    (unsigned char*)3288,
    (unsigned char*)3822,
    (unsigned char*)4245,
    (unsigned char*)4564,
    (unsigned char*)4733,
    (unsigned char*)4903,
    (unsigned char*)5073,
    (unsigned char*)5257,
    (unsigned char*)5494,
    (unsigned char*)5842,
    (unsigned char*)5940,
    (unsigned char*)6046,
    (unsigned char*)6196,
    (unsigned char*)6519,
    (unsigned char*)6761,
    (unsigned char*)6967,
    (unsigned char*)7133,
    (unsigned char*)7319,
    (unsigned char*)7524,
    (unsigned char*)7708,
    (unsigned char*)7859,
    (unsigned char*)7957,
    (unsigned char*)8113,
    (unsigned char*)8319,
    (unsigned char*)8607,
    (unsigned char*)9026,
    (unsigned char*)9300,
    (unsigned char*)9479,
    (unsigned char*)9748,
    (unsigned char*)9841,
    (unsigned char*)10016,
    (unsigned char*)10217,
    (unsigned char*)10399,
    (unsigned char*)10743,
    (unsigned char*)10969,
    (unsigned char*)11407,
    (unsigned char*)11778,
    (unsigned char*)12032,
    (unsigned char*)12362,
    (unsigned char*)12654,
    (unsigned char*)12863,
    (unsigned char*)13127,
    (unsigned char*)13385,
    (unsigned char*)13679,
    (unsigned char*)13831,
};

unsigned char ALCHM05_init(void)
{
    uintptr_t data;
    unsigned int i;
    uint8_t appvar;

    appvar = ti_Open("ALCHM05", "r");
    if (appvar == 0)
    {
        return 0;
    }

    data = (uintptr_t)ti_GetDataPtr(appvar) - (uintptr_t)ALCHM05_appvar[0] + ALCHM05_HEADER_SIZE;
    for (i = 0; i < 60; i++)
    {
        ALCHM05_appvar[i] += data;
    }

    ti_Close(appvar);

    return 1;
}

