#include "scheduleparam.h"

ScheduleParam::ScheduleParam() :
    schedule_id(0),
    schedule_week(0),
    time_section_id(0),
    schedule_month(0),
    schedule_day(0)
{
}

ScheduleParam::~ScheduleParam()
{
}

ScheduleParam::ScheduleParam(const ScheduleParam &rhs)
{
    this->schedule_id = rhs.schedule_id;
    this->schedule_week = rhs.schedule_week;
    this->time_section_id = rhs.time_section_id;
    this->schedule_month = rhs.schedule_month;
    this->schedule_day = rhs.schedule_day;
}

ScheduleParam &ScheduleParam::operator =(const ScheduleParam &rhs)
{
    this->schedule_id = rhs.schedule_id;
    this->schedule_week = rhs.schedule_week;
    this->time_section_id = rhs.time_section_id;
    this->schedule_month = rhs.schedule_month;
    this->schedule_day = rhs.schedule_day;
    return *this;
}

bool ScheduleParam::operator <(const ScheduleParam &rhs)
{
    if (this->schedule_id > rhs.schedule_id)
    {
        return false;
    }
    else if (this->time_section_id > rhs.time_section_id)
    {
        return false;
    }
    else
    {
        return true;
    }
}

bool ScheduleParam::operator ==(const ScheduleParam &rhs)
{
    if (this->schedule_id != rhs.schedule_id
            || this->schedule_week != rhs.schedule_week
            || this->time_section_id != rhs.time_section_id
            || this->schedule_month != rhs.time_section_id
            || this->schedule_day != rhs.schedule_day)
    {
        return false;
    }
    return true;
}
