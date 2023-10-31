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

### Functionality Simulation    

The processor and testbench verilog codes used for the functionality simulation are uploaded.  

We run functionality simulation by following commands:
```
iverilog processor.v testbench.v
./a.out
gtkwave waveform.vcd
```

The functinality of my code should be as follows:  
Inputs - Output  
00 - 0  
01 - 0  
10 - 0  
11 - 1  

The "$signal" flag depicts the x30 register.

<img width="700" alt="Screenshot from 2023-10-27 17-11-19" src="https://github.com/Lasya-G/RISCV---AutomaticStreetLight/assets/140998582/ec3c97b9-50b5-4b98-b5d8-32457b0c38ed">   
<img width="700" alt="Screenshot from 2023-10-27 17-10-03" src="https://github.com/Lasya-G/RISCV---AutomaticStreetLight/assets/140998582/7d80fc9d-db1e-4500-a0d9-24ebcb2267ba">  
<img width="700" alt="Screenshot from 2023-10-27 17-07-57" src="https://github.com/Lasya-G/RISCV---AutomaticStreetLight/assets/140998582/d68be628-73e2-4901-ae7f-6308d022333c">  
<img width="700" alt="Screenshot from 2023-10-27 17-06-05" src="https://github.com/Lasya-G/RISCV---AutomaticStreetLight/assets/140998582/2fb727b9-4a4c-40bb-a596-1f2e7de8941b">  

In the images we can observe that the ID_instructions are incrementing in accordance with the assembly code.  

- The input pins is of 2-bits where each bit represents each input sensor namely LDR sensor and PIR sensor.
- The functionality for the code is given such that the output should be high only when both the inputs are high.
- We can observe from the above images that the code functionality is correct as the output is becoming high only for a single input combination i.e; 11.


### GLS  


- We perform the Gate Level Simulation on the netlist file synthesised from yosys.
- This file basically maps the standard cells of sky130 library to our design
- Performing the GLS on our design, validates the logic of our design that is generated.
- We need to make some minor changes inorder to run GLS which can be observed in the module instantiation of the sram blocks of the below images:
<img width="500" alt="image" src="https://github.com/Lasya-G/RISCV---AutomaticStreetLight/assets/140998582/168b8937-06d9-4041-989a-bb3950fe65f0">
<img width="500" alt="Screenshot from 2023-10-31 21-41-44" src="https://github.com/Lasya-G/RISCV---AutomaticStreetLight/assets/140998582/c652ab3f-06f9-4b55-a439-89fa817c30f1">

- Following are the steps to convert our processor code to netlist:
```
read_liberty -lib sky130_fd_sc_hd__tt_025C_1v80_256.lib 
read_verilog processor.v
synth -top wrapper
dfflibmap -liberty sky130_fd_sc_hd__tt_025C_1v80_256.lib 
abc -liberty sky130_fd_sc_hd__tt_025C_1v80_256.lib
write_verilog syntheised__processor_test.v
```

<img width="1000" alt="Screenshot from 2023-10-31 21-29-52" src="https://github.com/Lasya-G/RISCV---AutomaticStreetLight/assets/140998582/7bdff079-b3c3-4112-970d-5d50fd621485">  
<img width="1000" alt="Screenshot from 2023-10-31 21-42-28" src="https://github.com/Lasya-G/RISCV---AutomaticStreetLight/assets/140998582/55f666f0-e264-426d-9b25-a66c22b8f4de">
<img width="1000" alt="Screenshot from 2023-10-31 21-43-10" src="https://github.com/Lasya-G/RISCV---AutomaticStreetLight/assets/140998582/2eb24564-3695-4668-bacf-2203feb12fea">
<img width="1000" alt="Screenshot from 2023-10-31 21-43-59" src="https://github.com/Lasya-G/RISCV---AutomaticStreetLight/assets/140998582/70ad1b2c-f920-4c59-9312-a7ba98ca2daf">
<img width="1000" alt="Screenshot from 2023-10-31 21-44-41" src="https://github.com/Lasya-G/RISCV---AutomaticStreetLight/assets/140998582/a21c47c3-38cd-4d4c-a06f-9db953e7561b">
<img width="1000" alt="Screenshot from 2023-10-31 21-45-09" src="https://github.com/Lasya-G/RISCV---AutomaticStreetLight/assets/140998582/21d7cabc-01a4-450a-87d7-2bd4207ac2ab">  



- To run the GLS simulation, follow the below commands:
```
iverilog -o a.out testbench.v synth_processor_test.v sky130_sram_1kbyte_1rw1r_32x256_8.v sky130_fd_sc_hd.v primitives.v 
./a.out
gtkwave waveform.vcd
```
<img width="1000" alt="Screenshot from 2023-10-31 22-29-43" src="https://github.com/Lasya-G/RISCV---AutomaticStreetLight/assets/140998582/6671ead3-2a92-4b2f-b79b-a6484c292e8c">
<img width="1000" alt="Screenshot from 2023-10-31 22-11-54" src="https://github.com/Lasya-G/RISCV---AutomaticStreetLight/assets/140998582/1e81d9e3-ef82-43f3-9aa0-c727bd82b34e">












