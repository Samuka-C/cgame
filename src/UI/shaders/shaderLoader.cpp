#include <UI/shaders/shaderLoader.h>
#include <Util/File/fileReader.h>

GLuint loadShader(std::string shaderPath, GLenum shaderType)
{
    std::string shaderSource = read_file(shaderPath);
    const char* shaderSourceC = shaderSource.c_str();

    GLuint shader = glCreateShader(shaderType);

    glShaderSource(shader, 1, &shaderSourceC, nullptr);

    glCompileShader(shader);

    return shader;
}

GLuint assembleShaderProgram(std::list<GLuint> shaders, bool deleteShaders=true)
{
    GLuint shaderProgram = glCreateProgram();

    for (auto shader : shaders)
    {
        glAttachShader(shaderProgram, shader);
    }

    glLinkProgram(shaderProgram);

    if (deleteShaders)
    {
        for (auto shader : shaders)
        {
            glDeleteShader(shader);
        }
    }

    return shaderProgram;
}
