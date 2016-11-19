.text
.global _start
_start:
		@ �쳣������  ƫ�Ƶ�ַ˳���ܸı�
		b		reset
		ldr		pc,_undefined_instruction
		ldr		pc,_software_interrupt
		ldr		pc,_prefetch_abort
		ldr		pc,_data_abort
		@ ������������ҲҪ���һ��ָ�����������������ַ�����ƫ��
		ldr		pc,_not_used
		ldr		pc,_irq
		ldr		pc,_fiq

@ �������쳣������������ڵ�ַ�����ڵ�ǰλ��
_undefined_instruction: .word  _undefined_instruction
_software_interrupt:	.word  _software_interrupt
_prefetch_abort:		.word  _prefetch_abort
_data_abort:			.word  _data_abort
_not_used:			    .word  _not_used
_irq:				    .word  irq_handler
_fiq:				    .word  _fiq


reset:
	@ �����쳣���������¶�λ��0x40008000��ַ�����
	ldr	r0,=0x40008000
	mcr	p15,0,r0,c12,c0,0		@ Vector Base Address Register

	@ ��ʼ������Ӳ���ӿ�
		mrs  	r0,cpsr
		bic		r0,r0,#0x1f
		orr		r0,r0,#0xd3
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
	MOV r3, #0x40000000
	fmxr FPEXC, r3

	/*
	 * disable MMU stuff and caches
	 */
	mrc	p15, 0, r0, c1, c0, 0
	bic	r0, r0, #0x00002000	@ clear bits 13 (--V-)
	bic	r0, r0, #0x00000007	@ clear bits 2:0 (-CAM)
	orr	r0, r0, #0x00001000	@ set bit 12 (---I) Icache
	orr	r0, r0, #0x00000002	@ set bit 1  (--A-) Align
	orr	r0, r0, #0x00000800	@ set bit 11 (Z---) BTB
	mcr	p15, 0, r0, c1, c0, 0

/* LED Test Code */

	ldr r0, =0x114001E0
	ldr r1, [r0]
	bic r1, r1, #0xf0000
	orr r1, r1, #0x10000
	str r1, [r0]

	ldr r0, =0x114001E8
	ldr r1, [r0]
	bic r1, r1, #0x300
	str r1, [r0]

	ldr r0, =0x114001E4
	ldr r1, [r0]
	orr r1, r1, #0x10
	str r1, [r0]

@ ��ʼ������ģʽ��ջ�ռ�
init_stack:
		@ ������ջ�ռ��ջ����ֵ��R0
		ldr		r0,stacktop         /*get stack top pointer*/

	/********svc mode stack********/
		@ ��ʼ��SVCģʽ�µ�ջ
		mov		sp,r0
		@ ջ���½�512�ֽ�
		sub		r0,#128*4          /*512 byte  for irq mode of stack*/
	/****irq mode stack**/
		@ �л�ģʽ��IRQģʽ
		msr		cpsr,#0xd2
		@ ��ʼ��IRQģʽ�µ�ջ��
		mov		sp,r0
		@ ջ���½�512�ֽ�
		sub		r0,#128*4          /*512 byte  for irq mode of stack*/
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
		msr		cpsr,#0x10
		mov		sp,r0             /*1024 byte  for user mode of stack*/

		@ ��ת��main����
		b		main

	.align	4

	/****  swi_interrupt handler  ****/


/****  irq_handler  ****/
@ �жϴ�������
irq_handler:
	@ ���ص�ַ����
	sub  lr,lr,#4
	@ ��һ�������ֳ�  ��R0-R12�Ĵ����е�ֵ���浽ջ�ռ�   ͬʱ�ѷ��ص�ַҲѹջ
	stmfd sp!,{r0-r12,lr}
	@ α����  do_irq����û�����Ǳ���ʱ������
	.weak do_irq
	@ ��ת���жϴ�������  ���淵�ص�ַ��LR��
	bl	do_irq
	@ ��ջ�ָ��ֳ�  ͬʱ��LR��ֵ��PCʵ�ֳ���ķ���  ^��ʾ��ջ��ͬʱ�ָ�CPSR
	ldmfd sp!,{r0-r12,pc}^

@ ջ����ʼ������ջ�ռ����ߵ�ַ��  ��Ϊʹ�õ�ջ������ջ
stacktop:    .word 		stack+4*512

@ ��ջ�ռ��ʼ�������ݶ���
.data
@ �ڵ�ǰλ��������4*512���ֽڵĿռ���Ϊջ�ռ�
stack:	 .space  4*512