#ifndef TIMINGPARAM_H
#define TIMINGPARAM_H

class TimingParam
{
public:
    TimingParam();
    ~TimingParam();
    TimingParam(const TimingParam &rhs);
    TimingParam& operator=(const TimingParam &rhs);
    bool operator==(const TimingParam &rhs);
    bool operator<(const TimingParam &rhs);

public:
    unsigned char timing_id;
    unsigned char cycle_time;
    unsigned char phase_offset;
    unsigned char coor_phase;
    unsigned char stage_timing_id;
};

#endif // TIMINGPARAM_H
