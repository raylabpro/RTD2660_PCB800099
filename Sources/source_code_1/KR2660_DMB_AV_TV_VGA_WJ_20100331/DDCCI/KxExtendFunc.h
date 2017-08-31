//------------------------------------------------------------------------

typedef struct
{
	BYTE Support;
	WORD Offset;
} SEFLogo,SEFPanel;


typedef struct
{
	BYTE Support;
	WORD Offset;
	char Name[16];
	BYTE Type;
} SEFEdid;


typedef struct
{
	BYTE Support;
	WORD Offset;
	BYTE KeyCount;
} SEFIR,SEFSDKeyInf;


typedef struct
{
	BYTE Support;
	WORD Offset;
	BYTE ADIOCount;
	BYTE ADKeyCount;
} SEFAD;

typedef struct
{
	char Name[16];
	BYTE KeyMessage;
} SEFIRKey,SEFADKey,SEFSDKey;


typedef struct
{
	BYTE Support;
	WORD Offset;
	char Name[16];
	BYTE DefaultValue;
} SEFOther;

//------------------------------------------------------------------------
//------------------------------------------------------------------------


#define _EF_IR_ENABLE_ADDRESS							((_EXTFUNC_REAL_BEGIN_ADDRESS & 0xFFFF) + _EXTFUNC_IR_OFFSET)
#define _EF_IR_KEYMSG_ADDRESS							((_EXTFUNC_REAL_BEGIN_ADDRESS & 0xFFFF) + _EXTFUNC_IR_OFFSET + 1)

#define _EF_SDKEY_ENABLE_ADDRESS						((_EXTFUNC_REAL_BEGIN_ADDRESS & 0xFFFF) + _EXTFUNC_SDKEY_OFFSET)
#define _EF_SDKEY_KEYMSG_ADDRESS						((_EXTFUNC_REAL_BEGIN_ADDRESS & 0xFFFF) + _EXTFUNC_SDKEY_OFFSET + 1)

/*
OFFSET      SIZE          NAME
0                 1            ENABLE(0xFF: Disable 0x00: Enable)
1                 128         LOGO OSD MAP
129              48          PALETTE
177              2            1 Bit Font Offset
179              2            2 Bit Font Offset
181              2            4 Bit Font Offset
183              ????        Logo Table
????             ????        1 Bit Font
????             ????        2 Bit Font
????             ????        4 Bit Font
*/

#define _EF_LOGO_BEGIN_ADDRESS                                  ((_EXTFUNC_REAL_BEGIN_ADDRESS & 0xFFFF) + _EXTFUNC_LOGO_OFFSET)
#define _EF_LOGO_ENABLE_ADDRESS                                     _EF_LOGO_BEGIN_ADDRESS
#define _EF_LOGO_OSDMAP_ADDRESS                               (_EF_LOGO_BEGIN_ADDRESS + 1)
#define _EF_LOGO_PALETTE_ADDRESS                              (_EF_LOGO_BEGIN_ADDRESS + 129)
#define _EF_LOGO_SAVE_1BITFONT_ADDRESS                  (_EF_LOGO_BEGIN_ADDRESS + 177)
#define _EF_LOGO_SAVE_2BITFONT_ADDRESS                  (_EF_LOGO_BEGIN_ADDRESS + 179)
#define _EF_LOGO_SAVE_4BITFONT_ADDRESS                  (_EF_LOGO_BEGIN_ADDRESS + 181)
#define _EF_LOGO_TABLE_ADDRESS                                  (_EF_LOGO_BEGIN_ADDRESS + 183)

#ifdef __KX_EXTENDFUNC__
bit g_fUserPresetLogo = 1;

#else
extern bit g_fUserPresetLogo;

#endif


void KxEFGetRealAddress(void);		// data count 8
void KxEFGetLogoInfo(void);			// data count 3
void KxEFGetEdidGroupCnt(void);		// data count 1
void KxEFGetEdidInfo(BYTE ucIndex);	// data count 20
void KxEFGetIRInfo(void);			// data count 4
void KxEFGetIRKeyInfo(BYTE ucIndex);// data count 17
void KxEFGetIrValue(BYTE *p);

void KxEFGetADPortInfo(void);			// data count 5
void KxEFGetADKeyInfo(BYTE ucIndex);	// data count 17

void KxEFGetADCValue(BYTE *p);			// ?
void KxEFPanelInfo(void);				// 3
void KxEFGetOtherFuncCnt(void);			// data count 1
void KxEFGetOtherFuncInfo(BYTE ucIndex);			// data count 20

void GetExtendEnable(void);
BYTE ScanExtendIR(void);


void KxEFGetSDKeyInfo(void);			// data count 4
void KxEFGetOneSDKeyInfo(BYTE ucIndex); // data count 17
void KxEFGetSDKeyMask(void);			// data count 1
BYTE CIOMaskToKeyMaskExt(BYTE ucIOMask);
	
WORD KxEFLogo1BitAddress(void);
WORD KxEFLogo2BitAddress(void);
WORD KxEFLogo4BitAddress(void);



