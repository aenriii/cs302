#pragma once
#include "../config.h"
#include <stdio.h>


#define LOGGING_LEVEL_DEBUG 0
#define LOGGING_LEVEL_INFO 1
#define LOGGING_LEVEL_WARN 2
#define LOGGING_LEVEL_ERROR 3
#define LOGGING_LEVEL_FATAL 4

#ifdef LOGGING_LEVEL
#define DEBUG(...) \
  if (LOGGING_LEVEL <= LOGGING_LEVEL_DEBUG) { \
    printf("[DEBUG] "); \
    printf(__VA_ARGS__); \
    printf("\n"); \
  }
#define INFO(...) \
    if (LOGGING_LEVEL <= LOGGING_LEVEL_INFO) { \
        printf("[INFO] "); \
        printf(__VA_ARGS__); \
        printf("\n"); \
    }
#define WARN(...) \
    if (LOGGING_LEVEL <= LOGGING_LEVEL_WARN) { \
        printf("[WARN] "); \
        printf(__VA_ARGS__); \
        printf("\n"); \
    }
#define ERROR(...) \
    if (LOGGING_LEVEL <= LOGGING_LEVEL_ERROR) { \
        printf("[ERROR] "); \
        printf(__VA_ARGS__); \
        printf("\n"); \
    }
#define FATAL(...) \
    if (LOGGING_LEVEL <= LOGGING_LEVEL_FATAL) { \
        printf("[FATAL] "); \
        printf(__VA_ARGS__); \
        printf("\n"); \
    }
#else
#define DEBUG(...)
#define INFO(...)
#define WARN(...)
#define ERROR(...)
#define FATAL(...)
#endif

