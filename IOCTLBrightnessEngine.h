//---------------------------------------------------------------------------

#ifndef IOCTLBrightnessEngineH
#define IOCTLBrightnessEngineH

typedef struct _DISPLAY_BRIGHTNESS {
   UCHAR ucDisplayPolicy;
   UCHAR ucACBrightness;
   UCHAR ucDCBrightness;
} DISPLAY_BRIGHTNESS, *PDISPLAY_BRIGHTNESS;

#define CTL_CODE( DeviceType, Function, Method, Access ) (                 \
    ((DeviceType) << 16) | ((Access) << 14) | ((Function) << 2) | (Method) \
)

#define FILE_DEVICE_VIDEO	0x0000002
#define METHOD_BUFFERED     0
#define FILE_ANY_ACCESS		0

#define IOCTL_VIDEO_QUERY_DISPLAY_BRIGHTNESS \
  CTL_CODE(FILE_DEVICE_VIDEO, 0x126, METHOD_BUFFERED, FILE_ANY_ACCESS)

#define IOCTL_VIDEO_SET_DISPLAY_BRIGHTNESS \
  CTL_CODE(FILE_DEVICE_VIDEO, 0x127, METHOD_BUFFERED, FILE_ANY_ACCESS)

#define DISPLAYPOLICY_BOTH	0x00000003

class TIOCTLBrightnessEngine
{
public:
	TIOCTLBrightnessEngine();
	~TIOCTLBrightnessEngine();

	bool DecreaseBrightness();
	void RestoreBrightness();

private:
	HANDLE m_hLCDDevice;
	DISPLAY_BRIGHTNESS m_OldDisplayBrightness;

};

//---------------------------------------------------------------------------
#endif
