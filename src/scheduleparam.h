#ifndef SCHEDULEPARAM_H
#define SCHEDULEPARAM_H

class ScheduleParam
{
public:
    explicit ScheduleParam();
    ~ScheduleParam();

    ScheduleParam(const ScheduleParam &rhs);
    ScheduleParam& operator=(const ScheduleParam &rhs);
    bool operator<(const ScheduleParam &rhs);
    bool operator==(const ScheduleParam &rhs);

public:
    unsigned char schedule_id;
    unsigned char schedule_week;
    unsigned char time_section_id;
    unsigned short schedule_month;
    unsigned int schedule_day;
};

#endif // SCHEDULEPARAM_H
