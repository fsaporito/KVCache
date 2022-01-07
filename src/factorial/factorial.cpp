#include "factorial.h"

int factorial::computeFact(const int factorialNumber)
{

    if (factorialNumber == 0)
        return 1;
    if (factorialNumber == 1)
        return 1;
    if (factorialNumber == 2)
        return 2;
    if (factorialNumber == 3)
        return 6;
    if (factorialNumber == 4)
        return 24;
    if (factorialNumber == 5)
        return 120;
    return factorialNumber * computeFact(factorialNumber - 1);
}
