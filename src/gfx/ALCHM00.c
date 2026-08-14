#include "pack_00.h"
#include <stdint.h>
#include <fileioc.h>

#define ALCHM00_HEADER_SIZE 0

unsigned char *ALCHM00_appvar[61] =
{
    (unsigned char*)0,
    (unsigned char*)512,
    (unsigned char*)698,
    (unsigned char*)872,
    (unsigned char*)1104,
    (unsigned char*)1156,
    (unsigned char*)1495,
    (unsigned char*)1647,
    (unsigned char*)1822,
    (unsigned char*)2103,
    (unsigned char*)2229,
    (unsigned char*)2361,
    (unsigned char*)2482,
    (unsigned char*)2641,
    (unsigned char*)2843,
    (unsigned char*)3015,
    (unsigned char*)3178,
    (unsigned char*)3354,
    (unsigned char*)3482,
    (unsigned char*)3651,
    (unsigned char*)3864,
    (unsigned char*)3870,
    (unsigned char*)4264,
    (unsigned char*)4376,
    (unsigned char*)4512,
    (unsigned char*)4686,
    (unsigned char*)4746,
    (unsigned char*)4981,
    (unsigned char*)5168,
    (unsigned char*)5303,
    (unsigned char*)5465,
    (unsigned char*)5593,
    (unsigned char*)5827,
    (unsigned char*)5935,
    (unsigned char*)6119,
    (unsigned char*)6125,
    (unsigned char*)6202,
    (unsigned char*)6413,
    (unsigned char*)6843,
    (unsigned char*)7081,
    (unsigned char*)7215,
    (unsigned char*)7423,
    (unsigned char*)7782,
    (unsigned char*)8003,
    (unsigned char*)8176,
    (unsigned char*)8470,
    (unsigned char*)8562,
    (unsigned char*)8664,
    (unsigned char*)8845,
    (unsigned char*)9137,
    (unsigned char*)9298,
    (unsigned char*)9404,
    (unsigned char*)9481,
    (unsigned char*)9589,
    (unsigned char*)9748,
    (unsigned char*)9959,
    (unsigned char*)10164,
    (unsigned char*)10311,
    (unsigned char*)10472,
    (unsigned char*)10739,
    (unsigned char*)11058,
};

unsigned char ALCHM00_init(void)
{
    uintptr_t data;
    unsigned int i;
    uint8_t appvar;

    appvar = ti_Open("ALCHM00", "r");
    if (appvar == 0)
    {
        return 0;
    }

    data = (uintptr_t)ti_GetDataPtr(appvar) - (uintptr_t)ALCHM00_appvar[0] + ALCHM00_HEADER_SIZE;
    for (i = 0; i < 61; i++)
    {
        ALCHM00_appvar[i] += data;
    }

    ti_Close(appvar);

    return 1;
}

