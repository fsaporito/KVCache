#include "factorial/factorial.h"
#include "prime/prime.h"
#include <catch2/catch.hpp>


TEST_CASE("Factorials are computed: 0!", "[computeFact0]")
{
    REQUIRE(factorial::computeFact(0) == 1);
}

TEST_CASE("Factorials are computed: 1!", "[computeFact1]")
{
    REQUIRE(factorial::computeFact(1) == 1);
}

TEST_CASE("Factorials are computed: 2!", "[computeFact2]")
{
    REQUIRE(factorial::computeFact(2) == 2);
}

TEST_CASE("Factorials are computed: 3!", "[computeFact3]")
{
    REQUIRE(factorial::computeFact(3) == 6);
}

TEST_CASE("Factorials are computed: 4!", "[computeFact4]")
{
    REQUIRE(factorial::computeFact(4) == 24);
}

TEST_CASE("Factorials are computed: 5!", "[computeFact5]")
{
    REQUIRE(factorial::computeFact(5) == 120);
}

TEST_CASE("Factorials are computed: 6!", "[computeFact6]")
{
    REQUIRE(factorial::computeFact(6) == 720);
}

TEST_CASE("Factorials are computed: 7!", "[computeFact7]")
{
    REQUIRE(factorial::computeFact(7) == 5040);
}

TEST_CASE("Factorials are computed: 8!", "[computeFact8]")
{
    REQUIRE(factorial::computeFact(8) == 40320);
}

TEST_CASE("Factorials are computed: 9!", "[computeFact9]")
{
    REQUIRE(factorial::computeFact(9) == 362880);
}

TEST_CASE("Factorials are computed: 10!", "[computeFact10]")
{
    REQUIRE(factorial::computeFact(10) == 3628800);
}


TEST_CASE("Primes are checked: 0", "[isPrime0]")
{
    REQUIRE(!prime::isPrime(0));
}

TEST_CASE("Primes are checked: 1", "[isPrime1]")
{
    REQUIRE(!prime::isPrime(1));
}

TEST_CASE("Primes are checked: 2", "[isPrime2]")
{
    REQUIRE(prime::isPrime(2));
}

TEST_CASE("Primes are checked: 3", "[isPrime3]")
{
    REQUIRE(prime::isPrime(3));
}

TEST_CASE("Primes are checked: 4", "[isPrime4]")
{
    REQUIRE(!prime::isPrime(4));
}

TEST_CASE("Primes are checked: 5", "[isPrime5]")
{
    REQUIRE(prime::isPrime(5));
}

TEST_CASE("Primes are checked: 6", "[isPrime6]")
{
    REQUIRE(!prime::isPrime(6));
}

TEST_CASE("Primes are checked: 7", "[isPrime7]")
{
    REQUIRE(prime::isPrime(7));
}

TEST_CASE("Primes are checked: 8", "[isPrime8]")
{
    REQUIRE(!prime::isPrime(8));
}

TEST_CASE("Primes are checked: 9", "[isPrime9]")
{
    REQUIRE(!prime::isPrime(9));
}

TEST_CASE("Primes are checked: 10", "[isPrime10]")
{
    REQUIRE(!prime::isPrime(10));
}

TEST_CASE("Primes are checked: 11", "[isPrime11]")
{
    REQUIRE(prime::isPrime(11));
}

TEST_CASE("Primes are checked: 13", "[isPrime13]")
{
    REQUIRE(prime::isPrime(13));
}

TEST_CASE("Primes are checked: 15", "[isPrime15]")
{
    REQUIRE(!prime::isPrime(15));
}

TEST_CASE("Primes are checked: 17", "[isPrime17]")
{
    REQUIRE(prime::isPrime(17));
}

TEST_CASE("Primes are checked: 19", "[isPrime19]")
{
    REQUIRE(prime::isPrime(19));
}

TEST_CASE("Primes are checked: 21", "[isPrime21]")
{
    REQUIRE(!prime::isPrime(21));
}

TEST_CASE("Primes are checked: 23", "[isPrime23]")
{
    REQUIRE(prime::isPrime(23));
}
