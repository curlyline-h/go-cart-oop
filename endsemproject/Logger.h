#pragma once
using namespace System;

public ref class Logger {
public:
    Logger();
    void logError(String^ message);
    void logInfo(String^ message);
};