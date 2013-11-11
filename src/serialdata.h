#ifndef SERIALDATA_H
#define SERIALDATA_H

class SerialData
{
public:
    SerialData();

public:
    const static char head =  0xf1 + '\0';
    const static char tail = 0xed + '\0';
    char type;
    char detector_id;
    char ms_time[4];
};

#endif // SERIALDATA_H
