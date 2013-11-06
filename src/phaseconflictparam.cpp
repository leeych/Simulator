#include "phaseconflictparam.h"

PhaseConflictParam::PhaseConflictParam()
{
    phase_id = 0;
    conflict_phase_id = 0;
}

PhaseConflictParam::~PhaseConflictParam()
{
}

PhaseConflictParam::PhaseConflictParam(const PhaseConflictParam &rhs)
{
    this->phase_id = rhs.phase_id;
    this->conflict_phase_id = rhs.conflict_phase_id;
}

PhaseConflictParam &PhaseConflictParam::operator =(const PhaseConflictParam &rhs)
{
    this->phase_id = rhs.phase_id;
    this->conflict_phase_id = rhs.conflict_phase_id;
    return *this;
}

bool PhaseConflictParam::operator ==(const PhaseConflictParam &rhs)
{
    if (this->phase_id != rhs.phase_id
            || this->conflict_phase_id != rhs.conflict_phase_id)
    {
        return false;
    }
    return true;
}

bool PhaseConflictParam::operator <(const PhaseConflictParam &rhs)
{
	if (this->phase_id <= rhs.phase_id)
	{
		return true;
	}
	return false;
}
