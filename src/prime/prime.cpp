#include "prime.h"

bool prime::isPrime(const int primeNumber)
{

    if (primeNumber <= 1)
        return false;

    if (primeNumber == 2 || primeNumber == 3)
        return true;

    if (primeNumber % 2 == 0 || primeNumber % 3 == 0)
        return false;

    for (int i = 5; i * i <= primeNumber; i += 6)
    {
        if (primeNumber % i == 0 || primeNumber % (i + 2) == 0)
            return false;
    }

    return true;
}
