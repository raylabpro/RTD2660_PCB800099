//----------------------------------------------------------------------------------------------------
// ID Code      : YPbPr.h No.0000
// Update Note  :
//
//----------------------------------------------------------------------------------------------------

#if(_YPBPR_SUPPORT == _ON)

//--------------------------------------------------
// Definitions of
//--------------------------------------------------
#define _MAX_YPBPR_MODE             11

//----------------------------------------------------------------------------------------------------

#ifdef __YPBPR__

//--------------------------------------------------
// YPbPr Tables
//--------------------------------------------------
ModeTableType code tYPBPR_MODE_TABLE[_MAX_YPBPR_MODE] =
{
#if(_YPBPR_OVERSCAN_PERCENT==_OVERSCAN_PERCENT_97_00)
    	{   // Mode 0 : 720 x 576i x 50 Hz
        	0 | _SYNC_HN_VN | _SYNC_HP_VN | _SYNC_HN_VP | _SYNC_HP_VP,          // Polarity Flags,
        	704-6, 272+10-2,                                                    // InputWidth, InputHeight,
        	156, 500,                                                           // HFreq in kHz, VFreq in Hz,
        	_HFREQ_TOLERANCE, _VFREQ_TOLERANCE,                                 // HFreqTolerance in kHz, VFreqTolerance in Hz,
        	864, 312,                                                           // HTotal, VTotal,
        	143+6/2, 24+2/2,//31,                                               // HStartPos, VStartPos,
    	},
    	{   // Mode 1 : 720 x 480i x 60 Hz
        	0 | _SYNC_HN_VN | _SYNC_HP_VN | _SYNC_HN_VP | _SYNC_HP_VP,          // Polarity Flags,
        	704-20+14, 224+8+1,                                                 // InputWidth, InputHeight,
        	157, 600,                                                           // HFreq in kHz, VFreq in Hz,
        	_HFREQ_TOLERANCE, _VFREQ_TOLERANCE,                                 // HFreqTolerance in kHz, VFreqTolerance in Hz,
        	858, 262,                                                           // HTotal, VTotal,
        	129+20-14/2, 22-1,//27,                                             // HStartPos, VStartPos,
    	},
    	{   // Mode 2 : 720 x 576p x 50 Hz
        	0 | _SYNC_HN_VN | _SYNC_HP_VN | _SYNC_HN_VP | _SYNC_HP_VP,          // Polarity Flags,
        	704-14+8, 560-8+7,                                                  // InputWidth, InputHeight,
        	312, 500,                                                           // HFreq in kHz, VFreq in Hz,
        	_HFREQ_TOLERANCE, _VFREQ_TOLERANCE,                                 // HFreqTolerance in kHz, VFreqTolerance in Hz,
        	864, 624,                                                           // HTotal, VTotal,
        	141+10-8/2, 48+8-7/2,                                               // HStartPos, VStartPos,
    	},
    	{   // Mode 3 : 720 x 480p x 60 Hz
        	0 | _SYNC_HN_VN | _SYNC_HP_VN | _SYNC_HN_VP | _SYNC_HP_VP,          // Polarity Flags,
        	704-20+14, 464+1,                                                   // InputWidth, InputHeight,
        	315, 600,                                                           // HFreq in kHz, VFreq in Hz,
        	_HFREQ_TOLERANCE, _VFREQ_TOLERANCE,                                 // HFreqTolerance in kHz, VFreqTolerance in Hz,
        	858, 526,                                                           // HTotal, VTotal,
        	131+10-14/2, 45-1,                                                  // HStartPos, VStartPos,
    	},
    	{   // Mode 4 : 1280 x 720p x 60 Hz
        	0 | _SYNC_HN_VN | _SYNC_HP_VN | _SYNC_HN_VP | _SYNC_HP_VP,          // Polarity Flags,
        	1248-6, 704-6,                                                      // InputWidth, InputHeight,
        	450, 600,                                                           // HFreq in kHz, VFreq in Hz,
        	_HFREQ_TOLERANCE, _VFREQ_TOLERANCE,                                 // HFreqTolerance in kHz, VFreqTolerance in Hz,
        	1650, 750,                                                          // HTotal, VTotal,
        	311+6/2, 33+6/2,                                                    // HStartPos, VStartPos,
    	},
    	{   // Mode 5 : 1920 x 1080i x 50 Hz(274M)
        	0 | _SYNC_HN_VN | _SYNC_HP_VN | _SYNC_HN_VP | _SYNC_HP_VP,          // Polarity Flags,
        	1776+86, 516+8,//524,                                               // InputWidth, InputHeight,
        	281, 500,                                                           // HFreq in kHz, VFreq in Hz,
        	_HFREQ_TOLERANCE, _VFREQ_TOLERANCE,                                 // HFreqTolerance in kHz, VFreqTolerance in Hz,
        	2640, 554,//562,                                                    // HTotal, VTotal,
        	308-86/2, 33-8/2,                                                   // HStartPos, VStartPos,
    	},
    	{   // Mode 6 : 1920 x 1080i x 50 Hz(295M)
        	0 | _SYNC_HN_VN | _SYNC_HP_VN | _SYNC_HN_VP | _SYNC_HP_VP,          // Polarity Flags,
        	1776+86, 516+8,//524,                                               // InputWidth, InputHeight,
        	281, 500,                                                           // HFreq in kHz, VFreq in Hz,
        	_HFREQ_TOLERANCE, _VFREQ_TOLERANCE,                                 // HFreqTolerance in kHz, VFreqTolerance in Hz,
       		2240, 562,                                                          // HTotal, VTotal,
        	308-86/2, 33-8/2,                                                   // HStartPos, VStartPos,
    	},
    	{   // Mode 7 : 1920 x 1080i x 60 Hz
        	0 | _SYNC_HN_VN | _SYNC_HP_VN | _SYNC_HN_VP | _SYNC_HP_VP,          // Polarity Flags,
        	1776+86, 516+8,//524,                                               // InputWidth, InputHeight,
        	337, 600,                                                           // HFreq in kHz, VFreq in Hz,
        	_HFREQ_TOLERANCE, _VFREQ_TOLERANCE, 								// HFreqTolerance in kHz, VFreqTolerance in Hz,
        	2200, 562,                                                          // HTotal, VTotal,
        	308-86/2, 33-8/2,                                                   // HStartPos, VStartPos,
    	},
    	{   // Mode 8 : 1280 x 720p x 50 Hz
        	0 | _SYNC_HN_VN | _SYNC_HP_VN | _SYNC_HN_VP | _SYNC_HP_VP,          // Polarity Flags,
        	1248-6, 704-6,                                                      // InputWidth, InputHeight,
        	376, 502,                                                           // HFreq in kHz, VFreq in Hz,
        	_HFREQ_TOLERANCE, _VFREQ_TOLERANCE,         						// HFreqTolerance in kHz, VFreqTolerance in Hz,
        	1980, 750,                                                          // HTotal, VTotal,
        	300+6/2, 25+6/2,                                                    // HStartPos, VStartPos,
    	},
    	{   //# Mode 9 : 1920 x 1080p x 50 Hz
        	0 | _SYNC_HN_VN | _SYNC_HP_VN | _SYNC_HN_VP | _SYNC_HP_VP,          // Polarity Flags,
        	1920-58, 1080-32,                                                   // InputWidth, InputHeight,
        	563, 501,                                                           // HFreq in kHz, VFreq in Hz,
        	_HFREQ_TOLERANCE, _VFREQ_TOLERANCE,                                 // HFreqTolerance in kHz, VFreqTolerance in Hz,
        	2640, 1125,                                                         // HTotal, VTotal,
        	236+58/2, 41+32/2,                                                  // HStartPos, VStartPos,
    	},
    	{   //# Mode 10 : 1920 x 1080p x 60 Hz
        	0 | _SYNC_HN_VN | _SYNC_HP_VN | _SYNC_HN_VP | _SYNC_HP_VP,          // Polarity Flags,
        	1920-58, 1080-32,                                                   // InputWidth, InputHeight,
        	678, 603,                                                           // HFreq in kHz, VFreq in Hz,
        	_HFREQ_TOLERANCE, _VFREQ_TOLERANCE,                                 // HFreqTolerance in kHz, VFreqTolerance in Hz,
        	2200, 562,                                                          // HTotal, VTotal,
        	236+58/2,41+32/2,                                                   // HStartPos, VStartPos,
    	},
#elif(_YPBPR_OVERSCAN_PERCENT==_OVERSCAN_PERCENT_95_00)
    	{   // Mode 0 : 720 x 576i x 50 Hz
        	0 | _SYNC_HN_VN | _SYNC_HP_VN | _SYNC_HN_VP | _SYNC_HP_VP,          // Polarity Flags,
        	704-20, 272+10,                                                     // InputWidth, InputHeight,
        	156, 500,                                                           // HFreq in kHz, VFreq in Hz,
        	_HFREQ_TOLERANCE, _VFREQ_TOLERANCE,                                 // HFreqTolerance in kHz, VFreqTolerance in Hz,
        	864, 312,                                                           // HTotal, VTotal,
        	143+20/2, 24,//31,                                                  // HStartPos, VStartPos,
    	},
    	{   // Mode 1 : 720 x 480i x 60 Hz
        	0 | _SYNC_HN_VN | _SYNC_HP_VN | _SYNC_HN_VP | _SYNC_HP_VP,          // Polarity Flags,
        	704-20, 224+8-4,                                                    // InputWidth, InputHeight,
        	157, 600,                                                           // HFreq in kHz, VFreq in Hz,
        	_HFREQ_TOLERANCE, _VFREQ_TOLERANCE,                                 // HFreqTolerance in kHz, VFreqTolerance in Hz,
        	858, 262,                                                           // HTotal, VTotal,
        	129+20/2, 22+4/2,//27,                                              // HStartPos, VStartPos,
    	},
    	{   // Mode 2 : 720 x 576p x 50 Hz
        	0 | _SYNC_HN_VN | _SYNC_HP_VN | _SYNC_HN_VP | _SYNC_HP_VP,          // Polarity Flags,
        	704-14-6, 560-8-4,                                                  // InputWidth, InputHeight,
        	312, 500,                                                           // HFreq in kHz, VFreq in Hz,
        	_HFREQ_TOLERANCE, _VFREQ_TOLERANCE,                                 // HFreqTolerance in kHz, VFreqTolerance in Hz,
        	864, 624,                                                           // HTotal, VTotal,
        	141+10+6/2, 48+8+4/2,                                                       // HStartPos, VStartPos,
    	},
    	{   // Mode 3 : 720 x 480p x 60 Hz
        	0 | _SYNC_HN_VN | _SYNC_HP_VN | _SYNC_HN_VP | _SYNC_HP_VP,          // Polarity Flags,
        	704-20, 464-8,                                                      // InputWidth, InputHeight,
        	315, 600,                                                           // HFreq in kHz, VFreq in Hz,
        	_HFREQ_TOLERANCE, _VFREQ_TOLERANCE,                                 // HFreqTolerance in kHz, VFreqTolerance in Hz,
        	858, 526,                                                           // HTotal, VTotal,
        	131+10, 45+8/2,                                                     // HStartPos, VStartPos,
    	},
    	{   // Mode 4 : 1280 x 720p x 60 Hz
        	0 | _SYNC_HN_VN | _SYNC_HP_VN | _SYNC_HN_VP | _SYNC_HP_VP,          // Polarity Flags,
        	1248-32, 704-20,                                                    // InputWidth, InputHeight,
        	450, 600,                                                           // HFreq in kHz, VFreq in Hz,
        	_HFREQ_TOLERANCE, _VFREQ_TOLERANCE,                                 // HFreqTolerance in kHz, VFreqTolerance in Hz,
        	1650, 750,                                                          // HTotal, VTotal,
        	311+32/2, 33+20/2,                                                            // HStartPos, VStartPos,
    	},
    	{   // Mode 5 : 1920 x 1080i x 50 Hz(274M)
        	0 | _SYNC_HN_VN | _SYNC_HP_VN | _SYNC_HN_VP | _SYNC_HP_VP,          // Polarity Flags,
        	1776+48, 516-3,//524-11,                                                          // InputWidth, InputHeight,
        	281, 500,                                                           // HFreq in kHz, VFreq in Hz,
        	_HFREQ_TOLERANCE, _VFREQ_TOLERANCE,                                 // HFreqTolerance in kHz, VFreqTolerance in Hz,
       		2640, 562,                                                          // HTotal, VTotal,
        	308-48/2, 33+3/2,                                                            // HStartPos, VStartPos,
    	},
    	{   // Mode 6 : 1920 x 1080i x 50 Hz(295M)
        	0 | _SYNC_HN_VN | _SYNC_HP_VN | _SYNC_HN_VP | _SYNC_HP_VP,          // Polarity Flags,
        	1776+48, 516-3,//524-11,                                                          // InputWidth, InputHeight,
        	281, 500,                                                           // HFreq in kHz, VFreq in Hz,
        	_HFREQ_TOLERANCE, _VFREQ_TOLERANCE,                                 // HFreqTolerance in kHz, VFreqTolerance in Hz,
       		2240, 562,                                                          // HTotal, VTotal,
        	308-48/2, 33+3/2,                                                            // HStartPos, VStartPos,
    	},
    	{   // Mode 7 : 1920 x 1080i x 60 Hz
        	0 | _SYNC_HN_VN | _SYNC_HP_VN | _SYNC_HN_VP | _SYNC_HP_VP,          // Polarity Flags,
        	1776+48, 524-11,                                                          // InputWidth, InputHeight,
        	337, 600,                                                           // HFreq in kHz, VFreq in Hz,
        	_HFREQ_TOLERANCE, _VFREQ_TOLERANCE, 		// HFreqTolerance in kHz, VFreqTolerance in Hz,
        	2200, 562,                                                          // HTotal, VTotal,
        	308-48/2, 33+11/2,                                                          	// HStartPos, VStartPos,
    	},
    	{   // Mode 8 : 1280 x 720p x 50 Hz
        	0 | _SYNC_HN_VN | _SYNC_HP_VN | _SYNC_HN_VP | _SYNC_HP_VP,          // Polarity Flags,
        	1248-32, 704-20,                                                    // InputWidth, InputHeight,
        	376, 502,                                                           // HFreq in kHz, VFreq in Hz,
        	_HFREQ_TOLERANCE, _VFREQ_TOLERANCE,         						// HFreqTolerance in kHz, VFreqTolerance in Hz,
        	1980, 750,                                                          // HTotal, VTotal,
        	300+32/2, 25+20/2,                                                            // HStartPos, VStartPos,
    	},
    	{   //# Mode 9 : 1920 x 1080p x 50 Hz
        	0 | _SYNC_HN_VN | _SYNC_HP_VN | _SYNC_HN_VP | _SYNC_HP_VP,          // Polarity Flags,
        	1920-96, 1080-54,                                                   // InputWidth, InputHeight,
        	563, 501,                                                           // HFreq in kHz, VFreq in Hz,
        	_HFREQ_TOLERANCE, _VFREQ_TOLERANCE,                                 // HFreqTolerance in kHz, VFreqTolerance in Hz,
        	2640, 1125,                                                         // HTotal, VTotal,
        	236+96/2, 41+54/2,                                                      		// HStartPos, VStartPos,
   		},
    	{   //# Mode 10 : 1920 x 1080p x 60 Hz
        	0 | _SYNC_HN_VN | _SYNC_HP_VN | _SYNC_HN_VP | _SYNC_HP_VP,          // Polarity Flags,
        	//1920-96, 1080-54,                                                 // InputWidth, InputHeight,
        	1920-120, 1080-68,                                                  // InputWidth, InputHeight,
        	678, 603,                                                           // HFreq in kHz, VFreq in Hz,
        	_HFREQ_TOLERANCE, _VFREQ_TOLERANCE,                                 // HFreqTolerance in kHz, VFreqTolerance in Hz,
        	2200, 562,                                                          // HTotal, VTotal,
        	//236+96/2,41+54/2,                                                       		// HStartPos, VStartPos,
        	236+120/2,41+68/2,                                                       		// HStartPos, VStartPos,
    	},
#elif(_YPBPR_OVERSCAN_PERCENT==_OVERSCAN_PERCENT_93_75)
    	{   // Mode 0 : 720 x 576i x 50 Hz
        	0 | _SYNC_HN_VN | _SYNC_HP_VN | _SYNC_HN_VP | _SYNC_HP_VP,          // Polarity Flags,
        	704-28, 272-2,                                                      // InputWidth, InputHeight,
        	156, 500,                                                           // HFreq in kHz, VFreq in Hz,
        	_HFREQ_TOLERANCE, _VFREQ_TOLERANCE,                                 // HFreqTolerance in kHz, VFreqTolerance in Hz,
        	864, 312,                                                           // HTotal, VTotal,
        	140+28/2, 28-2/2,//31,                                              // HStartPos, VStartPos,
    	},
    	{   // Mode 1 : 720 x 480i x 60 Hz
        	0 | _SYNC_HN_VN | _SYNC_HP_VN | _SYNC_HN_VP | _SYNC_HP_VP,          // Polarity Flags,
        	704-28, 224,//224+1,                                                    	// InputWidth, InputHeight,
        	157, 600,                                                           // HFreq in kHz, VFreq in Hz,
        	_HFREQ_TOLERANCE, _VFREQ_TOLERANCE,                                 // HFreqTolerance in kHz, VFreqTolerance in Hz,
        	858, 262,                                                           // HTotal, VTotal,
        	129+28/2, 21+1,//27,                                              	// HStartPos, VStartPos,
    	},
    	{   // Mode 2 : 720 x 576p x 50 Hz
        	0 | _SYNC_HN_VN | _SYNC_HP_VN | _SYNC_HN_VP | _SYNC_HP_VP,          // Polarity Flags,
        	704-28, 560-20,                                                     // InputWidth, InputHeight,
        	312, 500,                                                           // HFreq in kHz, VFreq in Hz,
        	_HFREQ_TOLERANCE, _VFREQ_TOLERANCE,                                 // HFreqTolerance in kHz, VFreqTolerance in Hz,
        	864, 624,                                                           // HTotal, VTotal,
        	140+28/2, 49+20/2,                                                       // HStartPos, VStartPos,
    	},
    	{   // Mode 3 : 720 x 480p x 60 Hz

        	0 | _SYNC_HN_VN | _SYNC_HP_VN | _SYNC_HN_VP | _SYNC_HP_VP,          // Polarity Flags,
        	704-28, 464-14,                                                     // InputWidth, InputHeight,
        	315, 600,                                                           // HFreq in kHz, VFreq in Hz,
        	_HFREQ_TOLERANCE, _VFREQ_TOLERANCE,                                 // HFreqTolerance in kHz, VFreqTolerance in Hz,
        	858, 526,                                                           // HTotal, VTotal,
        	131+28/2, 44+14/2,                                                  // HStartPos, VStartPos,
    	},

    	{   // Mode 4 : 1280 x 720p x 60 Hz
        	0 | _SYNC_HN_VN | _SYNC_HP_VN | _SYNC_HN_VP | _SYNC_HP_VP,          // Polarity Flags,
        	1248-48, 704-28,                                                    // InputWidth, InputHeight,
        	450, 600,                                                           // HFreq in kHz, VFreq in Hz,
        	_HFREQ_TOLERANCE, _VFREQ_TOLERANCE,                                 // HFreqTolerance in kHz, VFreqTolerance in Hz,
        	1650, 750,                                                          // HTotal, VTotal,
        	315+48/2, 31+28/2,                                                            // HStartPos, VStartPos,
    	},
    	{   // Mode 5 : 1920 x 1080i x 50 Hz(274M)
        	0 | _SYNC_HN_VN | _SYNC_HP_VN | _SYNC_HN_VP | _SYNC_HP_VP,          // Polarity Flags,
        	1776+24, 516-10,//524-11,                                           // InputWidth, InputHeight,
        	281, 500,                                                           // HFreq in kHz, VFreq in Hz,
        	_HFREQ_TOLERANCE, _VFREQ_TOLERANCE,                                 // HFreqTolerance in kHz, VFreqTolerance in Hz,
       		2640, 562,                                                          // HTotal, VTotal,
        	308-24/2, 33+6/2,                                                            // HStartPos, VStartPos,
    	},
    	{   // Mode 6 : 1920 x 1080i x 50 Hz(295M)
        	0 | _SYNC_HN_VN | _SYNC_HP_VN | _SYNC_HN_VP | _SYNC_HP_VP,          // Polarity Flags,
        	1776+24, 516-10,//524-11,                                           // InputWidth, InputHeight,
        	281, 500,                                                           // HFreq in kHz, VFreq in Hz,
        	_HFREQ_TOLERANCE, _VFREQ_TOLERANCE,                                 // HFreqTolerance in kHz, VFreqTolerance in Hz,
       		2240, 562,                                                          // HTotal, VTotal,
        	308-24/2, 33+6/2,                                                            // HStartPos, VStartPos,
    	},
    	{   // Mode 7 : 1920 x 1080i x 60 Hz
        	0 | _SYNC_HN_VN | _SYNC_HP_VN | _SYNC_HN_VP | _SYNC_HP_VP,          // Polarity Flags,
        	1776+24, 524-18,                                                    // InputWidth, InputHeight,
        	337, 600,                                                           // HFreq in kHz, VFreq in Hz,
        	_HFREQ_TOLERANCE, _VFREQ_TOLERANCE, 								// HFreqTolerance in kHz, VFreqTolerance in Hz,
        	2200, 562,                                                          // HTotal, VTotal,
        	308-24/2, 26+18/2,                                                          	// HStartPos, VStartPos,
    	},
    	{   // Mode 8 : 1280 x 720p x 50 Hz
        	0 | _SYNC_HN_VN | _SYNC_HP_VN | _SYNC_HN_VP | _SYNC_HP_VP,          // Polarity Flags,
        	1248-48, 704-28,                                                    // InputWidth, InputHeight,
        	376, 502,                                                           // HFreq in kHz, VFreq in Hz,
        	_HFREQ_TOLERANCE, _VFREQ_TOLERANCE,         						// HFreqTolerance in kHz, VFreqTolerance in Hz,
        	1980, 750,                                                          // HTotal, VTotal,
        	316+48/2, 28+28/2,                                                            // HStartPos, VStartPos,
    	},
    	{   //# Mode 9 : 1920 x 1080p x 50 Hz
        	0 | _SYNC_HN_VN | _SYNC_HP_VN | _SYNC_HN_VP | _SYNC_HP_VP,          // Polarity Flags,
        	1920-120, 1080-68,                                                  // InputWidth, InputHeight,
        	563, 501,                                                           // HFreq in kHz, VFreq in Hz,
        	_HFREQ_TOLERANCE, _VFREQ_TOLERANCE,                                 // HFreqTolerance in kHz, VFreqTolerance in Hz,
        	2640, 1125,                                                         // HTotal, VTotal,
        	236+120/2, 41+68/2,                                                      		// HStartPos, VStartPos,
   		},
    	{   //# Mode 10 : 1920 x 1080p x 60 Hz
        	0 | _SYNC_HN_VN | _SYNC_HP_VN | _SYNC_HN_VP | _SYNC_HP_VP,          // Polarity Flags,
        	1920-120, 1080-68,                                                  // InputWidth, InputHeight,
        	678, 603,                                                           // HFreq in kHz, VFreq in Hz,
        	_HFREQ_TOLERANCE, _VFREQ_TOLERANCE,                                 // HFreqTolerance in kHz, VFreqTolerance in Hz,
        	2200, 562,                                                          // HTotal, VTotal,
        	236+120/2,41+68/2,                                                       		// HStartPos, VStartPos,
    	},
#else
    	{   // Mode 0 : 720 x 576i x 50 Hz
        	0 | _SYNC_HN_VN | _SYNC_HP_VN | _SYNC_HN_VP | _SYNC_HP_VP,          // Polarity Flags,
        	704-20, 272+10,                                                     // InputWidth, InputHeight,
        	156, 500,                                                           // HFreq in kHz, VFreq in Hz,
        	_HFREQ_TOLERANCE, _VFREQ_TOLERANCE,                                 // HFreqTolerance in kHz, VFreqTolerance in Hz,
        	864, 312,                                                           // HTotal, VTotal,
        	143+20, 24,//31,                                                    // HStartPos, VStartPos,
    	},
    	{   // Mode 1 : 720 x 480i x 60 Hz
        	0 | _SYNC_HN_VN | _SYNC_HP_VN | _SYNC_HN_VP | _SYNC_HP_VP,          // Polarity Flags,
        	704-20, 224+8,                                                      // InputWidth, InputHeight,
        	157, 600,                                                           // HFreq in kHz, VFreq in Hz,
        	_HFREQ_TOLERANCE, _VFREQ_TOLERANCE,                                 // HFreqTolerance in kHz, VFreqTolerance in Hz,
        	858, 262,                                                           // HTotal, VTotal,
        	129+20, 22,//27,                                                    // HStartPos, VStartPos,
   	 	},
    	{   // Mode 2 : 720 x 576p x 50 Hz
        	0 | _SYNC_HN_VN | _SYNC_HP_VN | _SYNC_HN_VP | _SYNC_HP_VP,          // Polarity Flags,
        	704-14, 560-8,                                                      // InputWidth, InputHeight,
        	312, 500,                                                           // HFreq in kHz, VFreq in Hz,
        	_HFREQ_TOLERANCE, _VFREQ_TOLERANCE,                                 // HFreqTolerance in kHz, VFreqTolerance in Hz,
        	864, 624,                                                           // HTotal, VTotal,
        	141+10, 48+8,                                                       // HStartPos, VStartPos,
    	},
    	{   // Mode 3 : 720 x 480p x 60 Hz
        	0 | _SYNC_HN_VN | _SYNC_HP_VN | _SYNC_HN_VP | _SYNC_HP_VP,          // Polarity Flags,
        	704-20, 464,                                                        // InputWidth, InputHeight,
        	315, 600,                                                           // HFreq in kHz, VFreq in Hz,
        	_HFREQ_TOLERANCE, _VFREQ_TOLERANCE,                                 // HFreqTolerance in kHz, VFreqTolerance in Hz,
        	858, 526,                                                           // HTotal, VTotal,
        	131+10, 45,                                                         // HStartPos, VStartPos,
    	},
    	{   // Mode 4 : 1280 x 720p x 60 Hz
        	0 | _SYNC_HN_VN | _SYNC_HP_VN | _SYNC_HN_VP | _SYNC_HP_VP,          // Polarity Flags,
        	1248-20, 704,                                                       // InputWidth, InputHeight,
        	450, 600,                                                           // HFreq in kHz, VFreq in Hz,
        	_HFREQ_TOLERANCE, _VFREQ_TOLERANCE,                                 // HFreqTolerance in kHz, VFreqTolerance in Hz,
        	1650, 750,                                                          // HTotal, VTotal,
        	311+10, 33,                                                            // HStartPos, VStartPos,
    	},
    	{   // Mode 5 : 1920 x 1080i x 50 Hz(274M)
        	0 | _SYNC_HN_VN | _SYNC_HP_VN | _SYNC_HN_VP | _SYNC_HP_VP,          // Polarity Flags,
        	1776, 524,                                                          // InputWidth, InputHeight,
        	281, 500,                                                           // HFreq in kHz, VFreq in Hz,
        	_HFREQ_TOLERANCE, _VFREQ_TOLERANCE,                                 // HFreqTolerance in kHz, VFreqTolerance in Hz,
        	2640, 562,                                                          // HTotal, VTotal,
        	308, 33,                                                            // HStartPos, VStartPos,
    	},
    	{   // Mode 6 : 1920 x 1080i x 50 Hz(295M)
        	0 | _SYNC_HN_VN | _SYNC_HP_VN | _SYNC_HN_VP | _SYNC_HP_VP,          // Polarity Flags,
        	1776, 524,                                                          // InputWidth, InputHeight,
        	281, 500,                                                           // HFreq in kHz, VFreq in Hz,
        	_HFREQ_TOLERANCE, _VFREQ_TOLERANCE,                                 // HFreqTolerance in kHz, VFreqTolerance in Hz,
       		2240, 562,                                                          // HTotal, VTotal,
        	308, 33,                                                            // HStartPos, VStartPos,
    	},
    	{   // Mode 7 : 1920 x 1080i x 60 Hz
        	0 | _SYNC_HN_VN | _SYNC_HP_VN | _SYNC_HN_VP | _SYNC_HP_VP,          // Polarity Flags,
        	1776, 524,                                                          // InputWidth, InputHeight,
        	337, 600,                                                           // HFreq in kHz, VFreq in Hz,
        	_HFREQ_TOLERANCE, _VFREQ_TOLERANCE, 								// HFreqTolerance in kHz, VFreqTolerance in Hz,
        	2200, 562,                                                          // HTotal, VTotal,
        	308, 33,                                                          	// HStartPos, VStartPos,
    	},
    	{   // Mode 8 : 1280 x 720p x 50 Hz
        	0 | _SYNC_HN_VN | _SYNC_HP_VN | _SYNC_HN_VP | _SYNC_HP_VP,          // Polarity Flags,
        	1248, 704,                                                          // InputWidth, InputHeight,
        	376, 502,                                                           // HFreq in kHz, VFreq in Hz,
        	_HFREQ_TOLERANCE, _VFREQ_TOLERANCE,         						// HFreqTolerance in kHz, VFreqTolerance in Hz,
        	1980, 750,                                                          // HTotal, VTotal,
        	300, 25,                                                            // HStartPos, VStartPos,
    	},
    	{   //# Mode 9 : 1920 x 1080p x 50 Hz
        	0 | _SYNC_HN_VN | _SYNC_HP_VN | _SYNC_HN_VP | _SYNC_HP_VP,          // Polarity Flags,
        	1920, 1080,                                                    		// InputWidth, InputHeight,
        	563, 501,                                                           // HFreq in kHz, VFreq in Hz,
        	_HFREQ_TOLERANCE, _VFREQ_TOLERANCE,                                 // HFreqTolerance in kHz, VFreqTolerance in Hz,
        	2640, 1125,                                                         // HTotal, VTotal,
        	236, 41,                                                      		// HStartPos, VStartPos,
    	},
    	{   //# Mode 10 : 1920 x 1080p x 60 Hz
        	0 | _SYNC_HN_VN | _SYNC_HP_VN | _SYNC_HN_VP | _SYNC_HP_VP,          // Polarity Flags,
        	1920, 1080,                                                    		// InputWidth, InputHeight,
        	678, 603,                                                           // HFreq in kHz, VFreq in Hz,
        	_HFREQ_TOLERANCE, _VFREQ_TOLERANCE,                                 // HFreqTolerance in kHz, VFreqTolerance in Hz,
        	2200, 562,                                                          // HTotal, VTotal,
        	236,41,                                                       		// HStartPos, VStartPos,
   	 	},
#endif
};

BYTE code tYPBPR_TABLE_SET_SCALER[] =
{

//    4,  _NON_AUTOINC,   _SYNC_PROC_ACCESS_PORT_5C,      _SYNC_G_CLAMP_START_00,
  //  7,  _NON_AUTOINC,   _SYNC_PROC_DATA_PORT_5D,        0x10,0x18,0x10,0x18,

    
    4,  _NON_AUTOINC,   _SYNC_PROC_ACCESS_PORT_5C,      _SYNC_CAPTURE_WINDOW_SET_07,
  #if (_YPBPR_NONE_CHECK_APLL)	 
    5,  _NON_AUTOINC,   _SYNC_PROC_DATA_PORT_5D,        0x21,0x14,	
  #else
    5,  _NON_AUTOINC,   _SYNC_PROC_DATA_PORT_5D,        0x21,0x04, 
  #endif

    4,  _NON_AUTOINC,   _CB_ACCESS_PORT_64,             0x80,
    9,  _NON_AUTOINC,   _CB_DATA_PORT_65,               0x7e,0x7e,0x7e,0x80,0x80,0x80,
    4,  _NON_AUTOINC,   _CB_ACCESS_PORT_64,             0x00,

    4,  _NON_AUTOINC,   _YUV2RGB_CTRL_9C,               0x08,
    21, _NON_AUTOINC,   _YUV_RGB_COEF_DATA_9D,          0x04,0x00,0x00,0x00,0x06,0x60,
                                                        0x04,0x00,0xfe,0x70,0xfc,0xc0,
                                                        0x04,0x00,0x08,0x10,0x00,0x00,

    4,  _NON_AUTOINC,   _YUV2RGB_CTRL_9C,               0x07,

    4,  _NON_AUTOINC,   _PAGE_SELECT_9F,                _PAGE0,
    9,  _AUTOINC,       _P0_RED_GAIN_C0,                0x80,0x80,0x80,0x80,0x80,0x80,


    _END
};

//--------------------------------------------------
// Global Variables
//--------------------------------------------------


//--------------------------------------------------
// Function Prototypes
//--------------------------------------------------
BYTE CYPbPrSearchMode(void);
bit CYPbPrCompareMode(BYTE ucModeCnt);
void CYPbPrGetModeInfo(void);
void CYPbPrStartUp(void);
bit CYPbPrSetupMode(void);
void YPbPrADCDefault(void);
#if(_YPBPR_HW_AUTO_SOY == _ENABLE)
void CYPbPrHWAutoSOY(void);
#endif




#else

//--------------------------------------------------
// Extern Global Variables
//--------------------------------------------------

//--------------------------------------------------
// Extern Function Prototypes
//--------------------------------------------------
extern BYTE CYPbPrSearchMode(void);
extern bit CYPbPrSetupMode(void);
extern void CYPbPrHWAutoSOY(void);


#endif		//#ifdef __YPBPR__

#endif 		//#if(_YPBPR_SUPPORT == _ON)


extern BYTE code g_tYpbprTemp;

