#include <android/log.h>
#include <linux/time.h>
#include <time.h>
#include <android/window.h>
#include "react_native_rcore.h"
#include "Global.h"


#define LOG_TAG "RAYLIB_REACT_NATIVE_RCORE"  // Define the log tag
#define LOGI(...) __android_log_print(ANDROID_LOG_INFO, LOG_TAG, __VA_ARGS__)



// Get elapsed time measure in seconds since InitTimer()
double GetTime(void) {
    double time = 0.0;
    struct timespec ts = {0};
    clock_gettime(CLOCK_MONOTONIC, &ts);
    unsigned long long int nanoSeconds = (unsigned long long int) ts.tv_sec * 1000000000LLU +
                                         (unsigned long long int) ts.tv_nsec;

    time = (double) (nanoSeconds - CORE.Time.base) * 1e-9;  // Elapsed time since InitTimer()

    return time;
}

Vector2 GetWindowScaleDPI(void) {
    return (Vector2) {1.0f, 1.0f};
}

void PollInputEvents(void) {
    // Implementation of PollInputEvents
}

void SwapScreenBuffer() {
    globalEglHandler->swapBuffers();
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

void InitTimer(void)
{
    struct timespec now = { 0 };

    if (clock_gettime(CLOCK_MONOTONIC, &now) == 0)  // Success
    {
        CORE.Time.base = (unsigned long long int)now.tv_sec*1000000000LLU + (unsigned long long int)now.tv_nsec;
    }
    else LOGI("TIMER: Hi-resolution timer not available");


    CORE.Time.previous = GetTime();     // Get time as double
}

void SetupViewport(int width, int height)
{

    rlViewport(CORE.Window.renderOffset.x/2, CORE.Window.renderOffset.y/2, width, height);

    rlMatrixMode(RL_PROJECTION);        // Switch to projection matrix
    rlLoadIdentity();                   // Reset current matrix (projection)

    // Set orthographic projection to current framebuffer size
    // NOTE: Configured top-left corner as (0, 0)
    rlOrtho(0, height, width, 0, 0.0f, 1.0f);

    rlMatrixMode(RL_MODELVIEW);         // Switch back to modelview matrix
    rlLoadIdentity();                   // Reset current matrix (modelview)
}

int InitPlatform(void) {
    // Initialize display basic configuration
    //----------------------------------------------------------------------------
    CORE.Window.currentFbo.width =  500;
    CORE.Window.currentFbo.height = 500;

    InitGraphicsDevice();

    while (!CORE.Window.ready) {
        LOGI("Waiting for EGL initialization");
    }

    rlglInit(500,500);

    // Setup default viewport
    // NOTE: It updated CORE.Window.render.width and CORE.Window.render.height
    SetupViewport(500,500);

    // Initialize hi-res timer
    InitTimer();

    return 0;
}

// Initialize display device and framebuffer
// NOTE: width and height represent the screen (framebuffer) desired size, not actual display size
// If width or height are 0, default display size will be used for framebuffer size
// NOTE: returns false in case graphic device could not be created
int InitGraphicsDevice(void) {
    CORE.Window.fullscreen = true;

    if (globalEglHandler->initialize(_nativeWindow)) {
        LOGI("EGL initialized successfully");
        CORE.Window.ready = true;
        return 0;
    } else {
        LOGI("Failed to initialize EGL context");
        return -1;
    }
}

int GetCurrentMonitor(void){
    LOGI("GetCurrentMonitor is not available on target platform");
    return 0;
}

void ClosePlatform() {
    globalEglHandler->terminate();
}


void SetWindowSize(int width, int height) {
    LOGI("SetWindowSize is not available on target platform");
}
