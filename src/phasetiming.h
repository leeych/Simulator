#ifndef PHASETIMING_H
#define PHASETIMING_H


class PhaseTiming
{
public:
    PhaseTiming();
    ~PhaseTiming();
    PhaseTiming(const PhaseTiming &rhs);
    PhaseTiming& operator =(const PhaseTiming &rhs);
    bool operator==(const PhaseTiming &rhs);
    bool operator<(const PhaseTiming &rhs);

public:
    unsigned char phase_timing_id;
    unsigned char stage_id;
    unsigned char phase_id;
    unsigned char green_time;
    unsigned char yellow_time;
    unsigned char red_time;
    unsigned char spec_func;
    unsigned char delay_time;
};

#endif // PHASETIMING_H
