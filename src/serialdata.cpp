#include "serialdata.h"

SerialData::SerialData():
    type(0x01 + '\0'),
    lane_id(0x01 + '\0')
{
    ms_time[0] = '\0';
    ms_time[1] = '\0';
    ms_time[2] = '\0';
    ms_time[3] = '\0';
}
