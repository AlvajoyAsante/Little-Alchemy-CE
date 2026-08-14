#include "pack_07.h"
#include <stdint.h>
#include <fileioc.h>

#define ALCHM07_HEADER_SIZE 0

unsigned char *ALCHM07_appvar[60] =
{
    (unsigned char*)0,
    (unsigned char*)260,
    (unsigned char*)429,
    (unsigned char*)652,
    (unsigned char*)908,
    (unsigned char*)1099,
    (unsigned char*)1105,
    (unsigned char*)1127,
    (unsigned char*)1432,
    (unsigned char*)1712,
    (unsigned char*)1954,
    (unsigned char*)2254,
    (unsigned char*)2403,
    (unsigned char*)2805,
    (unsigned char*)3100,
    (unsigned char*)3254,
    (unsigned char*)3612,
    (unsigned char*)3733,
    (unsigned char*)4039,
    (unsigned char*)4252,
    (unsigned char*)4418,
    (unsigned char*)4541,
    (unsigned char*)4865,
    (unsigned char*)4986,
    (unsigned char*)5158,
    (unsigned char*)5450,
    (unsigned char*)5631,
    (unsigned char*)5855,
    (unsigned char*)6098,
    (unsigned char*)6578,
    (unsigned char*)6921,
    (unsigned char*)7155,
    (unsigned char*)7400,
    (unsigned char*)7558,
    (unsigned char*)7918,
    (unsigned char*)8206,
    (unsigned char*)8433,
    (unsigned char*)8734,
    (unsigned char*)9084,
    (unsigned char*)9239,
    (unsigned char*)9449,
    (unsigned char*)9618,
    (unsigned char*)9734,
    (unsigned char*)9999,
    (unsigned char*)10257,
    (unsigned char*)10502,
    (unsigned char*)10631,
    (unsigned char*)10827,
    (unsigned char*)11087,
    (unsigned char*)11270,
    (unsigned char*)11505,
    (unsigned char*)11796,
    (unsigned char*)12089,
    (unsigned char*)12255,
    (unsigned char*)12582,
    (unsigned char*)12872,
    (unsigned char*)13105,
    (unsigned char*)13459,
    (unsigned char*)13627,
    (unsigned char*)13848,
};

unsigned char ALCHM07_init(void)
{
    uintptr_t data;
    unsigned int i;
    uint8_t appvar;

    appvar = ti_Open("ALCHM07", "r");
    if (appvar == 0)
    {
        return 0;
    }

    data = (uintptr_t)ti_GetDataPtr(appvar) - (uintptr_t)ALCHM07_appvar[0] + ALCHM07_HEADER_SIZE;
    for (i = 0; i < 60; i++)
    {
        ALCHM07_appvar[i] += data;
    }

    ti_Close(appvar);

    return 1;
}

