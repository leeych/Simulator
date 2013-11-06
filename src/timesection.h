#ifndef TIMESECTION_H
#define TIMESECTION_H

class TimeSection
{
public:
    TimeSection();
    ~TimeSection();
    TimeSection(const TimeSection &rhs);
    TimeSection& operator=(const TimeSection &rhs);
    bool operator==(const TimeSection &rhs);
    bool operator<(const TimeSection &rhs);

public:
    unsigned char time_section_id;
    unsigned char event_id;
    unsigned char pattern_id;
    unsigned char start_hour;
    unsigned char start_minute;
    unsigned char ctrl_mode;
    unsigned char aux_func;
    unsigned char spec_func;
};


#endif // TIMESECTION_H
