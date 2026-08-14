#include "pack_09.h"
#include <stdint.h>
#include <fileioc.h>

#define ALCHM09_HEADER_SIZE 0

unsigned char *ALCHM09_appvar[40] =
{
    (unsigned char*)0,
    (unsigned char*)300,
    (unsigned char*)654,
    (unsigned char*)1035,
    (unsigned char*)1236,
    (unsigned char*)1400,
    (unsigned char*)1905,
    (unsigned char*)2088,
    (unsigned char*)2275,
    (unsigned char*)2739,
    (unsigned char*)2868,
    (unsigned char*)3208,
    (unsigned char*)3588,
    (unsigned char*)3825,
    (unsigned char*)4005,
    (unsigned char*)4164,
    (unsigned char*)4363,
    (unsigned char*)4718,
    (unsigned char*)4988,
    (unsigned char*)5159,
    (unsigned char*)5740,
    (unsigned char*)6142,
    (unsigned char*)6446,
    (unsigned char*)6838,
    (unsigned char*)7285,
    (unsigned char*)7577,
    (unsigned char*)8125,
    (unsigned char*)8409,
    (unsigned char*)8712,
    (unsigned char*)8937,
    (unsigned char*)9149,
    (unsigned char*)9539,
    (unsigned char*)9898,
    (unsigned char*)10060,
    (unsigned char*)10216,
    (unsigned char*)10488,
    (unsigned char*)10896,
    (unsigned char*)11255,
    (unsigned char*)11576,
    (unsigned char*)11829,
};

unsigned char ALCHM09_init(void)
{
    uintptr_t data;
    unsigned int i;
    uint8_t appvar;

    appvar = ti_Open("ALCHM09", "r");
    if (appvar == 0)
    {
        return 0;
    }

    data = (uintptr_t)ti_GetDataPtr(appvar) - (uintptr_t)ALCHM09_appvar[0] + ALCHM09_HEADER_SIZE;
    for (i = 0; i < 40; i++)
    {
        ALCHM09_appvar[i] += data;
    }

    ti_Close(appvar);

    return 1;
}

