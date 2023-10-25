#include <stdio.h>

int main()
{
int pir_value;
int ldr_value;
int control;

printf("Enter pir and ldr value : \n");
scanf("%d %d", &pir_value, &ldr_value);

while(1)
{

if (((pir_value)&&(ldr_value)) == 1)
{
control = 1;
printf("Light is ON\n");
printf("control=%d\n",control);
//control_reg = control * 16;
}

else
{
control = 0;
printf("Light is OFF\n");
printf("control=%d\n",control);
//control_reg = control *16;
}
}
return 0;
}

