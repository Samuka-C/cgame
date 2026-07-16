#ifndef CGAME_LOGGER
#define CGAME_LOGGER

#define log_debug(fmt, ...) \
    logDebugCaller(__FILE__, __LINE__, __func__, fmt, ##__VA_ARGS__)

#define log_info(fmt, ...) \
    logInfoCaller(__FILE__, __LINE__, __func__, fmt, ##__VA_ARGS__)

#define log_warning(fmt, ...) \
    logWarningCaller(__FILE__, __LINE__, __func__, fmt, ##__VA_ARGS__)

#define log_error(fmt, ...) \
    logErrorCaller(__FILE__, __LINE__, __func__, fmt, ##__VA_ARGS__)

/**
 * Shows a debug message on the console only if debug mode is on
 */
void logDebugCaller(const char* file, int line, const char* func, const char* fmt, ...);

/**
 * Shows a info message on the console
 */
void logInfoCaller(const char* file, int line, const char* func, const char* fmt, ...);

/**
 * Shows a warning message on the console
 */
void logWarningCaller(const char* file, int line, const char* func, const char* fmt, ...);

/**
 * Shows a error message on the console
 */
void logErrorCaller(const char* file, int line, const char* func, const char* fmt, ...);

#endif