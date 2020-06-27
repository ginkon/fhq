
#if !defined(TDRIVER_CLASS)
#define TDRIVER_CLASS

#pragma once

#include "winsvc.h"


//¥ÌŒÛ–≈œ¢
#define DRV_SUCCESS						 (DWORD)0	
#define DRV_ERROR_SCM					 (DWORD)-1	
#define DRV_ERROR_SERVICE				 (DWORD)-2	
#define DRV_ERROR_MEMORY				 (DWORD)-3	
#define DRV_ERROR_INVALID_PATH_OR_FILE	 (DWORD)-4	
#define DRV_ERROR_INVALID_HANDLE		 (DWORD)-5	
#define DRV_ERROR_STARTING				 (DWORD)-6	
#define DRV_ERROR_STOPPING				 (DWORD)-7	
#define DRV_ERROR_REMOVING				 (DWORD)-8		
#define DRV_ERROR_IO					 (DWORD)-9	
#define DRV_ERROR_NO_INITIALIZED		 (DWORD)-10		
#define DRV_ERROR_ALREADY_INITIALIZED	 (DWORD)-11	
#define DRV_ERROR_NULL_POINTER			 (DWORD)-12	
#define DRV_ERROR_UNKNOWN				 (DWORD)-13		



class TDriver
{
public:
	TDriver(void);		
	~TDriver(void);	

	DWORD InitDriver(LPCTSTR name, LPCTSTR path, LPCTSTR dosName=NULL);
	DWORD InitDriver(LPCTSTR path);


	DWORD LoadDriver(BOOL start = TRUE);
	DWORD LoadDriver(LPCTSTR name, LPCTSTR path, LPCTSTR dosName=NULL, BOOL start=TRUE);
	DWORD LoadDriver(LPCTSTR path, BOOL start=TRUE);


	DWORD UnloadDriver(BOOL forceClearData = FALSE);
	

	DWORD StartDriver(void);
	DWORD StopDriver(void);


	void SetRemovable(BOOL value);



	BOOL IsInitialized();
	BOOL IsStarted();
	BOOL IsLoaded();

	HANDLE GetDriverHandle(void);

	DWORD WriteIo(DWORD code, PVOID buffer, DWORD count);
	DWORD ReadIo(DWORD code, PVOID buffer, DWORD count);
	DWORD RawIo(DWORD code, PVOID inBuffer, DWORD inCount, PVOID outBuffer, DWORD outCount);
	
private:
	HANDLE driverHandle;
	
	LPTSTR driverName;		
	LPTSTR driverPath;		
	LPTSTR driverDosName;	

	BOOL initialized;	
	BOOL started;
	BOOL loaded;
	BOOL removable;

	DWORD OpenDevice(void);
};

#endif