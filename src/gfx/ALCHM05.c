#include "pack_05.h"
#include <stdint.h>
#include <fileioc.h>

#define ALCHM05_HEADER_SIZE 0

unsigned char *ALCHM05_appvar[60] =
{
    (unsigned char*)0,
    (unsigned char*)121,
    (unsigned char*)328,
    (unsigned char*)555,
    (unsigned char*)920,
    (unsigned char*)1178,
    (unsigned char*)1376,
    (unsigned char*)1649,
    (unsigned char*)1845,
    (unsigned char*)1981,
    (unsigned char*)2294,
    (unsigned char*)2535,
    (unsigned char*)2629,
    (unsigned char*)2871,
    (unsigned char*)3141,
    (unsigned char*)3333,
    (unsigned char*)3863,
    (unsigned char*)4293,
    (unsigned char*)4612,
    (unsigned char*)4781,
    (unsigned char*)4951,
    (unsigned char*)5127,
    (unsigned char*)5311,
    (unsigned char*)5547,
    (unsigned char*)5895,
    (unsigned char*)5993,
    (unsigned char*)6103,
    (unsigned char*)6253,
    (unsigned char*)6576,
    (unsigned char*)6812,
    (unsigned char*)7014,
    (unsigned char*)7169,
    (unsigned char*)7355,
    (unsigned char*)7563,
    (unsigned char*)7744,
    (unsigned char*)7895,
    (unsigned char*)7995,
    (unsigned char*)8151,
    (unsigned char*)8354,
    (unsigned char*)8642,
    (unsigned char*)9061,
    (unsigned char*)9335,
    (unsigned char*)9512,
    (unsigned char*)9778,
    (unsigned char*)9871,
    (unsigned char*)10046,
    (unsigned char*)10247,
    (unsigned char*)10429,
    (unsigned char*)10775,
    (unsigned char*)11001,
    (unsigned char*)11439,
    (unsigned char*)11814,
    (unsigned char*)12068,
    (unsigned char*)12398,
    (unsigned char*)12690,
    (unsigned char*)12905,
    (unsigned char*)13177,
    (unsigned char*)13435,
    (unsigned char*)13732,
    (unsigned char*)13884,
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

