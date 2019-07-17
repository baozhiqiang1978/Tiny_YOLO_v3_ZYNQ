/******************************************************************************
*
* Copyright (C) 2009 - 2014 Xilinx, Inc.  All rights reserved.
*
* Permission is hereby granted, free of charge, to any person obtaining a copy
* of this software and associated documentation files (the "Software"), to deal
* in the Software without restriction, including without limitation the rights
* to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
* copies of the Software, and to permit persons to whom the Software is
* furnished to do so, subject to the following conditions:
*
* The above copyright notice and this permission notice shall be included in
* all copies or substantial portions of the Software.
*
* Use of the Software is limited solely to applications:
* (a) running on a Xilinx device, or
* (b) that interact with a Xilinx device through a bus or interconnect.
*
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
* IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
* FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
* XILINX  BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
* WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF
* OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
* SOFTWARE.
*
* Except as contained in this notice, the name of the Xilinx shall not be used
* in advertising or otherwise to promote the sale, use or other dealings in
* this Software without prior written authorization from Xilinx.
*
******************************************************************************/

/*
 * helloworld.c: simple test application
 *
 * This application configures UART 16550 to baud rate 9600.
 * PS7 UART (Zynq) is not initialized by this application, since
 * bootrom/bsp configures it to baud rate 115200
 *
 * ------------------------------------------------
 * | UART TYPE   BAUD RATE                        |
 * ------------------------------------------------
 *   uartns550   9600
 *   uartlite    Configurable only in HW design
 *   ps7_uart    115200 (configured by bootrom/bsp)
 */
#include <stdio.h>
#include <math.h>

#include "xil_printf.h"
#include "xparameters.h"
#include <xtime_l.h>

#include "xyolo_yolo_top.h"
#include "xaxidma.h"

#include "layer_input_reduce.h"
#include "layer_output_sdk_reduce.h"
#include "layer_parameter.h"

//#include "yolo_fp.h"

XYolo_yolo_top yolo_yolo_top;
XYolo_yolo_top_Config *yolo_yolo_top_cfg;
XAxiDma axiDMA;
XAxiDma_Config *axiDMA_cfg;



void initPeripherals()
{
	printf("Initializing yolo_yolo_top\n");
	yolo_yolo_top_cfg = XYolo_yolo_top_LookupConfig(XPAR_YOLO_YOLO_TOP_0_DEVICE_ID);
	if(yolo_yolo_top_cfg)
	{
		int status = XYolo_yolo_top_CfgInitialize(&yolo_yolo_top,yolo_yolo_top_cfg);
		if(status != XST_SUCCESS)
		{
			printf("Error initializing yolo_yolo_top core\n");
		}
	}

	printf("Initializing AxiDMA\n");
	axiDMA_cfg = XAxiDma_LookupConfig(XPAR_AXIDMA_0_DEVICE_ID);
	if(axiDMA_cfg)
	{
		int status = XAxiDma_CfgInitialize(&axiDMA,axiDMA_cfg);
		if(status != XST_SUCCESS)
		{
			printf("Error initializing AxiDMA core\n");
		}
	}

	XAxiDma_IntrDisable(&axiDMA,XAXIDMA_IRQ_ALL_MASK,XAXIDMA_DEVICE_TO_DMA);
	XAxiDma_IntrDisable(&axiDMA,XAXIDMA_IRQ_ALL_MASK,XAXIDMA_DMA_TO_DEVICE);
}
short layer_output_hls_reduce[YOLO_INPUT_HEIGHT*YOLO_INPUT_WIDTH*MAX_KERNEL_NUM];

int main()
{
    //standard axi stream programme

	XTime tEnd, tStart;
	int time_used_hw;

    initPeripherals();

    XTime_GetTime(&tStart);

    XYolo_yolo_top_Set_activate_en_V(&yolo_yolo_top,0xfffffff3);
    XYolo_yolo_top_Set_input_h_V(&yolo_yolo_top,YOLO_INPUT_HEIGHT);
    XYolo_yolo_top_Set_input_w_V(&yolo_yolo_top,YOLO_INPUT_WIDTH);

    XYolo_yolo_top_Start(&yolo_yolo_top);


    Xil_DCacheFlushRange((u32)layer_input_reduce,YOLO_INPUT_HEIGHT*YOLO_INPUT_WIDTH*MAX_KERNEL_NUM*sizeof(short));
    Xil_DCacheFlushRange((u32)layer_output_hls_reduce,YOLO_INPUT_HEIGHT*YOLO_INPUT_WIDTH*MAX_KERNEL_NUM*sizeof(short));

   // printf("Sending data to IP core slave\n");
    XAxiDma_SimpleTransfer(&axiDMA,(u32)layer_input_reduce,YOLO_INPUT_HEIGHT*YOLO_INPUT_WIDTH*MAX_KERNEL_NUM*sizeof(short),XAXIDMA_DMA_TO_DEVICE);

	//printf("Get data\n");
	XAxiDma_SimpleTransfer(&axiDMA,(u32)layer_output_hls_reduce,YOLO_INPUT_HEIGHT*YOLO_INPUT_WIDTH*MAX_KERNEL_NUM*sizeof(short),XAXIDMA_DEVICE_TO_DMA);
	while(XAxiDma_Busy(&axiDMA,XAXIDMA_DEVICE_TO_DMA));

	Xil_DCacheInvalidateRange((u32)layer_output_hls_reduce,YOLO_INPUT_HEIGHT*YOLO_INPUT_WIDTH*MAX_KERNEL_NUM*sizeof(short));

	while(!XYolo_yolo_top_IsDone(&yolo_yolo_top));
    XTime_GetTime(&tEnd);

	printf("Calculation complete\n");
    time_used_hw = 1.0*((tEnd-tStart)*1000000)/(COUNTS_PER_SECOND);
    xil_printf("***%d(us)***\n\r", time_used_hw);

	for(int idx=0;idx<YOLO_INPUT_HEIGHT*YOLO_INPUT_WIDTH*MAX_KERNEL_NUM;idx++)
	{
		short ref = layer_output_sdk_reduce[idx];
		short get = layer_output_hls_reduce[idx];

		if(abs(ref-get)<16)
		{
			continue;
		}
		else
		{

			printf("Recv[%d]=%hd,Ref=%hd\n",idx,get,ref);
		}

	}

	printf("End\n");

    return 0;
}
