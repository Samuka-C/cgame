#include <Logger/logger.h>
#include <Util/File/fileReader.h>

#include <fstream>
#include <sstream>

using namespace cgame::logger;

namespace cgame::util::file
{

std::string read_file(const std::string& path)
{
    std::ifstream file(path);

    if (!file.is_open())
    {
        log_error("file with path: %s, couldn't be opened", path.c_str());
        return "";
    }

    std::stringstream buffer;
    buffer << file.rdbuf();

    return buffer.str();
}

}
