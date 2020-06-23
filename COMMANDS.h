//COMMANDS.h
//
//Listing of the command numbers to send to the server

//Testing commands
#define CMD_SerialTest					-8
#define CMD_FileTest					-7
#define CMD_ClkAnnounceTest				-6
#define CMD_DelayTest					-5
#define CMD_SemTest						-4
#define CMD_CrashTest					-3
#define CMD_TaskCtrlTest				-2
#define CMD_TimeTest					-1

#define CMD_STOP						0

//API Commands
#define CMD_MpGetVarData				1
#define CMD_MpReadIO					2
#define CMD_MpMonitor					3
#define CMD_MpGetPosVarData				4
#define CMD_MpGetAlarmStatus			5
#define CMD_MpGetAlarmCode				6
#define CMD_MpGetMode					7
#define CMD_MpGetCycle					8
#define CMD_MpGetServoPower				9
#define CMD_MpGetPlayStatus				10
#define CMD_MpGetMasterJob				11
#define CMD_MpGetCurJob					12
#define CMD_MpGetSpecialOpStatus		13
#define CMD_MpGetJobDate				14
#define CMD_MpGetCartPos				15
#define CMD_MpGetPulsePos				16
#define CMD_MpGetFBPulsePos				17
#define CMD_MpGetServoSpeed				18
#define CMD_MpGetFBSpeed				19
#define CMD_MpGetTorque					20
#define CMD_MpGetSysTimes				21
#define CMD_MpGetJogSpeed				22
#define CMD_MpGetJogCoord				23
#define CMD_MpPutVarData				24
#define CMD_MpWriteIO					25
#define CMD_MpPutPosVarData				26
#define CMD_MpCancelError				27
#define CMD_MpResetAlarm				28
#define CMD_MpSetMode					29
#define CMD_MpSetCycle					30
#define CMD_MpSetServoPower				31
#define CMD_MpSetMasterJob				32
#define CMD_MpSetCurJob					33
#define CMD_MpStartJob					34
#define CMD_MpHold						35
#define CMD_MpWaitForJobEnd				36
#define CMD_MpDeleteJob					37
#define CMD_MpConvertJobPtoR			38
#define CMD_MpConvertJobRtoP			39
#define CMD_MpIMOV						40
#define CMD_MpMOVJ						41
#define CMD_MpMOVL						42
#define CMD_MpPulseMOVJ					43
#define CMD_MpPulseMOVL					44
#define CMD_MpGetRobotTickCount			45
#define CMD_MpGetCarPosEx				46
