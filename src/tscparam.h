#ifndef TSCPARAM_H
#define TSCPARAM_H

#include "tsc.h"

class TSCParam
{
public:
    TSCParam();
    TSCParam(const TSCParam &rhs);
    ~TSCParam();

public:
    TSCHeader_t     tsc_header_;
    Unit_t          unit_param_;
    Schedule_t      sched_table_;
    TimeSection_t   time_section_table_;
    Pattern_t       timing_plan_table_;
    TimeConfig_t    stage_timing_table_;
    Phase_t         phase_table_;
    PhaseError_t    phase_conflict_table_;
    Channel_t       channel_table_;
    ChannelHint_t   channel_hint_table_;
    Detector_t      detector_table_;
};

#endif // TSCPARAM_H
