#include "pack_02.h"
#include <stdint.h>
#include <fileioc.h>

#define ALCHM02_HEADER_SIZE 0

unsigned char *ALCHM02_appvar[60] =
{
    (unsigned char*)0,
    (unsigned char*)235,
    (unsigned char*)259,
    (unsigned char*)394,
    (unsigned char*)724,
    (unsigned char*)870,
    (unsigned char*)1167,
    (unsigned char*)1370,
    (unsigned char*)1636,
    (unsigned char*)1833,
    (unsigned char*)1977,
    (unsigned char*)2160,
    (unsigned char*)2395,
    (unsigned char*)2621,
    (unsigned char*)2635,
    (unsigned char*)2754,
    (unsigned char*)2935,
    (unsigned char*)3126,
    (unsigned char*)3292,
    (unsigned char*)3457,
    (unsigned char*)3651,
    (unsigned char*)3905,
    (unsigned char*)3979,
    (unsigned char*)4364,
    (unsigned char*)4511,
    (unsigned char*)4642,
    (unsigned char*)4871,
    (unsigned char*)5061,
    (unsigned char*)5250,
    (unsigned char*)5399,
    (unsigned char*)5663,
    (unsigned char*)5914,
    (unsigned char*)6089,
    (unsigned char*)6404,
    (unsigned char*)6600,
    (unsigned char*)6737,
    (unsigned char*)6800,
    (unsigned char*)7141,
    (unsigned char*)7435,
    (unsigned char*)7699,
    (unsigned char*)7986,
    (unsigned char*)8183,
    (unsigned char*)8524,
    (unsigned char*)8667,
    (unsigned char*)8856,
    (unsigned char*)9051,
    (unsigned char*)9194,
    (unsigned char*)9473,
    (unsigned char*)9646,
    (unsigned char*)9833,
    (unsigned char*)9953,
    (unsigned char*)10178,
    (unsigned char*)10317,
    (unsigned char*)10509,
    (unsigned char*)10743,
    (unsigned char*)10981,
    (unsigned char*)11140,
    (unsigned char*)11311,
    (unsigned char*)11687,
    (unsigned char*)11933,
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

