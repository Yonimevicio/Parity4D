#pragma once
#include "IMGUI/imgui.h"
class Console
{
public:
    Console();
    ~Console();

    void ClearLog();
    void Draw(const char* title, bool* p_open, int width = 1080 , int height = 300);
    int  Stricmp(const char* s1, const char* s2);
    int  Strnicmp(const char* s1, const char* s2, int n);
    char* Strdup(const char* s);
    void Strtrim(char* s);
    void AddLog(const char* fmt, ...) IM_FMTARGS(2);

private:
    char                  InputBuf[4096];
    ImVector<char*>       Items;
    ImVector<const char*> Commands;
    ImVector<char*>       History;
    int                   HistoryPos;    // -1: new line, 0..History.Size-1 browsing history.
    ImGuiTextFilter       Filter;
    bool                  AutoScroll;
    bool                  ScrollToBottom;
	int width, height;
};

