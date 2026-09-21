#include <Logger/logger.h>
#include <UI/shaders/shaderLoader.h>
#include <Util/File/fileReader.h>

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
        char infoLog[512];
        glGetShaderInfoLog(shader, 512, nullptr, infoLog);

        log_error("Shader compilation failed: %s", infoLog);

        glDeleteShader(shader);
        return 0;
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
        char* description;
        glGetProgramInfoLog(shaderProgram, 512, nullptr, description);

        log_error("Shader program linking failed: %s", description);

        glDeleteProgram(shaderProgram);
        return 0;
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
