#include "exynos_4412.h"
#include "debug.h"
#define LED_ON_TIMER 0xfffff
void delay(unsigned int x){
	unsigned int timer=x;
	while(timer--);
}

void irq57_handler(void){
	deprint("irq57\n");
	GPX1.CON=GPX1.CON&(~(0xf<<0))|(0x1<<0);
	GPX1.DAT|=(0x1<<0);
	delay(LED_ON_TIMER);
	GPX1.DAT&=~(0x1<<0);
}
void irq58_handler(void){
	deprint("irq58\n");
	GPF3.CON=GPX2.CON&(~(0xf)<<16)|(0x1<<16);
	GPF3.DAT|=(0x1<<4);
	delay(LED_ON_TIMER);
	GPF3.DAT&=~(0x1<<4);
}
void do_irq(void){
	volatile unsigned int IRQ_ID=CPU0.ICCIAR & 0x3ff;
	switch (IRQ_ID){
	case 57:
		irq57_handler();
		//	EXT_INT41_PEND=EXT_INT41_PEND|(0x1<<1);
		//	BUG!!!，写一置零，如果低位本来是1,会将其一起清零
		EXT_INT41_PEND=0x2;
		break;
	case 58:
		irq58_handler();
		EXT_INT41_PEND=0x4;
		break;
	default:
		break;
	}
	deprint("switch over\n");
	CPU0.ICCEOIR = CPU0.ICCEOIR & (~(0x3ff))|IRQ_ID;	//将中断号告诉中断控制器，表示中断处理完毕，可以将下一个pending的中断送入
}
/* 外设
 * UART_RING=>GPX1_1(0xF)
 * EXT_INT41CON falling triger
 * EXT_INT41FLTCON0 //滤波
 * EXT_INT41_MASK	//使能/屏蔽中断
 * EXT_INT41_PEND
 * //中断挂起位，有中断就置一，是1就自动给GIC送中断，所以相应完毕之后就应该将其清零(写一清零)
 */ 
/* GIC
 * 可以通过设置GIC的寄存器使其触发一个irq给cpu<<--这里的软中断
 * 三类中断SGI，PPI，SPI
 * P741
 * 中断状态inactive pending active active and pending
 * P749 中断号：不是优先级，每一个中断都有一个独立的编号，57
 * P770 中断状态
 * P798 ICDDCRA GIC的总开关
 * ICDISER_CPU0 160个中断源每一个中断源有一位管理，
 * ICDISER1_CPU0
 * ICDIPTR_CPU
 * 160个中断，每个中断有8bit来管理这个中断交给哪个cpu来处理
 * 0x838 ICDIPTR14[15:7]
 * GIC有一个默认的优先级，默认irq
 */
/* CPU
 * ICCICR_CPUn使能相应的CPU
 * ICCPMR_CPUn
 */ 

int main()
{
	//外设
	//1. 将GPX1_1 GPX1_2 设置为中断功能GPX1CON
	GPX1.CON=GPX1.CON|(0xff<<4);
	detobin(GPX1.CON);
		
	//2. 设置GPX1_1 GPX1_2的触发方式 EXT_INT41_MASK
	EXT_INT41_CON=EXT_INT41_CON|(0x22);
	detobin(EXT_INT41_CON);

	//3. 使能GPX1_1 GPX1_2中断
	EXT_INT41_MASK=EXT_INT41_MASK&(~(0x3<<1));
	detobin(EXT_INT41_MASK);

	//GIC
	//4. 全局使能GIC使其可以监控外设的中断信号并转发到CPU接口
	ICDDCR=1;
	detobin(ICDDCR);
	//5. 在中断管理器中使能57,58号中断，ICDISER1[25]
	ICDISER.ICDISER1=ICDISER.ICDISER1|(0x3<<25);
	detobin(ICDISER.ICDISER1);	

	//6. 给57 58号中断选择一个目标CPU0 ICDIPTR14[23:16][15:8]
	ICDIPTR.ICDIPTR14=ICDIPTR.ICDIPTR14|(0x1<<16)|(0x1<<8);	
	detobin(ICDIPTR.ICDIPTR14);

	//CPU
	//7. 全局使能中断信号能够通过CPU0接口到达处理器 
	CPU0.ICCICR=1;	
	detobin(CPU0.ICCICR);

	//8. 优先级低于ICCPMR的中断才能被送入cpu，使所有的中断都能够经过CPU0接口到达处理器
	CPU0.ICCPMR=0xff;
	detobin(CPU0.ICCPMR);
	while(1);

	return 0;
}
