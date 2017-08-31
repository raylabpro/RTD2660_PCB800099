#include "Core\Header\Include.h"

BYTE code t7313Test[] = " ";


#if(AUDIO_TYPE == _AUDIO_SC7313)

BYTE code ucSc7313VolTable[] =
{
		//OSD			dB		STEP(dB)	备注
	0,	//VOL-MAX		0					音量最大。
	1,	//VOL-30		-1		1	
	2,	//VOL-29		-2		1	
	3,	//VOL-28		-3		1	
	4,	//VOL-27		-4		1	
	5,	//VOL-26		-5		1	
	6,	//VOL-25		-6		1	
	7,	//VOL-24		-7		1	
	8,	//VOL-23		-8		1	
	9,	//VOL-22		-9		1	
	10,	//VOL-21		-10		1	
	11,	//VOL-20		-11		1	
	12,	//VOL-19		-12		1	
	13,	//VOL-18		-13		1	
	14,	//VOL-17		-14		1	
	15,	//VOL-16		-15		1	
	16,	//VOL-15		-16		1	
	17,	//VOL-14		-18		2		
	18,	//VOL-13		-20		2			每次开机时将VOL设置在这个位置。
	19,	//VOL-12		-23		3	
	20,	//VOL-11		-26		3	
	21,	//VOL-10		-29		3	
	22,	//VOL-9			-32		3	
	23,	//VOL-8			-35		3	
	24,	//VOL-7			-38		3	
	25,	//VOL-6			-42		4	
	26,	//VOL-5			-46		4	
	27,	//VOL-4			-50		4	
	28,	//VOL-3			-54		4	
	30,	//VOL-2			-57		3	
	35,	//VOL-1			-60		3	
	42,
	52,
	63,	//VOL-MIN		-63		3			音量最小时静音。
	
	0
};
//---------------------------------------------

void CSc7313MuteOn(void)
{
    CI2cStart(0x88);  // SC7313 address
    CI2cSendByte(0x00 | 0x3f);
    CI2cSendByte(0xC0 | 0x1F);  // Balance mute
    CI2cSendByte(0xE0 | 0x1F);  // Balance mute
    CI2cStop();
}
//---------------------------------------------

void CSetSc7313Volume(BYTE ucVolume)
{
     WORD iVolume;

     iVolume = 33 - ((WORD)33 * ucVolume / 100);
    
     CI2cStart(0x88);    // SC7313 address
     CI2cSendByte(ucSc7313VolTable[iVolume]);
     CI2cStop();
}
//---------------------------------------------

void CSelect7313SoundChannel(BYTE ucChannel)
{
     CI2cStart(0x88);    // SC7313 address
     CI2cSendByte(0x00 | 0x3f);
     CI2cSendByte(0x80 | 0x00); // 前置左声道衰减
     CI2cSendByte(0xA0 | 0x00); // 前置右声道衰减
     CI2cSendByte(0xE0 | 0x00); // 后置左声道衰减
     CI2cSendByte(0xC0 | 0x00); // 后置右声道衰减
     CI2cSendByte(0x50 | 0x07);
     CI2cSendByte(0x70 | 0x07);
  //   CI2cSendByte((0x40 | 0x1c) | ucChannel); // Set 0dB
     CI2cSendByte((0x40 | 0x04) | ucChannel);  // Set +11.25dB
     CI2cStop();
}

//---------------------------------------------
BYTE code tBassTreble[17] =
{
   0x00,
   0x01,
   0x02,
   0x03,
   0x04,
   0x05,
   0x06,
   0x07,
   0x0F,
   0x0E,
   0x0D,
   0x0C,
   0x0B,
   0x0A,
   0x09,
   0x08,
   0x08,
};

BYTE code BalanceTable[] = 
{
	0x00,0x01,0x02,0x03,0x04,0x05,0x06,0x07,
	0x08,0x09,0x0A,0x0B,0x0C,0x0D,0x0E,0x0F,
	0x10,0x11,0x12,0x13,0x14,0x15,0x16,0x17,
	0x18,0x19,0x1A,0x1B,0x1C,0x1D,0x1E,0x1F,
};

void CSetAudioProcessor(BYTE ucBalance, BYTE ucBass, BYTE ucTreble) small
{
    BYTE BalanceTemp = (WORD)(ucBalance*64)/100;
    BYTE BalanceCurr = 0;

    CI2cStart(0x88);                 // SC7313 address
    CI2cSendByte(0x60 | tBassTreble[ucBass/6]);     // Bass
    CI2cSendByte(0x70 | tBassTreble[ucTreble/6]);   // Treble

    // Balance
    if (BalanceTemp > 32)
    {
        BalanceCurr = 0xC0 | (BalanceTemp - 32 - 1);
		CI2cSendByte(BalanceCurr);
        BalanceCurr = 0x80 | (BalanceTemp - 32 - 1);
		CI2cSendByte(BalanceCurr);
    }
    else if(BalanceTemp == 32)
    {
        BalanceCurr = 0xC0;
		CI2cSendByte(BalanceCurr);
        BalanceCurr = 0x80;
		CI2cSendByte(BalanceCurr);

        BalanceCurr = 0xE0;
		CI2cSendByte(BalanceCurr);
        BalanceCurr = 0xA0;
		CI2cSendByte(BalanceCurr);
    }
    else
    {
        BalanceCurr = 0xA0 | (32 - BalanceTemp - 1);
		CI2cSendByte(BalanceCurr);
        BalanceCurr = 0xE0 | (32 - BalanceTemp - 1);
		CI2cSendByte(BalanceCurr);
    }
    CI2cStop();
}


#endif 

