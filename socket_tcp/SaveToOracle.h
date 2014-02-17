#ifndef _SAVETOORACLE_H
#define _SAVETOORACLE_H

#include "data_format.h"
#include "OracleConn.h"

class CSaveToOracle
{
private:
	IDBConnect *m_pDBConn;
	IDBRecordSet *m_pDBRs;
public:
	CSaveToOracle();
	CSaveToOracle(IDBConnect *pDBConn, IDBRecordSet *pDBRs);
	~CSaveToOracle();
	int SaveTrainPosInfo(TRAINPOS_INFO info);
	int SaveRescuePosInfo(RESCUEPOS_INFO info);
	int SaveHandsetInfo(HANDSET_INFO info);
};



#endif	//_SAVETOORACLE_H
