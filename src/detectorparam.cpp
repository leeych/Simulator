#include "detectorparam.h"

DetectorParam::DetectorParam()
{
    detector_id = 0;
    detector_phase_ids = 0;
    detector_type = 0;
    detector_direction = 0;
    detector_delay = 0;
    detector_spec_func = 0;
    detector_flow = 0;
    detector_occupy = 0;

    detector_effective_time = 0;
    detector_failure_time = 0;
}

DetectorParam::DetectorParam(const DetectorParam &rhs)
{
    this->detector_id = rhs.detector_id;
    this->detector_phase_ids = rhs.detector_phase_ids;
    this->detector_type = rhs.detector_type;
    this->detector_direction = rhs.detector_direction;
    this->detector_delay = rhs.detector_delay;
    this->detector_spec_func = rhs.detector_spec_func;
    this->detector_flow = rhs.detector_flow;
    this->detector_occupy = rhs.detector_occupy;
    this->detector_effective_time = rhs.detector_effective_time;
    this->detector_failure_time = rhs.detector_failure_time;
}

DetectorParam &DetectorParam::operator =(const DetectorParam &rhs)
{
	if (*this == rhs)
	{
		return *this;
	}
    this->detector_id = rhs.detector_id;
    this->detector_phase_ids = rhs.detector_phase_ids;
    this->detector_type = rhs.detector_type;
    this->detector_direction = rhs.detector_direction;
    this->detector_delay = rhs.detector_delay;
    this->detector_spec_func = rhs.detector_spec_func;
    this->detector_flow = rhs.detector_flow;
    this->detector_occupy = rhs.detector_occupy;
    this->detector_effective_time = rhs.detector_effective_time;
    this->detector_failure_time = rhs.detector_failure_time;

    return *this;
}

bool DetectorParam::operator ==(const DetectorParam &rhs)
{
    if (this->detector_id != rhs.detector_id
//        || this->detector_phase_ids != rhs.detector_phase_ids
        || this->detector_type != rhs.detector_type
        || this->detector_direction != rhs.detector_direction
        || this->detector_delay != rhs.detector_delay
        || this->detector_spec_func != rhs.detector_spec_func
        || this->detector_flow != rhs.detector_flow
        || this->detector_occupy != rhs.detector_occupy
        || this->detector_effective_time != rhs.detector_effective_time
        || this->detector_failure_time != rhs.detector_failure_time)
    {
        return false;
    }
    return true;
}

//bool DetectorParam::operator <(const DetectorParam &rhs)
//{
//    if (this->detector_id > rhs.detector_id)
//    {
//        return false;
//    }
//    else if (this->detector_phase_ids > rhs.detector_phase_ids)
//    {
//        return false;
//    }
//    else
//    {
//        return true;
//    }
//}

bool operator<( const DetectorParam &left, const DetectorParam &right )
{
	if (left.detector_id > right.detector_id)
	{
		return false;
	}
	else if (left.detector_phase_ids > right.detector_phase_ids)
	{
		return false;
	}
	else 
	{
		return true;
	}
}