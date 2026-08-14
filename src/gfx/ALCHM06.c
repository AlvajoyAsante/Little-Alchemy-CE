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
    (unsigned char*)1343,
    (unsigned char*)1549,
    (unsigned char*)1700,
    (unsigned char*)1964,
    (unsigned char*)2130,
    (unsigned char*)2320,
    (unsigned char*)2736,
    (unsigned char*)2882,
    (unsigned char*)2972,
    (unsigned char*)3180,
    (unsigned char*)3480,
    (unsigned char*)3793,
    (unsigned char*)4023,
    (unsigned char*)4192,
    (unsigned char*)4373,
    (unsigned char*)4631,
    (unsigned char*)4757,
    (unsigned char*)4896,
    (unsigned char*)5262,
    (unsigned char*)5454,
    (unsigned char*)5711,
    (unsigned char*)6062,
    (unsigned char*)6389,
    (unsigned char*)6604,
    (unsigned char*)6808,
    (unsigned char*)7097,
    (unsigned char*)7531,
    (unsigned char*)7794,
    (unsigned char*)8061,
    (unsigned char*)8259,
    (unsigned char*)8617,
    (unsigned char*)8830,
    (unsigned char*)9013,
    (unsigned char*)9401,
    (unsigned char*)9623,
    (unsigned char*)9757,
    (unsigned char*)10101,
    (unsigned char*)10318,
    (unsigned char*)10434,
    (unsigned char*)10700,
    (unsigned char*)10835,
    (unsigned char*)11074,
    (unsigned char*)11208,
    (unsigned char*)11487,
    (unsigned char*)11651,
    (unsigned char*)11922,
    (unsigned char*)12072,
    (unsigned char*)12354,
    (unsigned char*)12896,
    (unsigned char*)13330,
    (unsigned char*)13365,
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

