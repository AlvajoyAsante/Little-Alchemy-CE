#include "pack_03.h"
#include <stdint.h>
#include <fileioc.h>

#define ALCHM03_HEADER_SIZE 0

unsigned char *ALCHM03_appvar[60] =
{
    (unsigned char*)0,
    (unsigned char*)301,
    (unsigned char*)556,
    (unsigned char*)695,
    (unsigned char*)905,
    (unsigned char*)1024,
    (unsigned char*)1295,
    (unsigned char*)1531,
    (unsigned char*)1751,
    (unsigned char*)1757,
    (unsigned char*)2010,
    (unsigned char*)2016,
    (unsigned char*)2383,
    (unsigned char*)2614,
    (unsigned char*)2620,
    (unsigned char*)2770,
    (unsigned char*)3044,
    (unsigned char*)3138,
    (unsigned char*)3324,
    (unsigned char*)3576,
    (unsigned char*)3721,
    (unsigned char*)3907,
    (unsigned char*)4142,
    (unsigned char*)4380,
    (unsigned char*)4535,
    (unsigned char*)4696,
    (unsigned char*)4952,
    (unsigned char*)5215,
    (unsigned char*)5454,
    (unsigned char*)5914,
    (unsigned char*)6076,
    (unsigned char*)6298,
    (unsigned char*)6414,
    (unsigned char*)6559,
    (unsigned char*)6675,
    (unsigned char*)6804,
    (unsigned char*)6936,
    (unsigned char*)7246,
    (unsigned char*)7476,
    (unsigned char*)7616,
    (unsigned char*)7757,
    (unsigned char*)7873,
    (unsigned char*)8029,
    (unsigned char*)8173,
    (unsigned char*)8364,
    (unsigned char*)8540,
    (unsigned char*)8853,
    (unsigned char*)8973,
    (unsigned char*)9079,
    (unsigned char*)9340,
    (unsigned char*)9651,
    (unsigned char*)9827,
    (unsigned char*)10000,
    (unsigned char*)10146,
    (unsigned char*)10314,
    (unsigned char*)10370,
    (unsigned char*)10644,
    (unsigned char*)10823,
    (unsigned char*)11092,
    (unsigned char*)11206,
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

