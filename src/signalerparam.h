#ifndef SIGNALERPARAM_H
#define SIGNALERPARAM_H

#include <QString>
#include <QMap>


class SignalerParam
{
public:
    SignalerParam();
    ~SignalerParam();
    SignalerParam(const SignalerParam &rhs);
    SignalerParam &operator =(const SignalerParam &rhs);

    enum SignalerStatus
    {
        Offline,
        Online
    };

public:
    int signaler_id;
    int signaler_port;
    QString signaler_name;
    QString signaler_ip;
    SignalerStatus signaler_status;
    QString location_desc;
    QString branch_road;
    QString signaler_mode;
    QString software_version;
    QString remark;
};


typedef QMap<int, SignalerParam> SignalerMap;

#endif // SIGNALERPARAM_H
