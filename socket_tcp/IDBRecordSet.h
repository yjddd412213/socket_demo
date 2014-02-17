#ifndef _dbRecordSet_h
#define _dbRecordSet_h


#include <winsock2.h>
 
typedef unsigned __int64 uint64;
typedef unsigned long    ulong;

#define REFRESH_GRANT		1	/* Refresh grant tables */
#define REFRESH_LOG			2	/* Start on new log file */
#define REFRESH_TABLES		4	/* close all tables */
#define REFRESH_HOSTS		8	/* Flush host cache */
#define REFRESH_STATUS		16	/* Flush status variables */
#define REFRESH_THREADS		32	/* Flush thread cache */
#define REFRESH_SLAVE       64  /* Reset master info and restart slave thread */
#define REFRESH_MASTER     128  /* Remove all bin logs in the index and truncate the index */

/* The following can't be set with mysql_refresh() */
#define REFRESH_READ_LOCK	16384	/* Lock tables for read */
#define REFRESH_FAST		32768	/* Intern flag */

/* RESET (remove all queries) from query cache */
#define REFRESH_QUERY_CACHE		65536
#define REFRESH_QUERY_CACHE_FREE 0x20000L /* pack query cache */
#define REFRESH_DES_KEY_FILE	0x40000L
#define REFRESH_USER_RESOURCES	0x80000L

enum FieldTypes { 
	TYPE_INT,
	TYPE_LONG,
	TYPE_FLOAT,
	TYPE_DOUBLE,
	TYPE_DATETIME,
	TYPE_ENUM,
	TYPE_SET,
	TYPE_STRING
};

#define DECLDIR __declspec(dllexport)

class IDBRecordSet
{
public:
	IDBRecordSet(){};
	virtual ~IDBRecordSet(){};

public:
	virtual int Query(const char * sql) = 0;
	virtual void Close(void) = 0;
	virtual int Refresh(unsigned int iOptions) = 0;

	virtual char * GetFieldValue(const char * field) = 0;
	virtual char * GetFieldValue(const int index) = 0;
	virtual int GetFieldValueInt(const char * field) = 0;
	virtual void * GetBinaryData(const char * field) = 0;
	
	virtual long GetFieldsCount(void) = 0;
	virtual uint64 GetRecordCount(void) = 0;
	virtual ulong* GetColumnLength(void) = 0;
	virtual FieldTypes GetFieldType(const int index) const = 0;
	virtual FieldTypes GetFieldType(const char * field) = 0;

	virtual int IsOpen(void) = 0;
	virtual int IsBOF(void) = 0;
	virtual int IsEOF(void) = 0;
	virtual int IsFieldNull(const int index) = 0;
	virtual int IsFieldNull(const char * field) = 0;

	// RecordSet Navigation
	virtual long MoveFirst(void) = 0;
	virtual long MoveLast(void) = 0;
	virtual long MoveNext(void) = 0;
	virtual long MovePrevious(void) = 0;
};

#endif