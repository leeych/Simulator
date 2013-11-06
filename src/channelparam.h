#ifndef CHANNELPARAM_H
#define CHANNELPARAM_H

const int MAX_CHANNEL_COUNT = 255;

class ChannelParam
{
public:
    ChannelParam();
    ChannelParam(const ChannelParam &rhs);

    bool operator<(const ChannelParam &rhs);
    ChannelParam& operator=(const ChannelParam &rhs);
    bool operator==(const ChannelParam &rhs);

public:
    // channel
    unsigned char channel_id;
    unsigned char channel_ctrl_src;
    unsigned char channel_flash;
    unsigned char channel_type;
    // channel hint
    unsigned char channel_direction;
    unsigned char channel_road;
};
#endif // CHANNELPARAM_H
