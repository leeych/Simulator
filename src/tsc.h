#ifndef TCS_H
#define TCS_H

#define MAX_CHAR_NUM         20

#define MAX_SCHEDULE_LINE    40

#define MAX_TIMESECTION_LINE 16
#define MAX_EVENT_LINE       48

#define MAX_PATTERN_LINE     32

#define MAX_TIMECONFIG_LINE  16
#define MAX_STAGE_LINE       32

#define MAX_PHASE_LINE       32

#define MAX_CHANNEL          32
#define MAX_CHANNEL_LINE     MAX_CHANNEL*MAX_PHASE_LINE

#define MAX_DETECTOR         48
#define MAX_WALKKEY          4
#define MAX_BUSDEV           4
#define MAX_DETECTOR_LINE    (MAX_DETECTOR+MAX_WALKKEY+MAX_BUSDEV)*MAX_PHASE_LINE

#define MAX_DETECTOR_DATA    5120

#define MAX_EVENTCLASS_LINE  20

#define MAX_EVENTLOG         255
#define MAX_EVENTLOG_LINE    MAX_EVENTLOG*MAX_EVENTCLASS_LINE

#define MAX_CHANNEL_STATUS	 4

//TSC Param File Header
typedef struct TSCHeader_t
{
    char          		CompanyName[9];
    char          		ProductName[4];
    char          		ProductId[6];
    unsigned char 		LocalIP1;
    unsigned char 		LocalIP2;
    unsigned char 		LocalIP3;
    unsigned char 		LocalIP4;
    unsigned char 		ServerIP1;
    unsigned char 		ServerIP2;
    unsigned char 		ServerIP3;
    unsigned char 		ServerIP4;
    int           		ServerPort;
} TSCHeader_t;

//Unit Table
typedef struct Unit_t
{
    unsigned char 		StartUpFlash;
    unsigned char 		StartUpRed;
    unsigned char 		WorkMode;
    unsigned char 		FlashMode;
    unsigned char 		AlarmFlag2;
    unsigned char 		AlarmFlag1;
    unsigned char 		ShortAlarm;
    unsigned char 		RemoteFlag;
    unsigned char 		FlashFreq;
    unsigned int  		BrightStart;
    unsigned int  		BrightStop;
} Unit_t;

//Schedule Table,c.8 and c.9
typedef struct ScheduleList_t
{
    unsigned char  		ScheduleId;
    unsigned short 		ScheduleMonth;
    unsigned char  		ScheduleWeek;
    unsigned int   		ScheduleDay;
    unsigned char  		TimeSectionId;
} ScheduleList_t;

typedef struct Schedule_t
{
    unsigned char 		FactScheduleNum;
    ScheduleList_t 		ScheduleList[MAX_SCHEDULE_LINE];
} Schedule_t;
//end c.8 and c.9

//TimeSection Table, c.10 and c.11
typedef struct TimeSectionList_t
{
    unsigned char 		TimeSectionId;
    unsigned char 		EventId;
    unsigned char 		StartHour;
    unsigned char 		StartMinute;
    unsigned char 		ControlMode;
    unsigned char 		PatternId;
    unsigned char 		AuxFunc;
    unsigned char 		SpecFunc;
} TimeSectionList_t;

typedef struct TimeSection_t
{
    unsigned char 		FactTimeSectionNum;
    unsigned char 		FactEventNum;
    TimeSectionList_t 	TimeSectionList[MAX_TIMESECTION_LINE][MAX_EVENT_LINE];
} TimeSection_t;
//end c.10 and c.11

//Pattern Table, c.40 and c.41
typedef struct PatternList_t
{
    unsigned char  		PatternId;
    unsigned short 		CycleTime;
    unsigned char  		PhaseOffset;
    unsigned char  		CoordPhase;
    unsigned char  		TimeConfigId;
} PatternList_t;

typedef struct Pattern_t
{
    unsigned char 		FactPatternNum;
    PatternList_t 		PatternList[MAX_PATTERN_LINE];
} Pattern_t;
//end c.40 and c.41

//TimeConfig Table, c.42 and c.43
typedef struct TimeConfigList_t
{
    unsigned char 		TimeConfigId;
    unsigned char 		StageId;
    unsigned int  		PhaseId;
    unsigned char 		GreenTime;
    unsigned char 		YellowTime;
    unsigned char 		RedTime;
    unsigned char 		SpecFunc;
} TimeConfigList_t;

typedef struct TimeConfig_t
{
    unsigned char 		FactTimeConfigNum;
    unsigned char 		FactStageNum;
    TimeConfigList_t 	TimeConfigList[MAX_TIMECONFIG_LINE][MAX_STAGE_LINE];
} TimeConfig_t;
//end c.42 and c.43

//Phase Table,c.18 and c.19
typedef struct PhaseList_t
{
    unsigned char 		PhaseId;
    unsigned char 		PhaseWalkGreen;
    unsigned char 		PhaseWalkClear;
    unsigned char 		PhaseMinGreen;
    unsigned char 		PhaseGreenDelay;
    unsigned char 		PhaseMaxGreen1;
    unsigned char 		PhaseMaxGreen2;
    unsigned char 		PhaseFixGreen;
    unsigned char 		PhaseGreenFlash;
    unsigned char 		PhaseType;
    unsigned char 		PhaseSpecFunc;
    unsigned char 		PhaseReserved;
} PhaseList_t;

typedef struct Phase_t
{
    unsigned char 		FactPhaseNum;
    PhaseList_t 		PhaseList[MAX_PHASE_LINE];
} Phase_t;
//end c.18 and c.19

//Phase Error Table, c.22 and c.23
typedef struct PhaseErrorList_t
{
    unsigned char 		PhaseId;
    unsigned int  		PhaseConflict;
} PhaseErrorList_t;

typedef struct PhaseError_t
{
    unsigned char 		FactPhaseErrorNum;
    PhaseErrorList_t 	PhaseErrorList[MAX_PHASE_LINE];
} PhaseError_t;
//end c.22 and c.23

//Channel Table, c.35 and c.36
typedef struct ChannelList_t
{
    unsigned char 		ChannelId;
    unsigned char 		ChannelCtrlSrc;
    unsigned char 		ChannelFlash;
    unsigned char 		ChannelType;
} ChannelList_t;

typedef struct Channel_t
{
    unsigned short 		FactChannelNum;
    ChannelList_t 		ChannelList[MAX_CHANNEL_LINE];
} Channel_t;
//end c.35 and c.36


//Channel Hint Table
typedef struct ChannelHintList_t
{
    unsigned char 		ChannelId;
    unsigned char 		ChannelDirect;
    unsigned char 		ChannelRoad;
} ChannelHintList_t;

typedef struct ChannelHint_t
{
    unsigned char 		FactChannelHintNum;
    ChannelHintList_t 	ChannelHintList[MAX_CHANNEL];
} ChannelHint_t;

//Detector Table, c.25 and c.26
typedef struct DetectorList_t
{
    unsigned char  		DetectorId;
    unsigned char  		DetectorPhase;
    unsigned char  		DetectorType;
    unsigned char  		DetectorDirect;
    unsigned char  		DetectorDelay;
    unsigned char  		DetectorSpecFunc;
    unsigned short 		DetectorFlow;
    unsigned char  		DetectorOccupy;
} DetectorList_t;

typedef struct Detector_t
{
    unsigned short 		FactDetectorNum;
    DetectorList_t 		DetectorList[MAX_DETECTOR_LINE];
} Detector_t;
//end c.25 and c.26

//Detector Data Table
typedef struct DetectorData_t
{
    unsigned short 		DataId;
    unsigned char  		DetectorId;
    unsigned char  		DetectorData;
    unsigned int   		PhaseId;
    unsigned int   		RecvTime;
} DetectorData_t;

//Event Class Table,c.13 and c.14
typedef struct EventClassList_t
{
    unsigned char 		EventClassId;
    unsigned char 		EventClassRowNum;
    unsigned char 		EventClassNameLen;
    char          		EventClassName[MAX_CHAR_NUM];
    unsigned int  		EventClassClearTime;
} EventClassList_t;

typedef struct EventClass_t
{
    unsigned char 		FactEventClassNum;
    EventClassList_t 	EventClassList[MAX_EVENTCLASS_LINE];
} EventClass_t;
//end c.13 and c.14

//Event Log Table,c.15 and c.16
typedef struct EventLogList_t
{
    unsigned char 		EventClassId;
    unsigned char 		EventLogId;
    unsigned int  		EventLogTime;
    unsigned int  		EventLogValue;
} EventLogList_t;

typedef struct EventLog_t
{
    unsigned short 		FactEventLogNum;
    EventLogList_t 		EventLogList[MAX_EVENTLOG_LINE];
} EventLog_t;
//end c.15 and c.16


//Channel Status Table
typedef struct ChannelStatusList_t
{
    unsigned char           ChannelStatusId;
    unsigned char           ChannelStatusReds;
    unsigned char           ChannelStatusYellows;
    unsigned char           ChannelStatusGreens;
} ChannelStatusList_t;

typedef struct ChannelStatus_t
{
    unsigned char           FactChannelStatusNum;
    ChannelStatusList_t     ChannelStatusList[MAX_CHANNEL_STATUS];
} ChannelStatus_t;

//Drive board status table
#define DRIBOARDNUM     16
typedef struct driboardstatusList_t
{
    unsigned char       dribid;
    unsigned char       status;
}driboardstatusList_t;

typedef struct driboardstatus_t
{
    driboardstatusList_t	driboardstatusList[DRIBOARDNUM];
}driboardstatus_t;

//latest five err info about lamp err or restore
#define FIVEERRLAMPINFO 5
typedef struct fiveerrlampinfoList_t
{
    unsigned char		mark;
    unsigned char		chanid;
    unsigned char		errtype;
}fiveerrlampinfoList_t;

typedef struct fiveerrlampinfo_t
{
    fiveerrlampinfoList_t	fiveerrlampinfoList[FIVEERRLAMPINFO];
}fiveerrlampinfo_t;

#endif // TCS_H
