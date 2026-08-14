#include "pack_08.h"
#include <stdint.h>
#include <fileioc.h>

#define ALCHM08_HEADER_SIZE 0

unsigned char *ALCHM08_appvar[60] =
{
    (unsigned char*)0,
    (unsigned char*)189,
    (unsigned char*)440,
    (unsigned char*)839,
    (unsigned char*)943,
    (unsigned char*)1386,
    (unsigned char*)1517,
    (unsigned char*)1879,
    (unsigned char*)1998,
    (unsigned char*)2111,
    (unsigned char*)2326,
    (unsigned char*)2721,
    (unsigned char*)3252,
    (unsigned char*)3463,
    (unsigned char*)3695,
    (unsigned char*)3973,
    (unsigned char*)4222,
    (unsigned char*)4561,
    (unsigned char*)5032,
    (unsigned char*)5486,
    (unsigned char*)5734,
    (unsigned char*)6042,
    (unsigned char*)6338,
    (unsigned char*)6876,
    (unsigned char*)7061,
    (unsigned char*)7567,
    (unsigned char*)7780,
    (unsigned char*)8124,
    (unsigned char*)8403,
    (unsigned char*)8952,
    (unsigned char*)9244,
    (unsigned char*)9466,
    (unsigned char*)9750,
    (unsigned char*)10066,
    (unsigned char*)10200,
    (unsigned char*)10332,
    (unsigned char*)10644,
    (unsigned char*)10917,
    (unsigned char*)11034,
    (unsigned char*)11212,
    (unsigned char*)11615,
    (unsigned char*)11952,
    (unsigned char*)12332,
    (unsigned char*)12476,
    (unsigned char*)12865,
    (unsigned char*)13204,
    (unsigned char*)13599,
    (unsigned char*)13955,
    (unsigned char*)14152,
    (unsigned char*)14350,
    (unsigned char*)14703,
    (unsigned char*)14941,
    (unsigned char*)15242,
    (unsigned char*)15393,
    (unsigned char*)15639,
    (unsigned char*)16129,
    (unsigned char*)16332,
    (unsigned char*)16611,
    (unsigned char*)16949,
    (unsigned char*)17216,
};

unsigned char ALCHM08_init(void)
{
    uintptr_t data;
    unsigned int i;
    uint8_t appvar;

    appvar = ti_Open("ALCHM08", "r");
    if (appvar == 0)
    {
        return 0;
    }

    data = (uintptr_t)ti_GetDataPtr(appvar) - (uintptr_t)ALCHM08_appvar[0] + ALCHM08_HEADER_SIZE;
    for (i = 0; i < 60; i++)
    {
        ALCHM08_appvar[i] += data;
    }

    ti_Close(appvar);

    return 1;
}

