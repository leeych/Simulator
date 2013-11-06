#ifndef PHASEPARAM_H
#define PHASEPARAM_H


class PhaseParam
{
public:
    PhaseParam();
    PhaseParam(const PhaseParam &rhs);
    PhaseParam& operator=(const PhaseParam &rhs);
    bool operator==(const PhaseParam &rhs);
    bool operator<(const PhaseParam &rhs);

public:
    unsigned char phase_id;
    unsigned char phase_walk_green;
    unsigned char phase_walk_clear;
    unsigned char phase_min_green;
    unsigned char phase_green_delay;
    unsigned char phase_max_green1;
    unsigned char phase_max_green2;
    unsigned char phase_fix_green;
    unsigned char phase_green_flash;
    unsigned char phase_type;
    unsigned char phase_spec_func;
    unsigned char phase_reserved;

    unsigned int phase_channel;
};

#endif // PHASEPARAM_H
