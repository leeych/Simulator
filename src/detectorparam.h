#ifndef DETECTORPARAM_H
#define DETECTORPARAM_H

class DetectorParam
{
public:
    DetectorParam();
    DetectorParam(const DetectorParam &rhs);
    DetectorParam& operator=(const DetectorParam &rhs);
    bool operator==(const DetectorParam &rhs);
	//bool operator<(const DetectorParam &rhs);
    friend bool operator<(const DetectorParam &left, const DetectorParam &right);

public:
    unsigned char detector_id;
    unsigned int detector_phase_ids;
    unsigned char detector_type;
    unsigned char detector_direction;
    unsigned char detector_delay;
    unsigned char detector_spec_func;
    unsigned char detector_flow;
    unsigned char detector_occupy;

    unsigned char detector_effective_time;
    unsigned char detector_failure_time;
};

#endif // DETECTORPARAM_H
