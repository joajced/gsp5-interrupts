#ifndef GPIO_H
#define GPIO_H

#include <stdbool.h>
#include "encoder.h"

void initInterrupts();

bool readButtonF(int);

#endif
