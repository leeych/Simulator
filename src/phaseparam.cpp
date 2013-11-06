#include "phaseparam.h"

PhaseParam::PhaseParam()
{
    phase_id = 0;
    phase_walk_green = 0;
    phase_walk_clear = 0;
    phase_min_green = 0;
    phase_green_delay = 0;
    phase_max_green1 = 0;
    phase_max_green2 = 0;
    phase_fix_green = 0;
    phase_green_flash = 0;
    phase_type = 0;
    phase_spec_func = 0;
    phase_reserved = 0;
    phase_channel = 0;
}

PhaseParam::PhaseParam(const PhaseParam &rhs)
{
    this->phase_id = rhs.phase_id;
    this->phase_walk_green = rhs.phase_walk_green;
    this->phase_walk_clear = rhs.phase_walk_clear;
    this->phase_min_green = rhs.phase_min_green;
    this->phase_green_delay = rhs.phase_green_delay;
    this->phase_max_green1 = rhs.phase_max_green1;
    this->phase_max_green2 = rhs.phase_max_green2;
    this->phase_fix_green = rhs.phase_fix_green;
    this->phase_green_flash = rhs.phase_green_flash;
    this->phase_type = rhs.phase_type;
    this->phase_spec_func = rhs.phase_spec_func;
    this->phase_reserved = rhs.phase_reserved;
    this->phase_channel = rhs.phase_channel;
}

PhaseParam& PhaseParam::operator=(const PhaseParam& rhs)
{
    this->phase_id = rhs.phase_id;
    this->phase_walk_green = rhs.phase_walk_green;
    this->phase_walk_clear = rhs.phase_walk_clear;
    this->phase_min_green = rhs.phase_min_green;
    this->phase_green_delay = rhs.phase_green_delay;
    this->phase_max_green1 = rhs.phase_max_green1;
    this->phase_max_green2 = rhs.phase_max_green2;
    this->phase_fix_green = rhs.phase_fix_green;
    this->phase_green_flash = rhs.phase_green_flash;
    this->phase_type = rhs.phase_type;
    this->phase_spec_func = rhs.phase_spec_func;
    this->phase_reserved = rhs.phase_reserved;
    this->phase_channel = rhs.phase_channel;
    return *this;
}

bool PhaseParam::operator ==(const PhaseParam &rhs)
{
    if (this->phase_id != rhs.phase_id
        || this->phase_walk_green != rhs.phase_walk_green
        || this->phase_walk_clear != rhs.phase_walk_clear
        || this->phase_min_green != rhs.phase_min_green
        || this->phase_green_delay != rhs.phase_green_delay
        || this->phase_max_green1 != rhs.phase_max_green1
        || this->phase_max_green2 != rhs.phase_max_green2
        || this->phase_fix_green != rhs.phase_fix_green
        || this->phase_green_flash != rhs.phase_green_flash
        || this->phase_type != rhs.phase_type
        || this->phase_spec_func != rhs.phase_spec_func
        || this->phase_reserved != rhs.phase_reserved
        || this->phase_channel != rhs.phase_channel)
    {
        return false;
    }
    return true;
}

bool PhaseParam::operator <(const PhaseParam &rhs)
{
    if (this->phase_id > rhs.phase_id)
    {
        return false;
    }
    else if (this->phase_channel > rhs.phase_channel)
    {
        return false;
    }
    else
    {
        return true;
    }
}
