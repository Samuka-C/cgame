#include <Logger/logger.h>

#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>

#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_YELLOW  "\x1b[33m"
#define ANSI_COLOR_BLUE    "\x1b[34m"
#define ANSI_COLOR_MAGENTA "\x1b[35m"
#define ANSI_COLOR_CYAN    "\x1b[36m"
#define ANSI_COLOR_RESET   "\x1b[0m"

char* format(const char* fmt, va_list args)
{
    va_list args_copy;
    va_copy(args_copy, args);

    int len = vsnprintf(NULL, 0, fmt, args_copy);
    va_end(args_copy);

    char* buffer = (char*)malloc(len+1);
    vsnprintf(buffer, len + 1, fmt, args);
    va_end(args);

    return buffer;
}

void logDebugCaller(const char* file, int line, const char* func, const char* fmt, ...)
{
    va_list args;
    va_start(args, fmt);

    char* msg = format(fmt, args);

    printf("%sDEBUG (%s - %s() - line %d): %s%s\n", ANSI_COLOR_BLUE, file, func, line, msg, ANSI_COLOR_RESET);

    free(msg);
}

void logInfoCaller(const char* file, int line, const char* func, const char* fmt, ...)
{
    va_list args;
    va_start(args, fmt);

    char* msg = format(fmt, args);

    printf("%sINFO (%s - %s() - line %d): %s%s\n", ANSI_COLOR_GREEN, file, func, line, msg, ANSI_COLOR_RESET);

    free(msg);
}

void logWarningCaller(const char* file, int line, const char* func, const char* fmt, ...)
{
    va_list args;
    va_start(args, fmt);

    char* msg = format(fmt, args);

    printf("%sWARNING! (%s - %s() - line %d): %s%s\n", ANSI_COLOR_YELLOW, file, func, line, msg, ANSI_COLOR_RESET);

    free(msg);
}

void logErrorCaller(const char* file, int line, const char* func, const char* fmt, ...)
{
    va_list args;
    va_start(args, fmt);

    char* msg = format(fmt, args);

    printf("%sERROR!! (%s - %s() - line %d): %s%s\n", ANSI_COLOR_RED, file, func, line, msg, ANSI_COLOR_RESET);

    free(msg);
}