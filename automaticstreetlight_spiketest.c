#include <stdio.h>

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

for( int i=0; i<8;i++)
{
pir_value=1;
ldr_value=1;
printf("pir_value=%d\n",pir_value);
printf("ldr_value=%d\n",ldr_value);
          

if (((pir_value)&&(ldr_value)) == 1)
{
control = 1;
control_reg = control * 8;
asm volatile(
		"and x30, x30, %1 \n\t"
		"and x30, x30, %0\n\t"		
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
		"and x30, x30, %0\n\t"		
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
