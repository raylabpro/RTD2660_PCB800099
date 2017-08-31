

#define USA_CATV_MAX_CHANNEL	        126
#define USA_AIR_MAX_CHANNEL		        69
#define KOR_CATV_MAX_CHANNEL	        134
#define KOR_AIR_MAX_CHANNEL		        77
#define JAP_CATV_MAX_CHANNEL	        63
#define JAP_AIR_MAX_CHANNEL	        	62
#define TAIWAN_CATV_MAX_CHANNEL	        127//126
#define TAIWAN_AIR_MAX_CHANNEL	        70

#define _CATV_MAX_CHANNEL               TAIWAN_CATV_MAX_CHANNEL
#define _AIR_MAX_CHANNEL                TAIWAN_AIR_MAX_CHANNEL

//--------------------------------------------------------------
#define JS6AM_USA_FRQ                   0
#define JS6AM_KOR_FRQ                   1
#define JS6AM_JAP_FRQ                   2
#define JS6AM_TAIWAN_FRQ				3

#define JS6AM_TYPE                      JS6AM_TAIWAN_FRQ
//--------------------------------------------------------------
extern WORD code tNTSC_AIR[_AIR_MAX_CHANNEL];
extern WORD code tNTSC_CATV[_CATV_MAX_CHANNEL];
