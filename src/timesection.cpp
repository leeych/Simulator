#include "timesection.h"

TimeSection::TimeSection()
{
    time_section_id = 0;
    event_id = 0;
    pattern_id = 0;
    start_hour = 0;
    start_minute = 0;
    ctrl_mode = 0;
    aux_func = 0;
    spec_func = 0;
}

TimeSection::~TimeSection()
{
}

TimeSection::TimeSection(const TimeSection &rhs)
{
    this->time_section_id = rhs.time_section_id;
    this->event_id = rhs.event_id;
    this->pattern_id = rhs.pattern_id;
    this->start_hour = rhs.start_hour;
    this->start_minute = rhs.start_minute;
    this->ctrl_mode = rhs.ctrl_mode;
    this->aux_func = rhs.aux_func;
    this->spec_func = rhs.spec_func;
}

TimeSection &TimeSection::operator =(const TimeSection &rhs)
{
    this->time_section_id = rhs.time_section_id;
    this->event_id = rhs.event_id;
    this->pattern_id = rhs.pattern_id;
    this->start_hour = rhs.start_hour;
    this->start_minute = rhs.start_minute;
    this->ctrl_mode = rhs.ctrl_mode;
    this->aux_func = rhs.aux_func;
    this->spec_func = rhs.spec_func;

    return *this;
}

bool TimeSection::operator ==(const TimeSection &rhs)
{
    if (this->time_section_id != rhs.time_section_id
            || this->event_id != rhs.event_id
            || this->pattern_id != rhs.pattern_id
            || this->start_hour != rhs.start_hour
            || this->start_minute != rhs.start_minute
            || this->ctrl_mode != rhs.ctrl_mode
            || this->aux_func != rhs.aux_func
            || this->spec_func != rhs.spec_func)
    {
        return false;
    }
    return true;
}

bool TimeSection::operator <(const TimeSection &rhs)
{
    if (this->time_section_id < rhs.time_section_id)
    {
        return true;
    }
    else if (this->time_section_id > rhs.time_section_id)
    {
        return false;
    }
    else if (this->event_id <= rhs.event_id)
    {
        return true;
    }
    else
    {
        return false;
    }
}
