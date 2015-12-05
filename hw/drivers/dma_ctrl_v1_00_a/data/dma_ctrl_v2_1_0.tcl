##############################################################################
## Filename:          C:\parkerbros\space-invaders\hw/drivers/dma_ctrl_v1_00_a/data/dma_ctrl_v2_1_0.tcl
## Description:       Microprocess Driver Command (tcl)
## Date:              Sat Dec 05 14:12:37 2015 (by Create and Import Peripheral Wizard)
##############################################################################

#uses "xillib.tcl"

proc generate {drv_handle} {
  xdefine_include_file $drv_handle "xparameters.h" "dma_ctrl" "NUM_INSTANCES" "DEVICE_ID" "C_BASEADDR" "C_HIGHADDR" 
}
