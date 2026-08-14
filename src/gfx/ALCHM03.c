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
    (unsigned char*)1025,
    (unsigned char*)1296,
    (unsigned char*)1534,
    (unsigned char*)1754,
    (unsigned char*)1760,
    (unsigned char*)2020,
    (unsigned char*)2026,
    (unsigned char*)2389,
    (unsigned char*)2620,
    (unsigned char*)2626,
    (unsigned char*)2776,
    (unsigned char*)3050,
    (unsigned char*)3145,
    (unsigned char*)3330,
    (unsigned char*)3582,
    (unsigned char*)3727,
    (unsigned char*)3905,
    (unsigned char*)4140,
    (unsigned char*)4373,
    (unsigned char*)4528,
    (unsigned char*)4691,
    (unsigned char*)4947,
    (unsigned char*)5210,
    (unsigned char*)5449,
    (unsigned char*)5909,
    (unsigned char*)6071,
    (unsigned char*)6293,
    (unsigned char*)6409,
    (unsigned char*)6554,
    (unsigned char*)6670,
    (unsigned char*)6798,
    (unsigned char*)6930,
    (unsigned char*)7240,
    (unsigned char*)7471,
    (unsigned char*)7611,
    (unsigned char*)7750,
    (unsigned char*)7866,
    (unsigned char*)8022,
    (unsigned char*)8166,
    (unsigned char*)8357,
    (unsigned char*)8533,
    (unsigned char*)8846,
    (unsigned char*)8966,
    (unsigned char*)9072,
    (unsigned char*)9333,
    (unsigned char*)9642,
    (unsigned char*)9818,
    (unsigned char*)9991,
    (unsigned char*)10137,
    (unsigned char*)10305,
    (unsigned char*)10361,
    (unsigned char*)10635,
    (unsigned char*)10814,
    (unsigned char*)11083,
    (unsigned char*)11196,
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

