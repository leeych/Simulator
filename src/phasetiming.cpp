#include "phasetiming.h"

PhaseTiming::PhaseTiming()
{
    phase_timing_id = 0;
    stage_id = 0;
    phase_id = 0;
    green_time = 0;
    yellow_time = 0;
    red_time = 0;
    spec_func = 0;
    delay_time = 0;
}

PhaseTiming::~PhaseTiming()
{
}

PhaseTiming::PhaseTiming(const PhaseTiming &rhs)
{
    this->phase_timing_id = rhs.phase_timing_id;
    this->stage_id = rhs.stage_id;
    this->phase_id = rhs.phase_id;
    this->green_time = rhs.green_time;
    this->yellow_time = rhs.yellow_time;
    this->red_time = rhs.red_time;
    this->spec_func = rhs.spec_func;
    this->delay_time = rhs.delay_time;
}

bool PhaseTiming::operator ==(const PhaseTiming &rhs)
{
    if (this->phase_timing_id != rhs.phase_timing_id
            || this->stage_id != rhs.stage_id
            || this->phase_id != rhs.phase_id
            || this->green_time != rhs.green_time
            || this->yellow_time != rhs.yellow_time
            || this->red_time != rhs.red_time
            || this->spec_func != rhs.spec_func
            || this->delay_time != rhs.delay_time)
    {
        return false;
    }
    return true;
}

bool PhaseTiming::operator <(const PhaseTiming &rhs)
{
    if (this->phase_timing_id > rhs.phase_timing_id)
    {
        return false;
    }
    else if (this->stage_id > rhs.stage_id)
    {
        return false;
    }
    else if (this->phase_id > rhs.phase_id)
    {
        return false;
    }
    else
    {
        return true;
    }
}

PhaseTiming &PhaseTiming::operator =(const PhaseTiming &rhs)
{
    this->phase_timing_id = rhs.phase_timing_id;
    this->stage_id = rhs.stage_id;
    this->phase_id = rhs.phase_id;
    this->green_time = rhs.green_time;
    this->yellow_time = rhs.yellow_time;
    this->red_time = rhs.red_time;
    this->spec_func = rhs.spec_func;
    this->delay_time = rhs.delay_time;

    return *this;
}
