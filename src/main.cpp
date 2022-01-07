#include <docopt/docopt.h>
#include <spdlog/spdlog.h>


#include "KVCache/KVCacheInterface/KVCacheAbstract.h"

static constexpr auto USAGE =
    R"(KVCache App.
 Usage:
 Options:
          -h --help     Show this screen.
          --version     Show version.
)";

int main(int argc, const char** argv)
{
    std::map<std::string, docopt::value> args = docopt::docopt(USAGE,
                                                               {std::next(argv), std::next(argv, argc)},
                                                               true,   // show help if requested
                                                               "KVCache App 1.0");   // version string

    spdlog::info("Starting Up KV Cache Client");

    std::string logArgsMes = "Received Args: \n";
    for (auto const& arg: args)
    {
        logArgsMes += arg.first + " = " + arg.second.asString() + "\n";
    }

    spdlog::info("Creating KVCache Object");
    auto kvCache = KVCache::Interface::KVCacheAbstract::createKVCache();
    spdlog::info("KVCache Object Created Succesfully");

    spdlog::info("Closing Up KV Cache Client");

    return 0;
}
