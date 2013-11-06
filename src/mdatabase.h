#ifndef MDATABASE_H
#define MDATABASE_H

#include "channelparam.h"
#include "detectorparam.h"
#include "phaseparam.h"
#include "phasetiming.h"
#include "timesection.h"
#include "timingparam.h"
#include "scheduleparam.h"
#include "phaseconflictparam.h"

//#include "signalerparam.h"

#include "tsc.h"
#include <stddef.h>
#include <QList>
#include <QMultiMap>

class MDatabase
{
public:
    MDatabase();
    ~MDatabase();

    static MDatabase *GetInstance();
//    {
//        if (instance_ != NULL)
//        {
//            instance_ = new MDatabase;
//        }
//        return instance_;
//    }

    void DestroyInstance();
    void ResetData();

    void set_tsc_header(const TSCHeader_t& header);
    void set_unit_table(const Unit_t &ut);
    void set_schedule_table(const QList<ScheduleParam>& sched_list);
    void set_schedule_table(const Schedule_t &schedule);

    void set_timesection_table(const QMultiMap<unsigned char, TimeSection> &tst);
    void set_timesection_table(const TimeSection_t &timesection);

    void set_timing_table(const QList<TimingParam> &tp_list);
    void set_timing_table(const Pattern_t &plan);

    void set_phasetiming_table(const QMultiMap<unsigned char, PhaseTiming> &stage_timing_plan);
    void set_phasetiming_table(const TimeConfig_t &timeconfig);

    void set_phase_table(const QList<PhaseParam> &phase_list);
    void set_phase_table(const Phase_t &phase);

    void set_channel_table(const QList<ChannelParam> &channel_list);
    void set_channel_table(const Channel_t &channel);
    void set_channel_hint_table(const ChannelHint_t &channel_hint);

    void set_phase_conflict_table(const QList<PhaseConflictParam> &conflict_list);
    void set_phase_conflict_table(const PhaseError_t &phase_err);

    void set_detector_table(const QList<DetectorParam> &detector_list);
    void set_detector_table(const Detector_t &detector);

//    void set_signaler(const SignalerMap &signaler);

    TSCHeader_t &get_tsc_header();
    Unit_t &get_unit_table();
    Schedule_t &get_schedule();
    TimeSection_t &get_timesection();
    Pattern_t &get_timingplan();
    TimeConfig_t &get_timeconfig();
    Phase_t &get_phase();
    PhaseError_t &get_phase_err();
    Channel_t &get_channel();
    ChannelHint_t &get_channel_hint();
    Detector_t &get_detector();

    QList<ScheduleParam> get_schedule_table();
    QList<TimeSection> get_timesection_table();
    QList<TimingParam> get_timing_table();
    QList<PhaseTiming> get_timeconfig_table();
    QList<PhaseParam> get_phase_table();
    QList<ChannelParam> get_channel_table();
    QList<DetectorParam> get_detector_table();
    QList<PhaseConflictParam> get_phase_conflict_table();

//    SignalerMap &get_signaler_map();


private:
	unsigned char get_phasetiming_phase_id(unsigned int phase_id_bits);
    QList<unsigned char> get_id_list_by_bits_op(unsigned int phase_ids);
	int index_of_channel_hint_table(unsigned char channel_id);
	static bool phasetiming_less_than(const PhaseTiming &left, const PhaseTiming &right);
	static bool timesection_less_than(const TimeSection &left, const TimeSection &right);
	static bool channel_less_than(const ChannelParam &left, const ChannelParam &right);
	static bool detector_less_than(const DetectorParam &left, const DetectorParam &right);

private:
    static MDatabase* instance_;

private:
    TSCHeader_t     tsc_header_;
    Schedule_t      sched_table_;
    Unit_t          unit_table_;
    TimeSection_t   timesection_table_;
    Pattern_t       pattern_table_;
    TimeConfig_t    timeconfig_table_;
    Phase_t         phase_table_; 
    Channel_t       channel_table_;
	ChannelHint_t	channel_hint_table_;
    PhaseError_t    phase_conflict_table_;
    Detector_t      detector_table_;

//    SignalerMap     signaler_map_;

private:
    QMap<unsigned char, unsigned short> cycle_time_map_;
    QMultiMap<unsigned char, unsigned char> channel_phase_map_; // for write to file

    QMultiMap<unsigned char, unsigned char> channel_phase_read_map_;    // for read from file
	void init_channel_ctrl_src_phase();

};

#endif // MDATABASE_H
