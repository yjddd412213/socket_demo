#ifndef _dbConnect_h
#define _dbConnect_h

#include "IDBRecordSet.h"

#define DECLDIR __declspec(dllexport)

enum DB_TYPE {TP_MYSQL, TP_ORACLE};

class IDBConnect
{
// Construction and Destruction
public:
	IDBConnect();
	virtual ~IDBConnect();

public:
	virtual int Connect( const char *host, 
						 const char *user, 
						 const char *passwd, 
						 const char *db, 
						 unsigned int port) = 0;
	virtual void Close(void) = 0;
	virtual int Execute(const char * sql) = 0;

	// connection status
	virtual int IsOpen(void) = 0;

	// reserved
	//virtual int SetConnOptions(enum mysql_option option, const char * arg) = 0;

	// transaction
	virtual int BeginTrans(void) = 0;
	virtual int RollbackTrans(void) = 0;
	virtual int CommitTrans(void) = 0;
	virtual int EndTrans(void) = 0;

	virtual int GetLastError(void) = 0;
	virtual int GetRealString(const char *inBuffer, int length, char *&outBuffer) = 0;
};

DECLDIR void InitDBEngine(const char * pSelDBType);

DECLDIR IDBConnect * ConnDBServer(const char *host, 
		   					      const char *user, 
						          const char *passwd, 
						          const char *db, 
						          unsigned int port);

/*****************************************************/
DECLDIR void SetConnectParam(const char *host, 
							 const char *user, 
							 const char *passwd, 
							 const char *db, 
							 unsigned int port);
DECLDIR int  ExecSQL(const char *sql);
/*****************************************************/

DECLDIR IDBConnect	 * CreateConnInst(void);
DECLDIR IDBRecordSet * CreateRsInst(IDBConnect *pIDBConn);

DECLDIR void DestroyInstance(IDBConnect   *&pDBConn);
DECLDIR void DestroyInstance(IDBRecordSet *&pDBRs);

DECLDIR void Close(IDBConnect *&pDBConn);
DECLDIR void Close(IDBRecordSet *&pDBRs);

#endif