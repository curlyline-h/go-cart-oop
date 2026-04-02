#include <windows.h>
#include <servprov.h>
#include <urlmon.h>

#include "Logger.h"

#include <msclr/marshal_cppstd.h>
#include <fstream>

Logger::Logger() {}

void Logger::logError(String^ message) {
    std::ofstream file("log.txt", std::ios::app);
    msclr::interop::marshal_context context;
    std::string msg = context.marshal_as<std::string>(message);
    file << "[ERROR] " << msg << "\n";
    file.close();
}

void Logger::logInfo(String^ message) {
    std::ofstream file("log.txt", std::ios::app);
    msclr::interop::marshal_context context;
    std::string msg = context.marshal_as<std::string>(message);
    file << "[INFO] " << msg << "\n";
    file.close();
}