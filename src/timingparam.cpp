#include "timingparam.h"

TimingParam::TimingParam()
{
    timing_id = 0;
    cycle_time = 0;
    phase_offset = 0;
    coor_phase = 0;
    stage_timing_id = 0;
}

TimingParam::~TimingParam()
{
}

TimingParam::TimingParam(const TimingParam &rhs)
{
    this->timing_id = rhs.timing_id;
    this->cycle_time = rhs.cycle_time;
    this->phase_offset = rhs.phase_offset;
    this->coor_phase = rhs.coor_phase;
    this->stage_timing_id = rhs.stage_timing_id;
}

TimingParam &TimingParam::operator =(const TimingParam &rhs)
{
    this->timing_id = rhs.timing_id;
    this->cycle_time = rhs.cycle_time;
    this->phase_offset = rhs.phase_offset;
    this->coor_phase = rhs.coor_phase;
    this->stage_timing_id = rhs.stage_timing_id;
    return *this;
}

bool TimingParam::operator ==(const TimingParam &rhs)
{
    if (this->timing_id != rhs.timing_id
            || this->cycle_time != rhs.cycle_time
            || this->phase_offset != rhs.phase_offset
            || this->coor_phase != rhs.coor_phase
            || this->stage_timing_id != rhs.stage_timing_id)
    {
        return false;
    }
    return true;
}

bool TimingParam::operator <(const TimingParam &rhs)
{
    if (this->timing_id > rhs.timing_id)
    {
        return false;
    }
    else
    {
        return true;
    }
}
