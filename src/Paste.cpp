#include <iostream>
#include <fstream>
#include <vector>
#include <future>
#include <string>
#include <chrono>
#include <thread>
#include <sys/stat.h>
#include <cstdio>

#include "Paste.hpp"

namespace {
    std::string RunCmd(const char* command) {
        char buffer[128];
        std::string ret;
        FILE *pipe = popen(command, "r");
        if (pipe != nullptr) {
            while (!feof(pipe)) {
                if (fgets(buffer, 128, pipe) != nullptr) {
                    ret += buffer;
                }
            }
            pclose(pipe);
        }
        return ret;
    }

    bool FileExists(const std::string& path) {
        struct stat buffer;
        if (stat(path.c_str(), &buffer) == 0) {
            return S_ISREG(buffer.st_mode);
        } else {
            return false;
        }
    }

    // Dex储存路径
    const std::string FilePath = "/data/adb/ET_Paste.dex";

    bool InitDex() {
        if (FileExists(FilePath)) return true;

        std::ofstream OutFile(FilePath, std::ios::binary);
        if (!OutFile) return false;

        OutFile.write(reinterpret_cast<const char*>(DexFile.data()), DexFile.size());
        OutFile.close();
        if (!OutFile) {
            std::remove(FilePath.c_str());
            return false;
        }
        return true;
    }
}

std::string ET::Paste() {
    if (!InitDex()) return "";

    std::string str = RunCmd("app_process64 -Djava.class.path=/data/adb/ET_Paste.dex /system/bin com.example.mylibrary.Main");

    if (!str.empty() && str.back() == '\n') {
        str.pop_back();
    }

    return str;
}

void ET::NB::Paste(bool* Switch, std::string* Str) {
    static std::future<std::string> Ret;
    static bool Flag = false;

    if (*Switch) {
        Ret = std::async(std::launch::async, []() {
            return ET::Paste();
        });
        *Switch = false;
        Flag = true;
    }

    if (Flag) {
        if (Ret.wait_for(std::chrono::seconds(0)) == std::future_status::ready) {
            *Str = Ret.get();
            Flag = false;
        }
    }
}
