#ifndef PHASECONFLICTPARAM_H
#define PHASECONFLICTPARAM_H

class PhaseConflictParam
{
public:
    PhaseConflictParam();
    ~PhaseConflictParam();

    PhaseConflictParam(const PhaseConflictParam &rhs);
    PhaseConflictParam& operator=(const PhaseConflictParam &rhs);
    bool operator==(const PhaseConflictParam &rhs);
    bool operator<(const PhaseConflictParam &rhs);

public:
    unsigned char phase_id;
    unsigned int conflict_phase_id;
};

#endif // PHASECONFLICTPARAM_H
