#pragma once
#include "../create_exception.h"

#include <string>
#include <filesystem>
#include <fstream>

#include "define/define.h"

namespace create{
    void config (const std::string &file_path);
}
