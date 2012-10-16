#include <stdio.h>
#include <string.h>

#include "utils.h"

void float2string(float zahl, char zieltxt[10])
{
    int _vorkomma = 0, _nachkomma = 0;
    float _buffer = 0;
    _vorkomma = (int)zahl;
    _buffer = zahl-_vorkomma;
    _nachkomma = (int)(_buffer*100);
    sprintf(zieltxt, "%d,%d", _vorkomma, _nachkomma);
}
