#include "channelparam.h"

ChannelParam::ChannelParam()
{
    channel_id = 0;
    channel_ctrl_src = 0;
    channel_flash = 0;
    channel_type = 0;

    channel_direction = 0;
    channel_road = 0;
}

ChannelParam::ChannelParam(const ChannelParam &rhs)
{
    this->channel_id = rhs.channel_id;
    this->channel_ctrl_src = rhs.channel_ctrl_src;
    this->channel_flash = rhs.channel_flash;
    this->channel_type = rhs.channel_type;

    this->channel_direction = rhs.channel_direction;
    this->channel_road = rhs.channel_road;
}

bool ChannelParam::operator <(const ChannelParam &rhs)
{
    if (this->channel_id > rhs.channel_id)
    {
        return false;
    }
    else if (this->channel_ctrl_src > rhs.channel_ctrl_src)
    {
        return false;
    }
    else
    {
        return true;
    }
}

ChannelParam &ChannelParam::operator =(const ChannelParam &rhs)
{
    this->channel_id = rhs.channel_id;
    this->channel_ctrl_src = rhs.channel_ctrl_src;
    this->channel_flash = rhs.channel_flash;
    this->channel_type = rhs.channel_type;

    this->channel_direction = rhs.channel_direction;
    this->channel_road = rhs.channel_road;

    return *this;
}

bool ChannelParam::operator ==(const ChannelParam &rhs)
{
    if (this->channel_id != rhs.channel_id
        || this->channel_ctrl_src != rhs.channel_ctrl_src
        || this->channel_flash != rhs.channel_flash
        || this->channel_type != rhs.channel_type
        || this->channel_direction != rhs.channel_direction
        || this->channel_road != rhs.channel_road)
    {
        return false;
    }
    return true;
}
