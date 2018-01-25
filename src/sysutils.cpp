#include "sysutils.h"

bool fpath_exists(const std::string& fpath) {
    struct stat buffer;

    return (stat(fpath.c_str(), &buffer) == 0);
}
