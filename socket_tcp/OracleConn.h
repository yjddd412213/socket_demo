#ifndef _oracleConn_h
#define _oracleConn_h



#include "IDBConnect.h"
#include "include/oracle/oci.h"

#include <string>
using namespace std;

class COracleConn : IDBConnect
{
public:
	COracleConn();
	virtual ~COracleConn();
	
public:
	virtual int  Connect(const char *host, const char *user, const char *passwd, const char *db, unsigned int port);
	virtual void Close(void);
	virtual int  Execute(const char * sql);
	virtual int  StorBinData(const char *insert_sql, const char * sql, const char * binfilename);
	virtual	int  ReadBinData(const char * binfilename);

	virtual int IsOpen();

	//virtual int SetConnOptions(enum mysql_option option, const char * arg);
	OCIStmt  * GetResultHandle(void) const { return m_phOCIStmt; };
	OCIError * GetErrorHandle(void)  const { return m_phOCIError; };
	sb4		   SelectLocator(text *sqlstmt);
	ub4		   FileLength(FILE *fp);
	void	   StreamWriteLob(OCILobLocator *lobl, FILE *fp, ub4 filelen);
	void	   StreamReadLob(OCILobLocator *lobl, FILE *fp);

	virtual int BeginTrans(void);
	virtual int RollbackTrans(void);
	virtual int CommitTrans(void);
	virtual int EndTrans(void);

	virtual int GetLastError(void);
	virtual int GetRealString(const char *inBuffer, int length, char * &outBuffer);
	
private:
	OCIEnv		*m_phOCIEnv;		// environment handle
	OCIServer	*m_phOCISrv;		// server handle
	OCIError	*m_phOCIError;		// error handle
	OCISession	*m_phOCISess;		// user session handle
	OCISvcCtx	*m_phOCISvc;		// server context
	OCIStmt		*m_phOCIStmt;
	OCILobLocator *m_phClob;
	OCILobLocator *m_phBlob;
	OCIBind		  *m_phInsertBind;
	OCIBind       *m_phBind;
	OCIDefine     *m_phDefine;

	int	m_nConnStatus;
};

#endif