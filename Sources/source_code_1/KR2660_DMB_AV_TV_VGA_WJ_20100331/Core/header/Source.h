//----------------------------------------------------------------------------------------------------
// ID Code      : Source.h No.0002
// Update Note  : 
//
//----------------------------------------------------------------------------------------------------

//----------------------------------------------------------------------------------------------------

#ifdef __SOURCE__

//--------------------------------------------------
// Global Variables
//--------------------------------------------------
bit bInterlaceMode = 0;

//--------------------------------------------------
// Function Prototypes
//--------------------------------------------------
bit CSourceHandler(void);
BYTE CGetSourcePortType(BYTE ucSource);
bit CSourceScanInputPort(BYTE ucSource);
bit CSourceScanInputPortVGA(BYTE ucAnalogSource);
bit CSourceScanInputPortDVI(BYTE ucPar);

#else

//--------------------------------------------------
// Extern Global Variables
//--------------------------------------------------
extern bit bInterlaceMode;

//--------------------------------------------------
// Extern Function Prototypes
//--------------------------------------------------
extern bit CSourceHandler(void);
extern BYTE CGetSourcePortType(BYTE ucSource);
extern bit CSourceScanInputPortDVI(BYTE ucPar);
extern bit bSourceVideo(void);

#endif 


//--------------------------------------------------
// Macro of Interlace Mode Check
//--------------------------------------------------	
#define GET_INTERLACE_MODE()            	(bInterlaceMode)
#define SET_INTERLACE_MODE()            	(bInterlaceMode = 1)
#define CLR_INTERLACE_MODE()            	(bInterlaceMode = 0)


