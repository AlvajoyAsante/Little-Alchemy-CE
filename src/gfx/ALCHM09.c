#include "pack_09.h"
#include <stdint.h>
#include <fileioc.h>

#define ALCHM09_HEADER_SIZE 0

unsigned char *ALCHM09_appvar[40] =
{
    (unsigned char*)0,
    (unsigned char*)309,
    (unsigned char*)677,
    (unsigned char*)1060,
    (unsigned char*)1269,
    (unsigned char*)1439,
    (unsigned char*)1959,
    (unsigned char*)2197,
    (unsigned char*)2389,
    (unsigned char*)2857,
    (unsigned char*)3022,
    (unsigned char*)3368,
    (unsigned char*)3761,
    (unsigned char*)3999,
    (unsigned char*)4195,
    (unsigned char*)4374,
    (unsigned char*)4593,
    (unsigned char*)4966,
    (unsigned char*)5250,
    (unsigned char*)5419,
    (unsigned char*)6013,
    (unsigned char*)6438,
    (unsigned char*)6735,
    (unsigned char*)7135,
    (unsigned char*)7582,
    (unsigned char*)7914,
    (unsigned char*)8467,
    (unsigned char*)8768,
    (unsigned char*)9090,
    (unsigned char*)9318,
    (unsigned char*)9545,
    (unsigned char*)9935,
    (unsigned char*)10308,
    (unsigned char*)10474,
    (unsigned char*)10650,
    (unsigned char*)10922,
    (unsigned char*)11370,
    (unsigned char*)11748,
    (unsigned char*)12112,
    (unsigned char*)12382,
};

unsigned char ALCHM09_init(void)
{
    uintptr_t data;
    unsigned int i;
    uint8_t appvar;

    appvar = ti_Open("ALCHM09", "r");
    if (appvar == 0)
    {
        return 0;
    }

    data = (uintptr_t)ti_GetDataPtr(appvar) - (uintptr_t)ALCHM09_appvar[0] + ALCHM09_HEADER_SIZE;
    for (i = 0; i < 40; i++)
    {
        ALCHM09_appvar[i] += data;
    }

    ti_Close(appvar);

    return 1;
}

