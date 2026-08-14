#include "pack_06.h"
#include <stdint.h>
#include <fileioc.h>

#define ALCHM06_HEADER_SIZE 0

unsigned char *ALCHM06_appvar[60] =
{
    (unsigned char*)0,
    (unsigned char*)152,
    (unsigned char*)279,
    (unsigned char*)397,
    (unsigned char*)543,
    (unsigned char*)747,
    (unsigned char*)925,
    (unsigned char*)1053,
    (unsigned char*)1140,
    (unsigned char*)1342,
    (unsigned char*)1548,
    (unsigned char*)1699,
    (unsigned char*)1960,
    (unsigned char*)2126,
    (unsigned char*)2315,
    (unsigned char*)2731,
    (unsigned char*)2877,
    (unsigned char*)2967,
    (unsigned char*)3175,
    (unsigned char*)3484,
    (unsigned char*)3797,
    (unsigned char*)4027,
    (unsigned char*)4196,
    (unsigned char*)4377,
    (unsigned char*)4635,
    (unsigned char*)4797,
    (unsigned char*)4938,
    (unsigned char*)5304,
    (unsigned char*)5499,
    (unsigned char*)5779,
    (unsigned char*)6130,
    (unsigned char*)6457,
    (unsigned char*)6673,
    (unsigned char*)6873,
    (unsigned char*)7162,
    (unsigned char*)7596,
    (unsigned char*)7859,
    (unsigned char*)8124,
    (unsigned char*)8322,
    (unsigned char*)8680,
    (unsigned char*)8893,
    (unsigned char*)9076,
    (unsigned char*)9464,
    (unsigned char*)9686,
    (unsigned char*)9820,
    (unsigned char*)10164,
    (unsigned char*)10381,
    (unsigned char*)10497,
    (unsigned char*)10764,
    (unsigned char*)10899,
    (unsigned char*)11138,
    (unsigned char*)11271,
    (unsigned char*)11550,
    (unsigned char*)11714,
    (unsigned char*)11985,
    (unsigned char*)12135,
    (unsigned char*)12428,
    (unsigned char*)12970,
    (unsigned char*)13408,
    (unsigned char*)13443,
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

