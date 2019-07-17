// ==============================================================
// Vivado(TM) HLS - High-Level Synthesis from C, C++ and SystemC v2019.1 (64-bit)
// Copyright 1986-2019 Xilinx, Inc. All Rights Reserved.
// ==============================================================
// CTRL_BUS
// 0x00 : Control signals
//        bit 0  - ap_start (Read/Write/COH)
//        bit 1  - ap_done (Read/COR)
//        bit 2  - ap_idle (Read)
//        bit 3  - ap_ready (Read)
//        bit 7  - auto_restart (Read/Write)
//        others - reserved
// 0x04 : Global Interrupt Enable Register
//        bit 0  - Global Interrupt Enable (Read/Write)
//        others - reserved
// 0x08 : IP Interrupt Enable Register (Read/Write)
//        bit 0  - Channel 0 (ap_done)
//        bit 1  - Channel 1 (ap_ready)
//        others - reserved
// 0x0c : IP Interrupt Status Register (Read/TOW)
//        bit 0  - Channel 0 (ap_done)
//        bit 1  - Channel 1 (ap_ready)
//        others - reserved
// 0x10 : Data signal of activate_en_V
//        bit 31~0 - activate_en_V[31:0] (Read/Write)
// 0x14 : reserved
// 0x18 : Data signal of input_h_V
//        bit 4~0 - input_h_V[4:0] (Read/Write)
//        others  - reserved
// 0x1c : reserved
// 0x20 : Data signal of input_w_V
//        bit 4~0 - input_w_V[4:0] (Read/Write)
//        others  - reserved
// 0x24 : reserved
// (SC = Self Clear, COR = Clear on Read, TOW = Toggle on Write, COH = Clear on Handshake)

#define XYOLO_YOLO_TOP_CTRL_BUS_ADDR_AP_CTRL            0x00
#define XYOLO_YOLO_TOP_CTRL_BUS_ADDR_GIE                0x04
#define XYOLO_YOLO_TOP_CTRL_BUS_ADDR_IER                0x08
#define XYOLO_YOLO_TOP_CTRL_BUS_ADDR_ISR                0x0c
#define XYOLO_YOLO_TOP_CTRL_BUS_ADDR_ACTIVATE_EN_V_DATA 0x10
#define XYOLO_YOLO_TOP_CTRL_BUS_BITS_ACTIVATE_EN_V_DATA 32
#define XYOLO_YOLO_TOP_CTRL_BUS_ADDR_INPUT_H_V_DATA     0x18
#define XYOLO_YOLO_TOP_CTRL_BUS_BITS_INPUT_H_V_DATA     5
#define XYOLO_YOLO_TOP_CTRL_BUS_ADDR_INPUT_W_V_DATA     0x20
#define XYOLO_YOLO_TOP_CTRL_BUS_BITS_INPUT_W_V_DATA     5

