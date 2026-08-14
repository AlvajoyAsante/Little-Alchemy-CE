#include "pack_02.h"
#include <stdint.h>
#include <fileioc.h>

#define ALCHM02_HEADER_SIZE 0

unsigned char *ALCHM02_appvar[60] =
{
    (unsigned char*)0,
    (unsigned char*)224,
    (unsigned char*)242,
    (unsigned char*)388,
    (unsigned char*)736,
    (unsigned char*)866,
    (unsigned char*)1158,
    (unsigned char*)1356,
    (unsigned char*)1628,
    (unsigned char*)1826,
    (unsigned char*)1989,
    (unsigned char*)2196,
    (unsigned char*)2428,
    (unsigned char*)2661,
    (unsigned char*)2667,
    (unsigned char*)2789,
    (unsigned char*)2972,
    (unsigned char*)3170,
    (unsigned char*)3337,
    (unsigned char*)3512,
    (unsigned char*)3728,
    (unsigned char*)3994,
    (unsigned char*)4075,
    (unsigned char*)4464,
    (unsigned char*)4620,
    (unsigned char*)4750,
    (unsigned char*)4964,
    (unsigned char*)5154,
    (unsigned char*)5360,
    (unsigned char*)5514,
    (unsigned char*)5767,
    (unsigned char*)6046,
    (unsigned char*)6229,
    (unsigned char*)6565,
    (unsigned char*)6775,
    (unsigned char*)6935,
    (unsigned char*)6994,
    (unsigned char*)7356,
    (unsigned char*)7670,
    (unsigned char*)7951,
    (unsigned char*)8273,
    (unsigned char*)8467,
    (unsigned char*)8825,
    (unsigned char*)8972,
    (unsigned char*)9180,
    (unsigned char*)9390,
    (unsigned char*)9547,
    (unsigned char*)9832,
    (unsigned char*)10009,
    (unsigned char*)10198,
    (unsigned char*)10326,
    (unsigned char*)10567,
    (unsigned char*)10725,
    (unsigned char*)10917,
    (unsigned char*)11153,
    (unsigned char*)11388,
    (unsigned char*)11561,
    (unsigned char*)11749,
    (unsigned char*)12160,
    (unsigned char*)12430,
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

