#include <stdio.h>

int main()
{
int pir_value;
int ldr_value;
int ldr_value_reg;
int x,y;
int control;
int control_reg;
int mask = 0xFFFFFFF7;
int testing;

                asm volatile(
                "andi x30, x30, 0x0000\n\t"
	    	:
	    	: 
		: "x30" 
		);

for( int i=0; i<8;i++)
{
/*
if (i<2)
{
x = 0;
y = 0;
}
else if (2<=i<4)
{
x = 0;
y = 1;
}
else if (4<=i<6)
{
x = 1;
y = 0;
}
else
{
x = 1;
y = 1;
}
ldr_value_reg = y *2;
asm volatile(
	    "or x30, x30, %1\n\t"
            "andi %0, x30, 0x01\n\t"
            :"=r"(pir_value)
            :"r"(x)
            :"x30"
            );

asm volatile(
	    "or x30, x30, %1\n\t"
            "andi %0, x30, 0x02\n\t"
            : "=r"(ldr_value)
            :"r"(ldr_value_reg)
            :"x30"
            );
*/
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
