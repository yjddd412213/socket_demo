#ifndef _DATA_FORMAT_H
#define _DATA_FORMAT_H

#include "stdafx.h"

enum TYPEID{
	TRAIN_POS		= 0,
	PLANE_POS		= 1,
	CAR_POS			= 2,
	SEARCHER_POS	= 31,
	DAMAGE_INFO		= 32,
	RESCUE_INFO		= 33
};

enum DB_ERRNO
{
	WRONG_DATATYPE
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
#endif	//_DATA_FORMAT_H
