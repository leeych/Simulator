#ifndef COMMAND_H
#define COMMAND_H

#include <string>

class Command
{
public:
//    static std::string DetectorInfo;
    static std::string GetVerId;         // 1
    static std::string BeginMonitor;    // 2
    static std::string EndMonitor;

    static std::string GetLampStatus;   // 3
    static std::string GetConfigure;    // 4
    static std::string GetEventInfo;    // 6
    static std::string GetTSCtime;      // 7
    static std::string GetNetAddress;   // 8
    static std::string GetDetectInfo;   // 9
    static std::string GetDriverInfo;   // 12

    static std::string ClearEventInfo;

    static std::string SetConfigure;
    static std::string ClearDetectInfo;


private:
    Command();
};

#endif // COMMAND_H
