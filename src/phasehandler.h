#ifndef PHASEHANDLER_H
#define PHASEHANDLER_H

#include "phaseparam.h"
#include "mdatabase.h"
#include <QList>

class PhaseHandler
{
public:
    PhaseHandler();
    ~PhaseHandler();

    void init_database(void *db_ptr);
    void reset_database();

    void init();

    bool addNewPhase();
    bool deletePhase(unsigned char phase_id);
    void set_phase(unsigned char phase_id, const PhaseParam& phase);
    bool get_phase(unsigned char phase_id, PhaseParam& phase);
    bool is_phase_exists(unsigned char phase_id);
    int index_of_phase_list(unsigned char phase_id);
    bool add_phase(const PhaseParam& phase);
    bool remove_phase(unsigned char phase_id);

    QList<PhaseParam *> get_phase_ptr_list();
    QList<PhaseParam> &get_phase_list();
    QList<unsigned char> get_phase_id_list();
	unsigned char get_phase_channel_id(unsigned char phase_id);
	QString get_phase_ctrled_channels_desc(unsigned int channel_ids);
    QList<unsigned char> get_phase_ctrled_channel_list(unsigned char phase_id);
//    unsigned char get_phase_type_by_desc(const QString &desc);
//    QString get_phase_type_desc(unsigned char phase_type);

    bool save_data();

private:
    unsigned char get_max_phase_id();
    void dump_list();

    static bool phase_less_than(const PhaseParam &left, const PhaseParam &right);

private:
    MDatabase* db_;
    QList<PhaseParam> phase_list_;
};

#endif // PHASEHANDLER_H
