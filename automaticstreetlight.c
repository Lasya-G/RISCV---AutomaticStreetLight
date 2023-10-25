#include <stdio.h>

int main()
{
int pir_value;
int ldr_value;
int control;
int control_reg;

while(1)
{
asm volatile(
            "or %0, x30, 1\n\t"
            :"=r"(pir_value)
        );

asm volatile(
            "or %0, x30, 1\n\t"
            : "=r"(ldr_value)
        );

if (((pir_value)&&(ldr_value)) == 1)
{
control = 1;
control_reg = control * 16;
asm volatile(
		"and x30, x30, %0 \n\t"
		"and x30, x30, %1\n\t"		
		:
		:"r"(control), "r"(mask)
		:"x30"
		);
}

else
{
control = 0;
control_reg = control *16;
asm volatile(
		"and x30, x30, %0 \n\t"
		"and x30, x30, %1\n\t"		
		:
		:"r"(control), "r"(mask)
		:"x30"
		);
}
}
return 0;
}
