#include "pack_01.h"
#include <stdint.h>
#include <fileioc.h>

#define ALCHM01_HEADER_SIZE 0

unsigned char *ALCHM01_appvar[60] =
{
    (unsigned char*)0,
    (unsigned char*)234,
    (unsigned char*)435,
    (unsigned char*)643,
    (unsigned char*)830,
    (unsigned char*)1014,
    (unsigned char*)1210,
    (unsigned char*)1389,
    (unsigned char*)1491,
    (unsigned char*)1600,
    (unsigned char*)1803,
    (unsigned char*)2033,
    (unsigned char*)2261,
    (unsigned char*)2386,
    (unsigned char*)2612,
    (unsigned char*)2766,
    (unsigned char*)3210,
    (unsigned char*)3380,
    (unsigned char*)3526,
    (unsigned char*)3738,
    (unsigned char*)3962,
    (unsigned char*)4086,
    (unsigned char*)4446,
    (unsigned char*)4712,
    (unsigned char*)4895,
    (unsigned char*)5112,
    (unsigned char*)5388,
    (unsigned char*)5660,
    (unsigned char*)5863,
    (unsigned char*)6066,
    (unsigned char*)6331,
    (unsigned char*)6542,
    (unsigned char*)6759,
    (unsigned char*)6890,
    (unsigned char*)7078,
    (unsigned char*)7222,
    (unsigned char*)7433,
    (unsigned char*)7560,
    (unsigned char*)7700,
    (unsigned char*)7923,
    (unsigned char*)8041,
    (unsigned char*)8125,
    (unsigned char*)8284,
    (unsigned char*)8680,
    (unsigned char*)8853,
    (unsigned char*)8976,
    (unsigned char*)9208,
    (unsigned char*)9355,
    (unsigned char*)9441,
    (unsigned char*)9584,
    (unsigned char*)9590,
    (unsigned char*)9751,
    (unsigned char*)9870,
    (unsigned char*)10134,
    (unsigned char*)10262,
    (unsigned char*)10473,
    (unsigned char*)10732,
    (unsigned char*)10935,
    (unsigned char*)11005,
    (unsigned char*)11164,
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

