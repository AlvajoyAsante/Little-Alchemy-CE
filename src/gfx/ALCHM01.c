#include "pack_01.h"
#include <stdint.h>
#include <fileioc.h>

#define ALCHM01_HEADER_SIZE 0

unsigned char *ALCHM01_appvar[60] =
{
    (unsigned char*)0,
    (unsigned char*)231,
    (unsigned char*)432,
    (unsigned char*)641,
    (unsigned char*)828,
    (unsigned char*)1012,
    (unsigned char*)1209,
    (unsigned char*)1381,
    (unsigned char*)1483,
    (unsigned char*)1592,
    (unsigned char*)1790,
    (unsigned char*)2020,
    (unsigned char*)2248,
    (unsigned char*)2373,
    (unsigned char*)2599,
    (unsigned char*)2753,
    (unsigned char*)3195,
    (unsigned char*)3365,
    (unsigned char*)3511,
    (unsigned char*)3723,
    (unsigned char*)3940,
    (unsigned char*)4065,
    (unsigned char*)4425,
    (unsigned char*)4689,
    (unsigned char*)4872,
    (unsigned char*)5089,
    (unsigned char*)5365,
    (unsigned char*)5637,
    (unsigned char*)5840,
    (unsigned char*)6042,
    (unsigned char*)6308,
    (unsigned char*)6519,
    (unsigned char*)6736,
    (unsigned char*)6867,
    (unsigned char*)7055,
    (unsigned char*)7199,
    (unsigned char*)7410,
    (unsigned char*)7531,
    (unsigned char*)7671,
    (unsigned char*)7894,
    (unsigned char*)8008,
    (unsigned char*)8092,
    (unsigned char*)8254,
    (unsigned char*)8645,
    (unsigned char*)8818,
    (unsigned char*)8941,
    (unsigned char*)9172,
    (unsigned char*)9319,
    (unsigned char*)9405,
    (unsigned char*)9548,
    (unsigned char*)9554,
    (unsigned char*)9717,
    (unsigned char*)9835,
    (unsigned char*)10094,
    (unsigned char*)10222,
    (unsigned char*)10433,
    (unsigned char*)10691,
    (unsigned char*)10894,
    (unsigned char*)10964,
    (unsigned char*)11123,
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

