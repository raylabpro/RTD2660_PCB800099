

#define __OSDTABLE003__


#include "Core\Header\Include.h"


#if(_OSD_TYPE == _OSD003)

//------------------------------------------------------------




// Menu item's define
// Option : _DISABLE_NOT_SHOW,_EN_PUB_KEYEVENT,_KEYMAP_EN_IN_NOSIGNAL
code SMenuItem g_tMenuItem[] = 
{

// Table
    // _MI_MENU_NONE
    {
        _EN_PUB_KEYEVENT | _KEYMAP_EN_IN_NOSIGNAL,       //BYTE Option;
        tKOMenuNone,            //SKeyToOsdEvent *KeyMsgToOsdEvnet;
        MMenuNoneProc,          //funcpProc Proc;
        CEnable,                //funcpEnable Enable;
    },
    // MainMenu\CONTRAST(_MI_CONTRAST)
    {
        _EN_PUB_KEYEVENT,       //BYTE Option;
        tKOContrastMenu,            //SKeyToOsdEvent *KeyMsgToOsdEvnet;
        MMainMenuProc,          //funcpProc Proc;
        CEnable,                //funcpEnable Enable;
    },
    // MainMenu\BRIGHTNESS(_MI_BRIGHTNESS)
    {
        _EN_PUB_KEYEVENT,       //BYTE Option;
        tKOBrightnessMenu,            //SKeyToOsdEvent *KeyMsgToOsdEvnet;
        MMainMenuProc,          //funcpProc Proc;
        CEnable,                //funcpEnable Enable;
    },
    // MainMenu\HUE(_MI_HUE)
    {
        _EN_PUB_KEYEVENT,       //BYTE Option;
        tKOMainMenu,            //SKeyToOsdEvent *KeyMsgToOsdEvnet;
        MMainMenuProc,          //funcpProc Proc;
        CVideoNTSCEnable,       //funcpEnable Enable;
    },
    // MainMenu\SATURATION(_MI_SATURATION)
    {
        _EN_PUB_KEYEVENT,       //BYTE Option;
        tKOSaturationMenu,      //SKeyToOsdEvent *KeyMsgToOsdEvnet;
        MMainMenuProc,          //funcpProc Proc;
        CEnable,                //funcpEnable Enable;
    },
	// MainMenu\AUDIO(_MI_AUDIO)
	{
		_EN_PUB_KEYEVENT,		//BYTE Option;
		tKOVolumeMenu,			//SKeyToOsdEvent *KeyMsgToOsdEvnet;
		MMainMenuProc,			//funcpProc Proc;
		CEnable,				//funcpEnable Enable;
	},
	// MainMenu\_MI_ATUOADJ(_MI_ATUOADJ)
	{
		_EN_PUB_KEYEVENT,		//BYTE Option;
		tKOVolumeMenu,			//SKeyToOsdEvent *KeyMsgToOsdEvnet;
		MMainMenuProc,			//funcpProc Proc;
		CVgaEnable,				//funcpEnable Enable;
	},
    // MainMenu\SOURCE(_MI_SOURCE)
    {
        _EN_PUB_KEYEVENT,       //BYTE Option;
        tKOMainMenu,            //SKeyToOsdEvent *KeyMsgToOsdEvnet;
        MMainMenuProc,          //funcpProc Proc;
        CEnable,                //funcpEnable Enable;
    },
    // MainMenu\LANGUAGE(_MI_LANGUAGE)
    {
        _EN_PUB_KEYEVENT,       //BYTE Option;
        tKOMainMenu,            //SKeyToOsdEvent *KeyMsgToOsdEvnet;
        MMainMenuProc,          //funcpProc Proc;
        CEnable,//CDisable,                //funcpEnable Enable;
    },
    // MainMenu\FM(_MI_FM_SEND)
    {
        _EN_PUB_KEYEVENT,       //BYTE Option;
        tKOMainMenu,            //SKeyToOsdEvent *KeyMsgToOsdEvnet;
        MMainMenuProc,          //funcpProc Proc;
        CEnable,                //funcpEnable Enable;
    },		
    // MainMenu\LR_SWAP(_MI_LR_SWAP)
    {
        _EN_PUB_KEYEVENT,       //BYTE Option;
        tKOMainMenu,            //SKeyToOsdEvent *KeyMsgToOsdEvnet;
        MMainMenuProc,          //funcpProc Proc;
        CPanelLRUD,                //funcpEnable Enable;
    },
    // MainMenu\UD_SWAP(_MI_UD_SWAP)
    {
        _EN_PUB_KEYEVENT,       //BYTE Option;
        tKOMainMenu,            //SKeyToOsdEvent *KeyMsgToOsdEvnet;
        MMainMenuProc,          //funcpProc Proc;
        CPanelLRUD,                //funcpEnable Enable;
    },
    // MainMenu\DISPLAY_RATIO(_MI_DISPLAY_RATIO)
    {
        _EN_PUB_KEYEVENT,       //BYTE Option;
        tKOMainMenu,            //SKeyToOsdEvent *KeyMsgToOsdEvnet;
        MMainMenuProc,          //funcpProc Proc;
        MDisplayRatioEnable,    //funcpEnable Enable;
    },    
//----------------------------TV_START------------------------------------------------
    // MainMenu\SYSTEM(_MI_SYSTEM)
    {
        _EN_PUB_KEYEVENT,       //BYTE Option;
        tKOMainMenu,            //SKeyToOsdEvent *KeyMsgToOsdEvnet;
        MMainMenuProc,          //funcpProc Proc;
        CDisable,//CTVEnable, 		        //funcpEnable Enable;
    },
    // MainMenu\AUTOSEARCH(_MI_AUTOSEARCH)
    {
        _EN_PUB_KEYEVENT,       //BYTE Option;
        tKOMainMenu,            //SKeyToOsdEvent *KeyMsgToOsdEvnet;
        MMainMenuProc,          //funcpProc Proc;
        CDisable, 		        //funcpEnable Enable;
    },
    // MainMenu\MANUALSEARCH(_MI_MANUALSEARCH)
    {
        _EN_PUB_KEYEVENT,       //BYTE Option;
        tKOMainMenu,            //SKeyToOsdEvent *KeyMsgToOsdEvnet;
        MMainMenuProc,          //funcpProc Proc;
        CDisable, 		        //funcpEnable Enable;
    },
    // MainMenu\TUNING(_MI_TUNING)
    {
        _EN_PUB_KEYEVENT,       //BYTE Option;
        tKOMainMenu,            //SKeyToOsdEvent *KeyMsgToOsdEvnet;
        MMainMenuProc,          //funcpProc Proc;
        CDisable, 		        //funcpEnable Enable;
    },
    // MainMenu\CHANNEL(_MI_CHANNEL)
    {
        _EN_PUB_KEYEVENT,       //BYTE Option;
        tKOMainMenu,            //SKeyToOsdEvent *KeyMsgToOsdEvnet;
        MMainMenuProc,          //funcpProc Proc;
        CDisable, 		        //funcpEnable Enable;
    },
//----------------------------TV_END------------------------------------------------
    // MainMenu\RESET(_MI_RESET)
    {
        _EN_PUB_KEYEVENT,       //BYTE Option;
        tKOMainMenu,            	//SKeyToOsdEvent *KeyMsgToOsdEvnet;
        MMainMenuProc,          //funcpProc Proc;
        CEnable,                //funcpEnable Enable;
    },
    // MainMenu\EXIT(_MI_EXIT)
    {
        _EN_PUB_KEYEVENT,       //BYTE Option;
        tKOExit,            	//SKeyToOsdEvent *KeyMsgToOsdEvnet;
        MMainMenuProc,          //funcpProc Proc;
        CEnable,                //funcpEnable Enable;
    },

};
//------------------------------------------------------------



#endif 	//#if(_OSD_TYPE == _OSD003)

