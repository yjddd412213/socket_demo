#ifndef _DATA_FORMAT_H
#define _DATA_FORMAT_H

#include "stdafx.h"

#define IPLENGTH		15
enum TYPEID{	//34医院准备消息 35图片信息 5派车 6心率
	TRAIN_POS		= 0,
	PLANE_POS		= 1,
	PERSON_POS		= 12,
	CAR_POS			= 2,
	SEARCHER_POS	= 31,
	DAMAGE_INFO		= 32,
	RESCUE_INFO		= 33
};

enum DB_ERRNO
{
	WRONG_DATATYPE	= -1,
	NONEEDTODEAL	= 0
};

struct TRAINPOS_INFO
{
	int				iID;
	std::string		strPosX;
	std::string		strPosY;
	std::string		strCardID;
	std::string		strDateTime;		
};

struct RESCUEPOS_INFO
{
	int			    iID;	
	int				iHeartRate;
	std::string	    strLongitude;
	std::string	    strLatitude;
	std::string		strCardID;
	std::string		strDateTime;		
};

struct HANDSET_INFO
{
	int			    iID;
	std::string		strCardID;
	std::string		strContent;
	std::string		strDateTime;		
};

struct SERVER_INFO
{
	int				iPort;
	char			strIP[IPLENGTH];
};
#endif	//_DATA_FORMAT_H

