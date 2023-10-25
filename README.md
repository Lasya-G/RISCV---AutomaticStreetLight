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
		:
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

asm_out  :     file format elf32-littleriscv


Disassembly of section .text:

00010054 <main>:
   10054:   ff010113                addi  sp,sp,-16
   10058:   00112623                sw    ra,12(sp)
   1005c:   00812423                sw    s0,8(sp)
   10060:   01010413                addi  s0,sp,16
   10064:   0bc000ef                jal   ra,10120 <read>
   10068:   ffdff06f                j     10064 <main+0x10>

0001006c <read_pir_sensor>:
   1006c:   fe010113                addi  sp,sp,-32
   10070:   00812e23                sw    s0,28(sp)
   10074:   02010413                addi  s0,sp,32
   10078:   001f6793                ori   a5,t5,1
   1007c:   fef42623                sw    a5,-20(s0)
   10080:   00000013                nop
   10084:   00078513                mv    a0,a5
   10088:   01c12403                lw    s0,28(sp)
   1008c:   02010113                addi  sp,sp,32
   10090:   00008067                ret

00010094 <read_ldr_sensor>:
   10094:   fe010113                addi  sp,sp,-32
   10098:   00812e23                sw    s0,28(sp)
   1009c:   02010413                addi  s0,sp,32
   100a0:   001f6793                ori   a5,t5,1
   100a4:   fef42623                sw    a5,-20(s0)
   100a8:   00000013                nop
   100ac:   00078513                mv    a0,a5
   100b0:   01c12403                lw    s0,28(sp)
   100b4:   02010113                addi  sp,sp,32
   100b8:   00008067                ret

000100bc <controller>:
   100bc:   fe010113                addi  sp,sp,-32
   100c0:   00812e23                sw    s0,28(sp)
   100c4:   02010413                addi  s0,sp,32
   100c8:   fec42783                lw    a5,-20(s0)
   100cc:   02078663                beqz  a5,100f8 <controller+0x3c>
   100d0:   fe842783                lw    a5,-24(s0)
   100d4:   02078263                beqz  a5,100f8 <controller+0x3c>
   100d8:   00100793                li    a5,1
   100dc:   fef42223                sw    a5,-28(s0)
   100e0:   fe442783                lw    a5,-28(s0)
   100e4:   00579793                slli  a5,a5,0x5
   100e8:   fef42023                sw    a5,-32(s0)
   100ec:   fe042783                lw    a5,-32(s0)
   100f0:   00ff7f33                and   t5,t5,a5
   100f4:   01c0006f                j     10110 <controller+0x54>
   100f8:   fe042223                sw    zero,-28(s0)
   100fc:   fe442783                lw    a5,-28(s0)
   10100:   00579793                slli  a5,a5,0x5
   10104:   fef42023                sw    a5,-32(s0)
   10108:   fe042783                lw    a5,-32(s0)
   1010c:   00ff7f33                and   t5,t5,a5
   10110:   00000013                nop
   10114:   01c12403                lw    s0,28(sp)
   10118:   02010113                addi  sp,sp,32
   1011c:   00008067                ret

00010120 <read>:
   10120:   ff010113                addi  sp,sp,-16
   10124:   00112623                sw    ra,12(sp)
   10128:   00812423                sw    s0,8(sp)
   1012c:   01010413                addi  s0,sp,16
   10130:   f8dff0ef                jal   ra,100bc <controller>
   10134:   00000013                nop
   10138:   00c12083                lw    ra,12(sp)
   1013c:   00812403                lw    s0,8(sp)
   10140:   01010113                addi  sp,sp,16
   10144:   00008067                ret

```


### Unique Instructions
To find the number of unique instructions make sure to rename the filename as sample_assembly.txt since the python script that we are using is opening the file name with sample_assembly.txt and both files should be in the same directory. The python script I am using is already uploaded. Now follow the command to get the number of different instructions used.
```
$ python3 instruction_counter.py // use this command after ensuring we are in the same directory as the script
```
Number of different instructions: 13  
List of unique instructions:  
mv  
addi  
li  
slli  
sw  
j  
beqz  
nop  
ori  
jal  
and  
lw  
ret  





