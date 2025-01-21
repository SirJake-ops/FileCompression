//
// Created by Jacob Pagan on 1/20/25.
//

#ifndef OSCONFIG_H
#define OSCONFIG_H

#if defined(_WIN32) || defined(_WIN64)
    #define OS_NAME "Windows"
#elif defined(__linux__)
    #define OS_NAME "Linux"
#elif defined(__APPLE__) || defined(__MACH__)
    #define OS_NAME "macOS"
#else
    #define OS_NAME "Unknown"
#endif

#endif //OSCONFIG_H
