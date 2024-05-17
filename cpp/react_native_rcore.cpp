#include <android/log.h>
#include <linux/time.h>
#include <time.h>
#include <android/window.h>

#define LOG_TAG "RAYLIB_REACT_NATIVE_RCORE"  // Define the log tag
#define LOGI(...) __android_log_print(ANDROID_LOG_INFO, LOG_TAG, __VA_ARGS__)


extern CoreData CORE;

// Get elapsed time measure in seconds since InitTimer()
double GetTime(void)
{
    double time = 0.0;
    struct timespec ts = { 0 };
    clock_gettime(CLOCK_MONOTONIC, &ts);
    unsigned long long int nanoSeconds = (unsigned long long int)ts.tv_sec*1000000000LLU + (unsigned long long int)ts.tv_nsec;

    time = (double)(nanoSeconds - CORE.Time.base)*1e-9;  // Elapsed time since InitTimer()

    return time;
}

Vector2 GetWindowScaleDPI(void) {
    return (Vector2){1.0f, 1.0f};
}

void PollInputEvents(void) {
    // Implementation of PollInputEvents
}

void SwapScreenBuffer(void) {
    // Swap screen buffer
}

// Set window state: maximized, if resizable
void MaximizeWindow(void) {
    LOGI("MaximizeWindow() not available on target platform");
}

// Set window state: minimized
void MinimizeWindow(void) {
    LOGI("MinimizeWindow() not available on target platform");
}

// Set window state: not minimized/maximized
void RestoreWindow(void) {
    LOGI("RestoreWindow() not available on target platform");
}

/* this is called by InitWindow() */
int InitPlatform(void) {

    // Initialize OpenGL context
    return 0;
}


void ClosePlatform(void) {
    // Cleanup OpenGL
}

// Set window dimensions
void SetWindowSize(int width, int height)
{
    LOGI("SetWindowSize() not available on target platform");
}

