#ifndef PA_LEGACY_IPC_INCLUDE
#define PA_LEGACY_IPCINCLUDE

#include <nds.h>

#ifdef __cplusplus
extern "C" {
#endif

//Thank you Xennon++.

#if defined(ARM9)
#define CONST const
#elif defined(ARM7)
#define CONST
#else
#error only for NDS
#endif

enum IPCZCommand{
	ResetRudolph		= 0x01,
	ResetBootlib		= 0x02,
	ResetMoonlight	= 0x03,
	ResetRudolphM		= 0x04,
	ResetMoonShell2		= 0x05,

	Shutdown		= 0x11,
	ReturnBootstub	= 0x12,

	//Slot2NDS		= 0x18, //Use bootMoonlight(0x080000c0)
	Slot2GBA		= 0x19,
	//ReturnDSMenu	= 0x1a, //GetFirmware then decompress it to get image
	ReturnDSiMenu		= 0x1b,

	GetARM7Bios		= 0x101,
	GetFirmware		= 0x102,
	WriteFirmware		= 0x103,
	RequestBatteryLevel	= 0x111,
	UnbrickGWInstaller	= 0x1101,

	EnableDSTTSDHCFlag	= 0x201,
	DisableDSTTSDHCFlag	= 0x202,

	PlaySound            = 0x301,
	StopSound            = 0x302,

	//CPTest		= 0xf1000000,
};

enum NDSType{
	NDSPhat	=0,
	NDSLite	=1,
	NDSi		=2,	//eXtra Large hardware is completely the same.
	ThreeDS	=0x10, //reserved?
};

typedef struct{
	u32 cmd;
	u32 bootaddress; //Used with ResetMoonlight
	u32 blanks;

	CONST u16 keysheld;
	CONST u16 keysdown;
	CONST u16 keysup;
	CONST u16 keysrepeat;
	CONST u16 touchX;
	CONST u16 touchY;

	CONST u8  battery;
	CONST u8  DUMMY;
	CONST u8  NDSType;
	CONST u8  flashmeversion;
	CONST u8  MAC[6];
	CONST u16 fwchksum;
	CONST u32 temperature; // use with /0x1000
	CONST u32 fwsize;

	//u32 argc;
	//u32 args[8];

	u8  *arm7bios_addr;
	u32 arm7bios_bufsize;
	u8  *firmware_addr;
	u32 firmware_bufsize;
	u8  *firmware_write_addr;
	u32 firmware_write_index; //must be 0,1,2,4,5 //should be u8?

	void *PCM_L;
	void *PCM_R;
	u32  PCM_freq;
	u32  PCM_size;
	u32  PCM_bits; //8bit or 16bit

	//u8 resetARM9ready;
	//u8 resetARM7ready;
} TransferRegionZ;

//I hope IPC won't be overridden by FIFO...
//They say after 0x02fFF800 is used for NDS settings, so I use 0x02fFF700.

#ifdef ARM9
extern TransferRegionZ volatile *IPCZ;
#define IPCZ_DSiMode ((TransferRegionZ volatile *)(0x0cfFF700))
#define IPCZ_DSMode ((TransferRegionZ volatile *)(0x02fFF700))
#elif ARM7
#define IPCZ ((TransferRegionZ volatile *)(0x02fFF700))
#endif

#ifdef __cplusplus
}
#endif
#endif //included