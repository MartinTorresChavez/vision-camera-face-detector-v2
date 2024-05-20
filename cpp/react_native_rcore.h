//
// Created by rodrigo gomes on 17/05/24.
//
#pragma once
#include "raylib.h"
#include <rlgl.h>


#ifdef __cplusplus
extern "C" {
#endif

typedef struct { unsigned int width; unsigned int height; } Size;

struct Render {
    int width;
    int height;
};

struct Framebuffer {
    int width;
    int height;
};

struct Screen {
    int width;
    int height;
};

struct Display {
    int width;
    int height;
};

struct renderOffset {
    int x;
    int y;
};

struct Window {
    Size currentFbo;
    Display display;
    Screen screen;
    Render render;
    renderOffset renderOffset;
    bool ready;
    bool fullscreen;
};



struct CoreData {
    struct {
        unsigned long long int base;
        double previous;
    } Time;

    Window Window;
};


extern CoreData CORE;
void SetWindowSize(int width, int height);
double GetTime(void);
Vector2 GetWindowScaleDPI(void);
void PollInputEvents(void);
void MaximizeWindow(void);
void MinimizeWindow(void);
void RestoreWindow(void);
int InitPlatform(void);
int InitGraphicsDevice(void);
void ClosePlatform(void);
void SetupViewport(int width, int height);
void InitTimer(void);


#ifdef __cplusplus
}
#endif



