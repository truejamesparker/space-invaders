#  Simulation Model Generator
#  Xilinx EDK 13.4 EDK_O.87xd
#  Copyright (c) 1995-2011 Xilinx, Inc.  All rights reserved.
#
#  File     dma_ctrl_0_wave.tcl (Mon Dec 07 13:21:43 2015)
#
#  Module   dma_ctrl_0_wrapper
#  Instance dma_ctrl_0
if { [info exists PathSeparator] } { set ps $PathSeparator } else { set ps "/" }
if { ![info exists tbpath] } { set tbpath "${ps}system_tb${ps}dut" }

# wave add $tbpath${ps}dma_ctrl_0${ps}S_AXI_ACLK -into $id
# wave add $tbpath${ps}dma_ctrl_0${ps}S_AXI_ARESETN -into $id
# wave add $tbpath${ps}dma_ctrl_0${ps}S_AXI_AWADDR -into $id
# wave add $tbpath${ps}dma_ctrl_0${ps}S_AXI_AWVALID -into $id
# wave add $tbpath${ps}dma_ctrl_0${ps}S_AXI_WDATA -into $id
# wave add $tbpath${ps}dma_ctrl_0${ps}S_AXI_WSTRB -into $id
# wave add $tbpath${ps}dma_ctrl_0${ps}S_AXI_WVALID -into $id
# wave add $tbpath${ps}dma_ctrl_0${ps}S_AXI_BREADY -into $id
# wave add $tbpath${ps}dma_ctrl_0${ps}S_AXI_ARADDR -into $id
# wave add $tbpath${ps}dma_ctrl_0${ps}S_AXI_ARVALID -into $id
# wave add $tbpath${ps}dma_ctrl_0${ps}S_AXI_RREADY -into $id
  wave add $tbpath${ps}dma_ctrl_0${ps}S_AXI_ARREADY -into $id
  wave add $tbpath${ps}dma_ctrl_0${ps}S_AXI_RDATA -into $id
  wave add $tbpath${ps}dma_ctrl_0${ps}S_AXI_RRESP -into $id
  wave add $tbpath${ps}dma_ctrl_0${ps}S_AXI_RVALID -into $id
  wave add $tbpath${ps}dma_ctrl_0${ps}S_AXI_WREADY -into $id
  wave add $tbpath${ps}dma_ctrl_0${ps}S_AXI_BRESP -into $id
  wave add $tbpath${ps}dma_ctrl_0${ps}S_AXI_BVALID -into $id
  wave add $tbpath${ps}dma_ctrl_0${ps}S_AXI_AWREADY -into $id
# wave add $tbpath${ps}dma_ctrl_0${ps}m_axi_lite_aclk -into $id
# wave add $tbpath${ps}dma_ctrl_0${ps}m_axi_lite_aresetn -into $id
# wave add $tbpath${ps}dma_ctrl_0${ps}md_error -into $id
# wave add $tbpath${ps}dma_ctrl_0${ps}m_axi_lite_arready -into $id
  wave add $tbpath${ps}dma_ctrl_0${ps}m_axi_lite_arvalid -into $id
  wave add $tbpath${ps}dma_ctrl_0${ps}m_axi_lite_araddr -into $id
  wave add $tbpath${ps}dma_ctrl_0${ps}m_axi_lite_arprot -into $id
  wave add $tbpath${ps}dma_ctrl_0${ps}m_axi_lite_rready -into $id
# wave add $tbpath${ps}dma_ctrl_0${ps}m_axi_lite_rvalid -into $id
# wave add $tbpath${ps}dma_ctrl_0${ps}m_axi_lite_rdata -into $id
# wave add $tbpath${ps}dma_ctrl_0${ps}m_axi_lite_rresp -into $id
# wave add $tbpath${ps}dma_ctrl_0${ps}m_axi_lite_awready -into $id
  wave add $tbpath${ps}dma_ctrl_0${ps}m_axi_lite_awvalid -into $id
  wave add $tbpath${ps}dma_ctrl_0${ps}m_axi_lite_awaddr -into $id
  wave add $tbpath${ps}dma_ctrl_0${ps}m_axi_lite_awprot -into $id
# wave add $tbpath${ps}dma_ctrl_0${ps}m_axi_lite_wready -into $id
  wave add $tbpath${ps}dma_ctrl_0${ps}m_axi_lite_wvalid -into $id
  wave add $tbpath${ps}dma_ctrl_0${ps}m_axi_lite_wdata -into $id
  wave add $tbpath${ps}dma_ctrl_0${ps}m_axi_lite_wstrb -into $id
  wave add $tbpath${ps}dma_ctrl_0${ps}m_axi_lite_bready -into $id
# wave add $tbpath${ps}dma_ctrl_0${ps}m_axi_lite_bvalid -into $id
# wave add $tbpath${ps}dma_ctrl_0${ps}m_axi_lite_bresp -into $id
  wave add $tbpath${ps}dma_ctrl_0${ps}interrupt -into $id

