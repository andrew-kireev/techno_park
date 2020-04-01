
#include "GlobalFunction.h"

int main(int argc, char* argv[]) {


    logger::Logger& log = logger::Logger::get_instance();
    log.set_global_logger(logger::create_stderr_logger());
    logger::error("error");
    logger::info("info");
    logger::debug("debug");
    logger::warning("warning");
    return 0;
}