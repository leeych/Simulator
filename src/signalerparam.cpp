#include "signalerparam.h"

SignalerParam::SignalerParam()
    : signaler_id(0),
      signaler_port(1024),
      signaler_status(Offline)
{
}

SignalerParam::~SignalerParam()
{
}

SignalerParam::SignalerParam(const SignalerParam &rhs)
{
    signaler_id = rhs.signaler_id;
    signaler_port = rhs.signaler_port;
    signaler_status = rhs.signaler_status;
    signaler_name = rhs.signaler_name;
    signaler_ip = rhs.signaler_ip;
    location_desc = rhs.location_desc;
    branch_road = rhs.branch_road;
    signaler_mode = rhs.signaler_mode;
    software_version = rhs.software_version;
    remark = rhs.remark;
}

SignalerParam &SignalerParam::operator =(const SignalerParam &rhs)
{
    if (this == &rhs)
    {
        return *this;
    }

    signaler_id = rhs.signaler_id;
    signaler_port = rhs.signaler_port;
    signaler_status = rhs.signaler_status;
    signaler_name = rhs.signaler_name;
    signaler_ip = rhs.signaler_ip;
    location_desc = rhs.location_desc;
    branch_road = rhs.branch_road;
    signaler_mode = rhs.signaler_mode;
    software_version = rhs.software_version;
    remark = rhs.remark;

    return *this;
}
