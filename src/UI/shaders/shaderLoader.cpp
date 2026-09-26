#include <Logger/logger.h>
#include <UI/shaders/shaderLoader.h>
#include <Util/File/fileReader.h>

using namespace cgame::logger;
using namespace cgame::util::file;

namespace cgame::ui::shaders
{

GLuint loadShader(std::string shaderPath, GLenum shaderType)
{
    std::string shaderSource = read_file(shaderPath);
    const char* shaderSourceC = shaderSource.c_str();

    GLuint shader = glCreateShader(shaderType);

    glShaderSource(shader, 1, &shaderSourceC, nullptr);

    glCompileShader(shader);

    GLint success;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);

    if (!success)
    {
        GLint logLength;
        glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &logLength);

        if (logLength <= 2)
        {
            log_error("Shader compilation failed, but OpenGL provided no error message.");
        }
        else
        {
            std::string infoLog(logLength, '\0');

            glGetShaderInfoLog(shader, logLength, nullptr, infoLog.data());

            log_error("Shader compilation failed: %s", infoLog.c_str());
        }
    }

    return shader;
}

GLuint assembleShaderProgram(std::list<GLuint> shaders, bool deleteShaders)
{
    GLuint shaderProgram = glCreateProgram();

    for (auto shader : shaders)
    {
        glAttachShader(shaderProgram, shader);
    }

    glLinkProgram(shaderProgram);

    GLint success;
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);

    if (!success)
    {
        GLint logLength;
        glGetProgramiv(shaderProgram, GL_INFO_LOG_LENGTH, &logLength);

        if (logLength <= 2)
        {
            log_error("Shader program linking failed, but OpenGL provided no error message.");
        }
        else
        {
            std::string infoLog(logLength, '\0');

            glGetProgramInfoLog(shaderProgram, logLength, nullptr, infoLog.data());

            log_error("Shader program linking failed: %s", infoLog.c_str());
        }
    }  

    if (deleteShaders)
    {
        for (auto shader : shaders)
        {
            glDeleteShader(shader);
        }
    }

    return shaderProgram;
}

}
