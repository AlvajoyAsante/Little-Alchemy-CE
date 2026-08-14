#include "pack_00.h"
#include <stdint.h>
#include <fileioc.h>

#define ALCHM00_HEADER_SIZE 0

unsigned char *ALCHM00_appvar[61] =
{
    (unsigned char*)0,
    (unsigned char*)512,
    (unsigned char*)698,
    (unsigned char*)872,
    (unsigned char*)1113,
    (unsigned char*)1165,
    (unsigned char*)1504,
    (unsigned char*)1656,
    (unsigned char*)1835,
    (unsigned char*)2119,
    (unsigned char*)2245,
    (unsigned char*)2381,
    (unsigned char*)2507,
    (unsigned char*)2665,
    (unsigned char*)2867,
    (unsigned char*)3038,
    (unsigned char*)3201,
    (unsigned char*)3377,
    (unsigned char*)3516,
    (unsigned char*)3685,
    (unsigned char*)3898,
    (unsigned char*)3904,
    (unsigned char*)4298,
    (unsigned char*)4410,
    (unsigned char*)4545,
    (unsigned char*)4719,
    (unsigned char*)4779,
    (unsigned char*)5014,
    (unsigned char*)5202,
    (unsigned char*)5337,
    (unsigned char*)5495,
    (unsigned char*)5623,
    (unsigned char*)5857,
    (unsigned char*)5965,
    (unsigned char*)6149,
    (unsigned char*)6155,
    (unsigned char*)6226,
    (unsigned char*)6437,
    (unsigned char*)6867,
    (unsigned char*)7105,
    (unsigned char*)7242,
    (unsigned char*)7450,
    (unsigned char*)7809,
    (unsigned char*)8032,
    (unsigned char*)8207,
    (unsigned char*)8501,
    (unsigned char*)8593,
    (unsigned char*)8695,
    (unsigned char*)8876,
    (unsigned char*)9168,
    (unsigned char*)9329,
    (unsigned char*)9435,
    (unsigned char*)9512,
    (unsigned char*)9620,
    (unsigned char*)9779,
    (unsigned char*)9990,
    (unsigned char*)10195,
    (unsigned char*)10343,
    (unsigned char*)10504,
    (unsigned char*)10769,
    (unsigned char*)11088,
};

unsigned char ALCHM00_init(void)
{
    uintptr_t data;
    unsigned int i;
    uint8_t appvar;

    appvar = ti_Open("ALCHM00", "r");
    if (appvar == 0)
    {
        return 0;
    }

    data = (uintptr_t)ti_GetDataPtr(appvar) - (uintptr_t)ALCHM00_appvar[0] + ALCHM00_HEADER_SIZE;
    for (i = 0; i < 61; i++)
    {
        ALCHM00_appvar[i] += data;
    }

    ti_Close(appvar);

    return 1;
}

