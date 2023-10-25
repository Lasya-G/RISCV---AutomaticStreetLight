## AutomaticStreetLight

### Project Overview
The objective of this project is to design an automated Street Lightening system. Our focus is to implement this innovative solution using a RISC-V processor, a departure from traditional Arduino boards. The primary motivation for this endeavor is to enhance efficiency by  minimising the usage of the energy in the street light systems.   
The components used in this project are: LDR sensor, PIR sensor, RISC-V Processor, Relay module, LED.  

*LDR sensor*: It automatically switches ON lights when the sunlight goes below the visible region of our eyes. This is done by a sensor called Light Dependent Resistor (LDR) which senses the light actually like our eyes. It automatically switches OFF lights whenever the sunlight comes, visible to our eyes.

*PIR sensor*: PIR sensors are commonly called simply "PIR", or sometimes "PID", for "passive infrared detector". The term passive refers to the fact that PIR devices do not radiate energy for detection purposes. They work entirely by detecting infrared radiation (radiant heat) emitted by or reflected from objects.   

### Block Diagram

<img width="600" alt="image0" src="https://github.com/Lasya-G/RISCV---AutomaticStreetLight/assets/140998582/503047b1-52e1-462f-a545-33e1f01be7e7">

### Flow Chart

<img width="600" alt="Screenshot from 2023-10-05 09-32-06" src="https://github.com/Lasya-G/RISCV---AutomaticStreetLight/assets/140998582/e7481ccf-5ee6-48cf-8235-05d677df5f6a"> 

### C Code

```
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

```

C code can be compiled using following commands:
```
gcc ASL.c
./a.out
```

### C Code simulation results  
<img width="500" alt="Screenshot from 2023-10-25 15-01-19" src="https://github.com/Lasya-G/RISCV---AutomaticStreetLight/assets/140998582/db899425-7b9c-46b6-9774-e0021f3a451d">  
<img width="500" alt="Screenshot from 2023-10-25 15-01-06" src="https://github.com/Lasya-G/RISCV---AutomaticStreetLight/assets/140998582/d7e59340-8a85-4dbc-803d-ca2f01765d14">  

### Modified C code for Spike Simulation
```
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
```
Use the following commands t perform spike simulation:
```
 riscv64-unknown-elf-gcc -march=rv64i -mabi=lp64 -ffreestanding -o out automaticstreetlight_spiketest.c
 spike pk out
```


### Spike simulation Results

As per my application, whenever both the sensors i.e; pir sensor as well as ldr sensor reads high value, the street light should be ON(control=1). In all the other cases the light should be OFF(control=0). We can observe the spike simulation results for all the four possible input combinations and their corresponding output functionality.
<img width="700" alt="image" src="https://github.com/Lasya-G/RISCV---AutomaticStreetLight/assets/140998582/3b6fbf33-3a43-498c-b3b2-e47c523bc7c2">   
<img width="700" alt="image" src="https://github.com/Lasya-G/RISCV---AutomaticStreetLight/assets/140998582/2f1e95a5-5eb5-49ad-aa8b-cd3964da6c86">  
<img width="700" alt="image" src="https://github.com/Lasya-G/RISCV---AutomaticStreetLight/assets/140998582/bb5893d5-1ade-44e6-a9a6-f0d32c12e9e3">
<img width="700" alt="image" src="https://github.com/Lasya-G/RISCV---AutomaticStreetLight/assets/140998582/ec3d530f-7046-4fda-8bbc-24a6c3485c45">    


### Assembly code  

```


out:     file format elf32-littleriscv


Disassembly of section .text:

00010054 <main>:
   10054:	fd010113          	addi	sp,sp,-48
   10058:	02812623          	sw	s0,44(sp)
   1005c:	03010413          	addi	s0,sp,48
   10060:	ff700793          	li	a5,-9
   10064:	fef42623          	sw	a5,-20(s0)
   10068:	000f7f13          	andi	t5,t5,0
   1006c:	001f7793          	andi	a5,t5,1
   10070:	fef42423          	sw	a5,-24(s0)
   10074:	002f7793          	andi	a5,t5,2
   10078:	fef42223          	sw	a5,-28(s0)
   1007c:	fe842783          	lw	a5,-24(s0)
   10080:	00078a63          	beqz	a5,10094 <main+0x40>
   10084:	fe442783          	lw	a5,-28(s0)
   10088:	00078663          	beqz	a5,10094 <main+0x40>
   1008c:	00100793          	li	a5,1
   10090:	0080006f          	j	10098 <main+0x44>
   10094:	00000793          	li	a5,0
   10098:	00100713          	li	a4,1
   1009c:	02e79663          	bne	a5,a4,100c8 <main+0x74>
   100a0:	00100793          	li	a5,1
   100a4:	fef42023          	sw	a5,-32(s0)
   100a8:	fe042783          	lw	a5,-32(s0)
   100ac:	00379793          	slli	a5,a5,0x3
   100b0:	fcf42e23          	sw	a5,-36(s0)
   100b4:	fdc42783          	lw	a5,-36(s0)
   100b8:	fec42703          	lw	a4,-20(s0)
   100bc:	00ef7f33          	and	t5,t5,a4
   100c0:	00ff6f33          	or	t5,t5,a5
   100c4:	fa9ff06f          	j	1006c <main+0x18>
   100c8:	fe042023          	sw	zero,-32(s0)
   100cc:	fe042783          	lw	a5,-32(s0)
   100d0:	00379793          	slli	a5,a5,0x3
   100d4:	fcf42e23          	sw	a5,-36(s0)
   100d8:	fdc42783          	lw	a5,-36(s0)
   100dc:	fec42703          	lw	a4,-20(s0)
   100e0:	00ef7f33          	and	t5,t5,a4
   100e4:	00ff6f33          	or	t5,t5,a5
   100e8:	f85ff06f          	j	1006c <main+0x18>

```


### Unique Instructions
To find the number of unique instructions make sure to rename the filename as sample_assembly.txt since the python script that we are using is opening the file name with sample_assembly.txt and both files should be in the same directory. The python script I am using is already uploaded. Now follow the command to get the number of different instructions used.
```
$ python3 instruction_counter.py // use this command after ensuring we are in the same directory as the script
```
Number of different instructions: 11  
List of unique instructions:  
lw  
sw  
addi  
and  
slli  
or  
j  
beqz  
bne  
li  
andi  






