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
    (unsigned char*)1375,
    (unsigned char*)1503,
    (unsigned char*)1865,
    (unsigned char*)1985,
    (unsigned char*)2098,
    (unsigned char*)2307,
    (unsigned char*)2702,
    (unsigned char*)3230,
    (unsigned char*)3440,
    (unsigned char*)3690,
    (unsigned char*)3967,
    (unsigned char*)4217,
    (unsigned char*)4555,
    (unsigned char*)5025,
    (unsigned char*)5479,
    (unsigned char*)5727,
    (unsigned char*)6032,
    (unsigned char*)6328,
    (unsigned char*)6865,
    (unsigned char*)7050,
    (unsigned char*)7556,
    (unsigned char*)7769,
    (unsigned char*)8113,
    (unsigned char*)8392,
    (unsigned char*)8941,
    (unsigned char*)9233,
    (unsigned char*)9455,
    (unsigned char*)9739,
    (unsigned char*)10058,
    (unsigned char*)10209,
    (unsigned char*)10341,
    (unsigned char*)10653,
    (unsigned char*)10926,
    (unsigned char*)11047,
    (unsigned char*)11225,
    (unsigned char*)11628,
    (unsigned char*)11962,
    (unsigned char*)12339,
    (unsigned char*)12483,
    (unsigned char*)12867,
    (unsigned char*)13198,
    (unsigned char*)13593,
    (unsigned char*)13949,
    (unsigned char*)14151,
    (unsigned char*)14349,
    (unsigned char*)14703,
    (unsigned char*)14939,
    (unsigned char*)15245,
    (unsigned char*)15395,
    (unsigned char*)15637,
    (unsigned char*)16108,
    (unsigned char*)16311,
    (unsigned char*)16590,
    (unsigned char*)16939,
    (unsigned char*)17209,
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

