#ifndef CGAME_SHADER_LOADER
#define CGAME_SHADER_LOADER

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <string>
#include <list>

/**
 * @brief loads and compiles a gl shader
 * 
 * @return a GLuint code for the shader created
 */
GLuint loadShader(std::string shaderPath, GLenum shaderType);

/**
 * @brief assembles a shader program from various shaders
 * 
 * @param deleteShaders controls if the method should delete the shaders after assembling the program
 * 
 * @return a GLuint code for the shader program created
 */
GLuint assembleShaderProgram(std::list<GLuint> shaders, bool deleteShaders=true);

#endif