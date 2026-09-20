#include <Util/File/fileReader.h>

#include <fstream>
#include <sstream>

std::string read_file(const std::string& path)
{
    std::ifstream file(path);

    std::stringstream buffer;
    buffer << file.rdbuf();

    return buffer.str();
}
