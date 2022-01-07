#include <functional>
#include <iostream>

#include <docopt/docopt.h>
#include <spdlog/spdlog.h>


#include "factorial/factorial.h"
#include "prime/prime.h"

static constexpr auto USAGE =
    R"(Test App.
 Usage:
        intro --factorial 7 => compute the factorial of the given number
        intro --prime 7 => check if the given number is prime
 Options:
          -h --help     Show this screen.
          --version     Show version.
          --factorial   Compute the factorial. 
          --prime       Check if the given number is prime.
)";

int main(int argc, const char** argv)
{
    std::map<std::string, docopt::value> args = docopt::docopt(USAGE,
                                                               {std::next(argv), std::next(argv, argc)},
                                                               true,   // show help if requested
                                                               "Test App 1.0");   // version string

    bool computeFactorial = false;
    int factorialNumber = 0;
    bool checkPrime = false;
    int primeNumber = 0;

    std::cout << "Received Args: "
              << "\n";
    for (auto const& arg: args)
    {
        std::cout << arg.first << "=" << arg.second << std::endl;
        if (arg.first.compare("factorial") == 0)
        {
            computeFactorial = true;
            factorialNumber = static_cast<int>(arg.second.asLong());
        }
        if (arg.first.compare("prime") == 0)
        {
            checkPrime = true;
            primeNumber = static_cast<int>(arg.second.asLong());
        }
    }


    // Use the default logger (stdout, multi-threaded, colored)
    spdlog::info("Hello, {}!", "World");

    // Factorial
    if (computeFactorial)
    {
        if (factorialNumber < 0)
            std::cerr << "Cannot compute the factorial of a negative number"
                      << "\n";

        const int fact = factorial::computeFact(factorialNumber);
        std::cout << "Factorial of  " << factorialNumber << " is: " << fact << "\n";
    }

    // Prime
    if (checkPrime)
    {
        const bool prime = prime::isPrime(primeNumber);
        std::cout << primeNumber << " is";
        if (!prime)
            std::cout << " not ";
        std::cout << " Prime"
                  << "\n";
    }

    return 0;
}
