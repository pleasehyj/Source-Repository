#include "exynos_4412.h"

//第2N个元素表示声调  第2N+1个元素表示该声调的时间
unsigned char MUSIC[500] ={
//祝你平安
0x26,0x20,0x20,0x20,0x20,0x20,0x26,0x10,0x20,0x10,0x20,0x80,0x26,0x20,0x30,0x20,
0x30,0x20,0x39,0x10,0x30,0x10,0x30,0x80,0x26,0x20,0x20,0x20,0x20,0x20,0x1c,0x20,
0x20,0x80,0x2b,0x20,0x26,0x20,0x20,0x20,0x2b,0x10,0x26,0x10,0x2b,0x80,0x26,0x20,
0x30,0x20,0x30,0x20,0x39,0x10,0x26,0x10,0x26,0x60,0x40,0x10,0x39,0x10,0x26,0x20,
0x30,0x20,0x30,0x20,0x39,0x10,0x26,0x10,0x26,0x80,0x26,0x20,0x2b,0x10,0x2b,0x10,
0x2b,0x20,0x30,0x10,0x39,0x10,0x26,0x10,0x2b,0x10,0x2b,0x20,0x2b,0x40,0x40,0x20,
0x20,0x10,0x20,0x10,0x2b,0x10,0x26,0x30,0x30,0x80,0x18,0x20,0x18,0x20,0x26,0x20,
0x20,0x20,0x20,0x40,0x26,0x20,0x2b,0x20,0x30,0x20,0x30,0x20,0x1c,0x20,0x20,0x20,
0x20,0x80,0x1c,0x20,0x1c,0x20,0x1c,0x20,0x30,0x20,0x30,0x60,0x39,0x10,0x30,0x10,
0x20,0x20,0x2b,0x10,0x26,0x10,0x2b,0x10,0x26,0x10,0x26,0x10,0x2b,0x10,0x2b,0x80,
0x18,0x20,0x18,0x20,0x26,0x20,0x20,0x20,0x20,0x60,0x26,0x10,0x2b,0x20,0x30,0x20,
0x30,0x20,0x1c,0x20,0x20,0x20,0x20,0x80,0x26,0x20,0x30,0x10,0x30,0x10,0x30,0x20,
0x39,0x20,0x26,0x10,0x2b,0x10,0x2b,0x20,0x2b,0x40,0x40,0x10,0x40,0x10,0x20,0x10,
0x20,0x10,0x2b,0x10,0x26,0x30,0x30,0x80,0x00,
//路边的野华不要采
0x30,0x1C,0x10,0x20,0x40,0x1C,0x10,0x18,0x10,0x20,0x10,0x1C,0x10,0x18,0x40,0x1C,
0x20,0x20,0x20,0x1C,0x20,0x18,0x20,0x20,0x80,0xFF,0x20,0x30,0x1C,0x10,0x18,0x20,
0x15,0x20,0x1C,0x20,0x20,0x20,0x26,0x40,0x20,0x20,0x2B,0x20,0x26,0x20,0x20,0x20,
0x30,0x80,0xFF,0x20,0x20,0x1C,0x10,0x18,0x10,0x20,0x20,0x26,0x20,0x2B,0x20,0x30,
0x20,0x2B,0x40,0x20,0x20,0x1C,0x10,0x18,0x10,0x20,0x20,0x26,0x20,0x2B,0x20,0x30,
0x20,0x2B,0x40,0x20,0x30,0x1C,0x10,0x18,0x20,0x15,0x20,0x1C,0x20,0x20,0x20,0x26,
0x40,0x20,0x20,0x2B,0x20,0x26,0x20,0x20,0x20,0x30,0x80,0x20,0x30,0x1C,0x10,0x20,
0x10,0x1C,0x10,0x20,0x20,0x26,0x20,0x2B,0x20,0x30,0x20,0x2B,0x40,0x20,0x15,0x1F,
0x05,0x20,0x10,0x1C,0x10,0x20,0x20,0x26,0x20,0x2B,0x20,0x30,0x20,0x2B,0x40,0x20,
0x30,0x1C,0x10,0x18,0x20,0x15,0x20,0x1C,0x20,0x20,0x20,0x26,0x40,0x20,0x20,0x2B,
0x20,0x26,0x20,0x20,0x20,0x30,0x30,0x20,0x30,0x1C,0x10,0x18,0x40,0x1C,0x20,0x20,
0x20,0x26,0x40,0x13,0x60,0x18,0x20,0x15,0x40,0x13,0x40,0x18,0x80,0x00,
};

unsigned int Num = 0;

void Dealy_Ms(unsigned int Time)
{
	unsigned int i,j;

	for(i=0;i<Time;i++)
		for(j=0;j<2500;j++);
}

void main(void)
{
	GPD0.CON = GPD0.CON & (~(0xF << 0)) | (0x2 << 0);
	/*将DPD0_0管脚设置成PWM功能*/
	PWM.TCFG0 = PWM.TCFG0 & (~(0xff)) | 99;
	/*一级预分频100000000/(99+1) = 1000000*/
	PWM.TCFG1 = PWM.TCFG1 & (~(0xf));
	/*二级预分频1000000/1 = 1000000*/
	PWM.TCON = PWM.TCON | (1 << 3);
	/*打开自动重装载功能*/
	PWM.TCNTB0 = 1000;
	/*设置频率为1MHZ/1000=1000HZ  周期为1/1000HZ=1ms*/
	PWM.TCMPB0 = 500;
	/*设置占空比  500/1000=50％*/
	PWM.TCON = PWM.TCON | (1 << 1);
	/*手动将TCNTB0中的值加载到TCNTB0*/
	PWM.TCON = PWM.TCON | 1 ;
	/*打开计数器0*/
	PWM.TCON = PWM.TCON & ~((1 << 1));
	/*关闭手动装载*/

	while(1)
	{
		PWM.TCON = PWM.TCON | (1 << 3);
		PWM.TCNTB0 = MUSIC[2*Num] << 5;
		PWM.TCMPB0 = PWM.TCNTB0/2;
		PWM.TCON = PWM.TCON | (1 << 1);
		PWM.TCON = PWM.TCON | 1 ;
		PWM.TCON = PWM.TCON & ~((1 << 1));
		Dealy_Ms(MUSIC[2*Num+1]*10);
		Num ++;
		if(Num == 200)
			Num = 0;
	}
}
