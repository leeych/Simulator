#include "tscparam.h"
#include <memory.h>

TSCParam::TSCParam()
{
    memset(&tsc_header_, 0x00, sizeof(tsc_header_));
    memset(&unit_param_, 0x00, sizeof(unit_param_));
    memset(&sched_table_, 0x00, sizeof(sched_table_));
    memset(&time_section_table_, 0x00, sizeof(time_section_table_));
    memset(&timing_plan_table_, 0x00, sizeof(timing_plan_table_));
    memset(&stage_timing_table_, 0x00, sizeof(stage_timing_table_));
    memset(&phase_table_, 0x00, sizeof(phase_table_));
    memset(&phase_conflict_table_, 0x00, sizeof(phase_conflict_table_));
    memset(&channel_table_, 0x00, sizeof(channel_table_));
    memset(&channel_hint_table_, 0x00, sizeof(channel_hint_table_));
    memset(&detector_table_, 0x00, sizeof(detector_table_));
}

TSCParam::TSCParam(const TSCParam &rhs)
{
    memcpy(&this->tsc_header_, &rhs.tsc_header_, sizeof(rhs.tsc_header_));
    memcpy(&this->unit_param_, &rhs.unit_param_, sizeof(rhs.unit_param_));
    memcpy(&this->sched_table_, &rhs.sched_table_, sizeof(rhs.sched_table_));
    memcpy(&this->time_section_table_, &rhs.time_section_table_, sizeof(rhs.time_section_table_));
    memcpy(&this->timing_plan_table_, &rhs.timing_plan_table_, sizeof(rhs.timing_plan_table_));
    memcpy(&this->stage_timing_table_, &rhs.stage_timing_table_, sizeof(rhs.stage_timing_table_));
    memcpy(&this->phase_table_, &rhs.phase_table_, sizeof(rhs.phase_table_));
    memcpy(&this->phase_conflict_table_, &rhs.phase_conflict_table_, sizeof(rhs.phase_conflict_table_));
    memcpy(&this->channel_table_, &rhs.channel_table_, sizeof(rhs.channel_table_));
    memcpy(&this->channel_hint_table_, &rhs.channel_hint_table_, sizeof(rhs.channel_hint_table_));
    memcpy(&this->detector_table_, &rhs.detector_table_, sizeof(rhs.detector_table_));
}

TSCParam::~TSCParam()
{
}
