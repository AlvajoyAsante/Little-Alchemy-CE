#include "pack_07.h"
#include <stdint.h>
#include <fileioc.h>

#define ALCHM07_HEADER_SIZE 0

unsigned char *ALCHM07_appvar[60] =
{
    (unsigned char*)0,
    (unsigned char*)269,
    (unsigned char*)427,
    (unsigned char*)644,
    (unsigned char*)886,
    (unsigned char*)1055,
    (unsigned char*)1069,
    (unsigned char*)1099,
    (unsigned char*)1391,
    (unsigned char*)1650,
    (unsigned char*)1874,
    (unsigned char*)2161,
    (unsigned char*)2312,
    (unsigned char*)2700,
    (unsigned char*)2983,
    (unsigned char*)3134,
    (unsigned char*)3481,
    (unsigned char*)3608,
    (unsigned char*)3888,
    (unsigned char*)4088,
    (unsigned char*)4261,
    (unsigned char*)4387,
    (unsigned char*)4697,
    (unsigned char*)4819,
    (unsigned char*)4990,
    (unsigned char*)5258,
    (unsigned char*)5435,
    (unsigned char*)5661,
    (unsigned char*)5875,
    (unsigned char*)6335,
    (unsigned char*)6664,
    (unsigned char*)6882,
    (unsigned char*)7116,
    (unsigned char*)7267,
    (unsigned char*)7618,
    (unsigned char*)7899,
    (unsigned char*)8108,
    (unsigned char*)8413,
    (unsigned char*)8737,
    (unsigned char*)8904,
    (unsigned char*)9118,
    (unsigned char*)9283,
    (unsigned char*)9407,
    (unsigned char*)9665,
    (unsigned char*)9914,
    (unsigned char*)10129,
    (unsigned char*)10261,
    (unsigned char*)10454,
    (unsigned char*)10691,
    (unsigned char*)10870,
    (unsigned char*)11112,
    (unsigned char*)11376,
    (unsigned char*)11653,
    (unsigned char*)11831,
    (unsigned char*)12139,
    (unsigned char*)12408,
    (unsigned char*)12643,
    (unsigned char*)12986,
    (unsigned char*)13159,
    (unsigned char*)13380,
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

