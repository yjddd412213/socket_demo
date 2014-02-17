#include "stdafx.h"
#include "SaveToOracle.h"

CSaveToOracle::CSaveToOracle()
{

}

CSaveToOracle::CSaveToOracle(IDBConnect *pDBConn, IDBRecordSet *pDBRs)
{
	m_pDBConn = pDBConn;
	m_pDBRs = pDBRs;
}

CSaveToOracle::~CSaveToOracle()
{

}

int CSaveToOracle::SaveTrainPosInfo(TRAINPOS_INFO info)
{
	if (m_pDBConn == NULL)
	{
		return -1;
	}
	char strSql[BUFSIZ] = {0};
	_snprintf_s(strSql, BUFSIZ, "insert into TRAIN_POS_INFO (type, cardid, posx, posy, time)"
						   //"values(%d, '%s', '%s', '%s', (select sysdate from dual))", 
						   "values(%d, '%s', '%s', '%s', to_date('%s', 'yyyy-MM-dd HH24:Mi:ss'))",
		info.iID, (info.strCardID).c_str(), info.strPosX.c_str(), info.strPosY.c_str()//);
		, info.strDateTime.c_str());
	
	return m_pDBConn->Execute(strSql);
}

int CSaveToOracle::SaveRescuePosInfo(RESCUEPOS_INFO info)
{
	if (m_pDBConn == NULL)
	{
		return -1;
	}
	char strSql[BUFSIZ] = {0};
	snprintf(strSql, BUFSIZ, "insert into RESCUE_POS_INFO (type, cardid, LONGITUDE, LATITUDE, time) \
							 values(%d, '%s', '%s', '%s', to_date('%s', 'yyyy-MM-dd HH24:Mi:ss'))", 
		info.iID, info.strCardID.c_str(), info.strLongitude.c_str(), info.strLatitude.c_str(), info.strDateTime.c_str());

	return m_pDBConn->Execute(strSql);
}

int CSaveToOracle::SaveHandsetInfo(HANDSET_INFO info)
{
	if (m_pDBConn == NULL)
	{
		return -1;
	}
	char strSql[BUFSIZ] = {0};
	snprintf(strSql, BUFSIZ, "insert into HANDSET_INFO (type, cardid, CONTENT, time) \
							 values(%d, '%s', '%s', to_date('%s', 'yyyy-MM-dd HH24:Mi:ss'))", 
		info.iID, info.strCardID.c_str(), info.strContent.c_str(), info.strDateTime.c_str());

	return m_pDBConn->Execute(strSql);
}