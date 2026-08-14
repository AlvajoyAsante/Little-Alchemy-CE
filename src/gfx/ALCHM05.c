#include "pack_05.h"
#include <stdint.h>
#include <fileioc.h>

#define ALCHM05_HEADER_SIZE 0

unsigned char *ALCHM05_appvar[60] =
{
    (unsigned char*)0,
    (unsigned char*)108,
    (unsigned char*)307,
    (unsigned char*)524,
    (unsigned char*)888,
    (unsigned char*)1140,
    (unsigned char*)1327,
    (unsigned char*)1589,
    (unsigned char*)1783,
    (unsigned char*)1923,
    (unsigned char*)2230,
    (unsigned char*)2460,
    (unsigned char*)2555,
    (unsigned char*)2794,
    (unsigned char*)3061,
    (unsigned char*)3238,
    (unsigned char*)3750,
    (unsigned char*)4166,
    (unsigned char*)4457,
    (unsigned char*)4614,
    (unsigned char*)4778,
    (unsigned char*)4953,
    (unsigned char*)5108,
    (unsigned char*)5333,
    (unsigned char*)5675,
    (unsigned char*)5772,
    (unsigned char*)5893,
    (unsigned char*)6034,
    (unsigned char*)6346,
    (unsigned char*)6571,
    (unsigned char*)6764,
    (unsigned char*)6908,
    (unsigned char*)7078,
    (unsigned char*)7288,
    (unsigned char*)7459,
    (unsigned char*)7618,
    (unsigned char*)7715,
    (unsigned char*)7864,
    (unsigned char*)8046,
    (unsigned char*)8348,
    (unsigned char*)8754,
    (unsigned char*)8999,
    (unsigned char*)9179,
    (unsigned char*)9415,
    (unsigned char*)9494,
    (unsigned char*)9678,
    (unsigned char*)9874,
    (unsigned char*)10068,
    (unsigned char*)10388,
    (unsigned char*)10588,
    (unsigned char*)11009,
    (unsigned char*)11401,
    (unsigned char*)11628,
    (unsigned char*)11939,
    (unsigned char*)12215,
    (unsigned char*)12425,
    (unsigned char*)12674,
    (unsigned char*)12919,
    (unsigned char*)13203,
    (unsigned char*)13370,
};

unsigned char ALCHM05_init(void)
{
    uintptr_t data;
    unsigned int i;
    uint8_t appvar;

    appvar = ti_Open("ALCHM05", "r");
    if (appvar == 0)
    {
        return 0;
    }

    data = (uintptr_t)ti_GetDataPtr(appvar) - (uintptr_t)ALCHM05_appvar[0] + ALCHM05_HEADER_SIZE;
    for (i = 0; i < 60; i++)
    {
        ALCHM05_appvar[i] += data;
    }

    ti_Close(appvar);

    return 1;
}

