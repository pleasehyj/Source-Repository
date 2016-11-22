.text
.global _start
_start:	@异常向量表，这里设置异常向量表的基地址，line24=>基地址为0x40008000
		b		reset
		ldr		pc,_undefined_instruction	;
		ldr		pc,_software_interrupt
		ldr		pc,_prefetch_abort
		ldr		pc,_data_abort
		ldr		pc,_not_used	@reserved
		ldr		pc,_irq
		ldr		pc,_fiq

_undefined_instruction: .word  _undefined_instruction
_software_interrupt:	.word  _software_interrupt
_prefetch_abort:		.word  _prefetch_abort
_data_abort:			.word  _data_abort
_not_used:			.word  _not_used
_irq:					.word  irq_handler
_fiq:				.word  _fiq


reset:
	
	ldr	r0,=0x40008000
	mcr	p15,0,r0,c12,c0,0		@ Vector Base Address Register
								//把r0中的数据写入到协处理器p15里面的寄存器c12中

		mrs  	r0,cpsr			//保存cpsr到r0寄存器
		bic		r0,r0,#0x1f		//r0低5置零
		orr		r0,r0,#0xd3		//r0低5位置为SVC
		msr		cpsr,r0         @ Enable svc mode of cpu

    	mov	r0, #0xfffffff
      	mcr	p15, 0, r0, c1, c0, 2  	@ Defines access permissions for each coprocessor
									@ Privileged and User mode access

	/*
	 * Invalidate L1 I/D
	 */
	mov	r0, #0			@ set up for MCR
	mcr	p15, 0, r0, c8, c7, 0	@ invalidate TLBs
	mcr	p15, 0, r0, c7, c5, 0	@ invalidate icache


	@Set the FPEXC EN bit to enable the FPU:
	MOV r3, #0x40000000			@设置浮点运算
	fmxr FPEXC, r3

	/*
	 * disable MMU stuff and caches，关闭MMU
	 */
	mrc	p15, 0, r0, c1, c0, 0
	bic	r0, r0, #0x00002000	@ clear bits 13 (--V-)
	bic	r0, r0, #0x00000007	@ clear bits 2:0 (-CAM)
	orr	r0, r0, #0x00001000	@ set bit 12 (---I) Icache
	orr	r0, r0, #0x00000002	@ set bit 1  (--A-) Align
	orr	r0, r0, #0x00000800	@ set bit 11 (Z---) BTB
	mcr	p15, 0, r0, c1, c0, 0

init_stack:
		ldr		r0,stacktop         /*get stack top pointer*/

	/********svc mode stack********/
		mov		sp,r0
		sub		r0,#128*4          	/*512 byte  for irq mode of stack*/
	/****irq mode stack**/
		msr		cpsr,#0xd2			//切换到irq模式
		mov		sp,r0
		sub		r0,#128*4          	/*512 byte  for irq mode of stack*/
	/***fiq mode stack***/
		msr 	cpsr,#0xd1
		mov		sp,r0
		sub		r0,#0
	/***abort mode stack***/
		msr		cpsr,#0xd7
		mov		sp,r0
		sub		r0,#0
	/***undefine mode stack***/
		msr		cpsr,#0xdb
		mov		sp,r0
		sub		r0,#0
   /*** sys mode and usr mode stack ***/
		msr		cpsr,#0x10			//最后一次初始化usr模式的栈，1.方便直接b main, 2. 如果之前切换到usr，不便于切换回其他的特权模式，usr不能直接修改cpsr来切换，但是特权模式可以
									//切换到usr模式的同时，将irq，fiq打开
		mov		sp,r0             	/*1024 byte  for user mode of stack*/

		b		main				//跳转到main函数

	.align	4

	/****  swi_interrupt handler  ****/


	/****  irq_handler  ****/
irq_handler:

	sub  lr,lr,#4					//lr=lr-4，lr是执行跳转前执行指令的下一条指令的地址，
									//异常返回的地址应该是跳转前执行的指令地址，而不是下一条，
									//这点和函数调用不一样，因为调用本身占用一条指令，但是异常不会占用指令
									//函数调用和SWI在指令执行期间进行lr=pc-4,irq/fiq是在指令执行完毕后进行lr=pc-4，此时pc已经移动了，所以这样操作lr会跳过本该执行的下一条指令，所以我们要lr=lr-4
	stmfd sp!,{r0-r12,lr}			//将现场进行压栈，已经进入irq模式，所以这里的sp是irq的sp，用来保护usr模式的r0-r12,lr
	.weak do_irq					//声明一个弱符号，即便符号没有定义，也不会报错
	bl	do_irq						//do_irq 即异常处理程序
	ldmfd sp!,{r0-r12,pc}^			//出栈恢复现场，pc里放的lr的值，^表示出栈的同时从SPSR恢复CPSR

stacktop:    .word 		stack+4*512
.data

stack:	 .space  4*512
