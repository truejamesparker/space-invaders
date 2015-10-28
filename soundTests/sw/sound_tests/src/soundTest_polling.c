#include <stdio.h>
#include "platform.h"

#include "xparameters.h"

#include "soundDriver/xac97_l.h"

#include <xbasic_types.h>
#include <xio.h>
#include <xenv.h>

extern int tankFireSoundRate;
extern int tankFireSoundFrames;
extern int tankFireSound[];

void print(char *str);

int main() {
    init_platform();

    print("Hello World\n\r");

    // apparently we don't need to init it, just HardReset
    XAC97_HardReset(XPAR_AXI_AC97_0_BASEADDR);

    XAC97_WriteReg(XPAR_AXI_AC97_0_BASEADDR, AC97_ExtendedAudioStat, 1);
    XAC97_WriteReg(XPAR_AXI_AC97_0_BASEADDR, AC97_PCM_DAC_Rate, AC97_PCM_RATE_11025_HZ);

    while (1) {
    	XAC97_PlayAudio(XPAR_AXI_AC97_0_BASEADDR, tankFireSound, &tankFireSound[tankFireSoundFrames]);

    	XAC97_Delay(1000000);
    }

    cleanup_platform();

    return 0;
}
