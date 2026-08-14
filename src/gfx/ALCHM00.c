#include "pack_00.h"
#include <stdint.h>
#include <fileioc.h>

#define ALCHM00_HEADER_SIZE 0

unsigned char *ALCHM00_appvar[61] =
{
    (unsigned char*)0,
    (unsigned char*)512,
    (unsigned char*)695,
    (unsigned char*)844,
    (unsigned char*)1064,
    (unsigned char*)1121,
    (unsigned char*)1467,
    (unsigned char*)1607,
    (unsigned char*)1760,
    (unsigned char*)2012,
    (unsigned char*)2126,
    (unsigned char*)2245,
    (unsigned char*)2357,
    (unsigned char*)2508,
    (unsigned char*)2696,
    (unsigned char*)2858,
    (unsigned char*)3012,
    (unsigned char*)3174,
    (unsigned char*)3297,
    (unsigned char*)3451,
    (unsigned char*)3657,
    (unsigned char*)3671,
    (unsigned char*)4046,
    (unsigned char*)4162,
    (unsigned char*)4290,
    (unsigned char*)4460,
    (unsigned char*)4519,
    (unsigned char*)4724,
    (unsigned char*)4905,
    (unsigned char*)5026,
    (unsigned char*)5176,
    (unsigned char*)5304,
    (unsigned char*)5528,
    (unsigned char*)5631,
    (unsigned char*)5814,
    (unsigned char*)5828,
    (unsigned char*)5902,
    (unsigned char*)6123,
    (unsigned char*)6567,
    (unsigned char*)6781,
    (unsigned char*)6908,
    (unsigned char*)7123,
    (unsigned char*)7474,
    (unsigned char*)7667,
    (unsigned char*)7832,
    (unsigned char*)8099,
    (unsigned char*)8193,
    (unsigned char*)8282,
    (unsigned char*)8446,
    (unsigned char*)8727,
    (unsigned char*)8884,
    (unsigned char*)8981,
    (unsigned char*)9060,
    (unsigned char*)9161,
    (unsigned char*)9303,
    (unsigned char*)9481,
    (unsigned char*)9687,
    (unsigned char*)9824,
    (unsigned char*)9970,
    (unsigned char*)10207,
    (unsigned char*)10504,
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

