//#include <stdio.h>

int main()
{
int pir_value;
int ldr_value;
int control;
int control_reg;
int mask = 0xFFFFFFF7;


asm volatile(
                "andi x30, x30, 0x0000\n\t"
	    	:
	    	: 
		: "x30" 
		);

while(1)

asm volatile(
		"andi %0, x30, 0x01\n\t"
		: "=r" (pir_value)
		:
		:);
		
		
asm volatile(
		"andi %0, x30, 0x02\n\t"
		: "=r" (ldr_value)
		:
		:);         

if (((pir_value)&&(ldr_value)) == 1)
{
control = 1;
control_reg = control * 8;
asm volatile(
		"and x30, x30, %1 \n\t"
		"or x30, x30, %0\n\t"		
		:
		:"r"(control_reg), "r"(mask)
		:"x30"
		);
		
     	
printf("control= %d\n", control);
printf("Light is ON\n");
}

else
{
control = 0;
control_reg = control *8;
asm volatile(
		"and x30, x30, %1 \n\t"
		"or x30, x30, %0\n\t"		
		:
		:"r"(control_reg), "r"(mask)
		:"x30"
		)
printf("control= %d\n", control);
printf("Light is OFF\n");
}
}
return 0;
}
