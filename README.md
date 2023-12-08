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
riscv64-unknown-elf-gcc -march=rv32i -mabi=ilp32 -ffreestanding -nostdlib -o out automaticstreetlight_spiketest.c
riscv64-unknown-elf-objdump -d -r out > assembly.txt
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
 
<img width="800" alt="Screenshot from 2023-10-27 17-06-05" src="https://github.com/Lasya-G/RISCV---AutomaticStreetLight/assets/140998582/2fb727b9-4a4c-40bb-a596-1f2e7de8941b">   
<img width="800" alt="Screenshot from 2023-10-27 17-07-57" src="https://github.com/Lasya-G/RISCV---AutomaticStreetLight/assets/140998582/d68be628-73e2-4901-ae7f-6308d022333c">   
<img width="800" alt="Screenshot from 2023-10-27 17-11-19" src="https://github.com/Lasya-G/RISCV---AutomaticStreetLight/assets/140998582/ec3c97b9-50b5-4b98-b5d8-32457b0c38ed">    
<img width="800" alt="image" src="https://github.com/Lasya-G/RISCV---AutomaticStreetLight/assets/140998582/747d007a-7227-4ab4-8df3-0569232fd5e2">    

Here, in this image we can observe the input being 11 and the output is becoming 1 during the instruction ```00FF6F33``` which jumps to another instruction and changes the output to 1.


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

<img width="800" alt="Screenshot from 2023-10-31 21-29-52" src="https://github.com/Lasya-G/RISCV---AutomaticStreetLight/assets/140998582/7bdff079-b3c3-4112-970d-5d50fd621485">  
<img width="800" alt="Screenshot from 2023-10-31 21-42-28" src="https://github.com/Lasya-G/RISCV---AutomaticStreetLight/assets/140998582/55f666f0-e264-426d-9b25-a66c22b8f4de">
<img width="800" alt="Screenshot from 2023-10-31 21-43-10" src="https://github.com/Lasya-G/RISCV---AutomaticStreetLight/assets/140998582/2eb24564-3695-4668-bacf-2203feb12fea">
<img width="800" alt="Screenshot from 2023-10-31 21-43-59" src="https://github.com/Lasya-G/RISCV---AutomaticStreetLight/assets/140998582/70ad1b2c-f920-4c59-9312-a7ba98ca2daf">
<img width="800" alt="Screenshot from 2023-10-31 21-44-41" src="https://github.com/Lasya-G/RISCV---AutomaticStreetLight/assets/140998582/a21c47c3-38cd-4d4c-a06f-9db953e7561b">
<img width="800" alt="Screenshot from 2023-10-31 21-45-09" src="https://github.com/Lasya-G/RISCV---AutomaticStreetLight/assets/140998582/21d7cabc-01a4-450a-87d7-2bd4207ac2ab">  



- To run the GLS simulation, follow the below commands:
```
iverilog -o a.out testbench.v synth_processor_test.v sky130_sram_1kbyte_1rw1r_32x256_8.v sky130_fd_sc_hd.v primitives.v 
./a.out
gtkwave waveform.vcd
```
<img width="800" alt="Screenshot from 2023-10-31 22-29-43" src="https://github.com/Lasya-G/RISCV---AutomaticStreetLight/assets/140998582/6671ead3-2a92-4b2f-b79b-a6484c292e8c">
<img width="800" alt="Screenshot from 2023-10-31 22-11-54" src="https://github.com/Lasya-G/RISCV---AutomaticStreetLight/assets/140998582/1e81d9e3-ef82-43f3-9aa0-c727bd82b34e">


We can see that the GLS is generating the same output as that of the Functionality simulation.  


### PHYSICAL DESIGN  

### SoC Design and openLAN  

The design of ASIC requires 3 main elements:  
<img width="400" alt="image" src="https://github.com/Lasya-G/Advanced-Physical-Design-using-open-lane/assets/140998582/a1d87924-47f5-4b99-b224-63a885a06366">  

The simplified ASIC design flow is shown below:  
<img width="450" alt="image" src="https://github.com/Lasya-G/Advanced-Physical-Design-using-open-lane/assets/140998582/1ff9041d-9dfe-4a04-b814-d8c18dd0c583">  

- **Synthesis**: This converts RTL into a circuit using the components from the standard cell library. The resultant circuit is described in HDL and is usually referred as gate-level netlist, which is a functional equivalent of RTL. Each cell has a different view depending on the tool used.
<img width="450" alt="image" src="https://github.com/Lasya-G/Advanced-Physical-Design-using-open-lane/assets/140998582/76df67ee-686b-438c-bd43-10d7ed8d6cd7">

- **Floor and Power planning**: The objective is to plan the silicon area and robust power distribution network to power the circuits.
  - Chip-Floor Planning: Partition the chip die between different system building blocks and place the I/O pads.
  - Macro-Floor Planning: We define the macro dimensions and its pin locations. We also define row definitions which is used in placement process.
  - Power PLanning : It is the process of managing and distributing electrical power within an IC to ensure proper functionality, performance, and reliability while minimizing power consumption.
<img width="400" alt="image" src="https://github.com/Lasya-G/Advanced-Physical-Design-using-open-lane/assets/140998582/1ce74b69-b92e-4275-8f02-57eb9ccae251">
<img width="200" alt="image" src="https://github.com/Lasya-G/Advanced-Physical-Design-using-open-lane/assets/140998582/1438aeca-4f1f-4396-86f0-6b965a85fcbc">
<img width="200" alt="image" src="https://github.com/Lasya-G/Advanced-Physical-Design-using-open-lane/assets/140998582/770361da-3faf-4993-8bd4-ff692b42e75b">

- **Placement**: Place the cells on the floorplan rows aligned with the sites. It is usually done in 2 steps:
  - Global placement : Finds the optimal positions for all cells, which can involve cell overlapping
  - Detailed placement : Positions are minimally altered to their fixed positions.
<img width="400" alt="image" src="https://github.com/Lasya-G/Advanced-Physical-Design-using-open-lane/assets/140998582/e3977563-aae6-4fe4-a0a8-45bec22d3799">


- **Clock Tree Synthesis**: It is used to create a clock distribution network inorder to deliver clock to all sequential elements with minimum skew and minimum latency, and in a good shape. It usually looks like a tree.
<img width="400" alt="image" src="https://github.com/Lasya-G/Advanced-Physical-Design-using-open-lane/assets/140998582/56fedd15-636f-4ceb-8cca-9699a8980766">

- **Routing**: Implement the interconnect using the available metal layers. These metal layers tracks form a routing grid. As routing grid is huge, divide and conquer approach is used for routing. First, Global routing generates the routing guides and then the Detailed routing uses the guide to implement actual wiring.

- **Sign Off**: It undergoes **Physical Verification** which includes Design Rules Checking and Layout vs Schematic, and **Timing Verification** which includes Static Timing Analysis.

<img width="500" alt="image" src="https://github.com/Lasya-G/Advanced-Physical-Design-using-open-lane/assets/140998582/7b760c4f-2dd0-40c1-9533-dbb1b13737f8">  

**OpenLane**

- It started as an Open-source flow for a true Open source tape-out experiment.
- Strive is a family of open everything SoCs. <img width="400" alt="image" src="https://github.com/Lasya-G/Advanced-Physical-Design-using-open-lane/assets/140998582/6bbdf602-9033-4594-ab31-5eafb0b70018">
- The main goal of OpenLane is to produce a clean GDSII with no human intervention.
- It is tuned for Skywater 130nm Open PDK, also supports XFAB180 and GF130G.
- It has 2 modes of operation: Autonomous and Interactive.

**OpenLane ASIC Flow**:  
<img width="700" alt="image" src="https://github.com/Lasya-G/Advanced-Physical-Design-using-open-lane/assets/140998582/f02bc1db-eee4-4c52-aa64-98c0a7577b01">     

### INVOKING YOSYS and SYNTHESIS  

Go to ```ASIC/OpenLane``` and Use the below commands to invoke yosys:

```
make mount
%./flow.tcl -interactive
% package require openlane 0.9
% prep -design RISCV-ASL
```

Run the following command to synthesize the code:  
```
run_synthesis
```

<img width="750" alt="ASL_terminal_synthesis" src="https://github.com/Lasya-G/RISCV---AutomaticStreetLight/assets/140998582/707edb24-7c35-4966-9612-2c6c25d4d483">  
<img width="750" alt="ASL_synthesis_area" src="https://github.com/Lasya-G/RISCV---AutomaticStreetLight/assets/140998582/67232a74-fac1-4ea6-b5cb-045ab5715d5a">  

### FLOORPLAN  

Goal is to plan the silicon area and create a robust power distribution network (PDN) to power each of the individual components of the synthesized netlist. In addition, macro placement and blockages must be defined before placement occurs to ensure a legalized GDS file. In power planning we create the ring which is connected to the pads which brings power around the edges of the chip. We also include power straps to bring power to the middle of the chip using higher metal layers which reduces IR drop and electro-migration problem.  

Use the following command to run flopprplan:  
```
run_floorplan
```
<img width="750" alt="ASL_terminal_floorplan" src="https://github.com/Lasya-G/RISCV---AutomaticStreetLight/assets/140998582/d8c9ac67-0202-4abe-a70b-cc038f03a52f">  

To view the floorplan: Magic is invoked after moving to the results/floorplan directory,then use the floowing command:  

```
cd ASIC/OPenLane/designs/RISCV_ASL/runs/RUN_2023.11.14_16.42.43/results/floorplan
magic -T home/.volare/sky130A/libs.tech/magic/sky130A.tech lef read ../../tmp/merged.nom.lef def read wrapper.def &
```

<img width="750" alt="ASL_floorplan_magic" src="https://github.com/Lasya-G/RISCV---AutomaticStreetLight/assets/140998582/c2d6376f-bd5d-4522-a9df-1e3ee4c3eca2">    

**Areas Post FLOORPLAN**  
<img width="750" alt="ASL_floorplan_diearea" src="https://github.com/Lasya-G/RISCV---AutomaticStreetLight/assets/140998582/732e08f1-9b2c-437e-86af-3109430dd171">  
<img width="750" alt="ASL_floorplan_corearea" src="https://github.com/Lasya-G/RISCV---AutomaticStreetLight/assets/140998582/9f1697fc-b0cd-429d-a3f1-d3816b0aae24">  

### PLACEMENT  

Place the standard cells on the floorplane rows, aligned with sites defined in the technology lef file. Placement is done in two steps: Global and Detailed. In Global placement tries to find optimal position for all cells but they may be overlapping and not aligned to rows, detailed placement takes the global placement and legalizes all of the placements trying to adhere to what the global placement wants. The next step in the OpenLANE ASIC flow is placement. The synthesized netlist is to be placed on the floorplan. Placement is perfomed in 2 stages:

    Global Placement: It finds optimal position for all cells which may not be legal and cells may overlap. Optimization is done through reduction of half parameter wire length.

    Detailed Placement: It alters the position of cells post global placement so as to legalise them.

run the following command to run the placement  
```
run_placement
```

<img width="750" alt="ASL_terminal_placement" src="https://github.com/Lasya-G/RISCV---AutomaticStreetLight/assets/140998582/1008116b-5c74-463a-b9e0-d6fdbf000301">  

To view the placement: Magic is invoked after moving to the results/floorplan directory,then use the floowing command:  

```
cd ASIC/OPenLane/designs/RISCV_ASL/runs/RUN_2023.11.14_16.42.43/results/placement
magic -T home/.volare/sky130A/libs.tech/magic/sky130A.tech lef read ../../tmp/merged.nom.lef def read wrapper.def &
```

<img width="750" alt="ASL_placement_magic" src="https://github.com/Lasya-G/RISCV---AutomaticStreetLight/assets/140998582/89be7480-c25c-4838-80aa-28c00cdda378">  


### CLOCK TREE SYNTHESIS  

Clock tree synteshsis is used to create the clock distribution network that is used to deliver the clock to all sequential elements. The main goal is to create a network with minimal skew across the chip. H-trees are a common network topology that is used to achieve this goal.

The purpose of building a clock tree is enable the clock input to reach every element and to ensure a zero clock skew. H-tree is a common methodology followed in CTS.

Run the following command to perform CTS  
```
run_cts
```

<img width="750" alt="ASL_terminal_cts" src="https://github.com/Lasya-G/RISCV---AutomaticStreetLight/assets/140998582/41f9ce24-ed22-41cb-98eb-d7d0bb0f8bba">  

**Slack, Skew, Area and Power Reports**  

<img width="750" alt="ASL_cts_reports" src="https://github.com/Lasya-G/RISCV---AutomaticStreetLight/assets/140998582/998416cc-79a6-4999-b937-76c84a52c0a9">  
<img width="750" alt="ASL_cts_reports1" src="https://github.com/Lasya-G/RISCV---AutomaticStreetLight/assets/140998582/13e9197f-7fd0-4ff3-96e3-191611372ebf">  


### ROUTING  
Implements the interconnect system between standard cells using the remaining available metal layers after CTS and PDN generation. The routing is performed on routing grids to ensure minimal DRC errors.  
OpenLANE uses the TritonRoute tool for routing. There are 2 stages of routing:
- Global routing: Routing region is divided into rectangle grids which are represented as course 3D routes (Fastroute tool).
- Detailed routing: Finer grids and routing guides used to implement physical wiring (TritonRoute tool).

Features of TritonRoute:

- Honouring pre-processed route guides
- Assumes that each net satisfies inter guide connectivity
- Uses MILP based panel routing scheme
- Intra-layer parallel and inter-layer sequential routing framework

Run the following command to run the routing:  
```
run_routing
```

<img width="750" alt="image" src="https://github.com/Lasya-G/RISCV---AutomaticStreetLight/assets/140998582/11ad51ed-be71-4d93-be9a-456e57055f05">  

To view the routing, Magic is invoked after moving to the results/floorplan directory,then use the floowing command:  

```
cd ASIC/OPenLane/designs/RISCV_ASL/runs/RUN_2023.11.14_16.42.43/results/routing
magic -T home/.volare/sky130A/libs.tech/magic/sky130A.tech lef read ../../tmp/merged.nom.lef def read wrapper.def &
```

<img width="750" alt="ASL_routing_magic" src="https://github.com/Lasya-G/RISCV---AutomaticStreetLight/assets/140998582/3055a07f-786a-4ba6-9f45-f8b8a619f03d">  
<img width="750" alt="ASL_routing_magic1" src="https://github.com/Lasya-G/RISCV---AutomaticStreetLight/assets/140998582/c399f2cf-a870-4df4-ac82-9e83fa7b2ba6">  
<img width="750" alt="ASL_routing_area" src="https://github.com/Lasya-G/RISCV---AutomaticStreetLight/assets/140998582/30f45e29-f8f5-48b4-802e-19a76240bdcb">  



**POST_ROUTING REPORTS**:

<img width="750" alt="image" src="https://github.com/Lasya-G/RISCV---AutomaticStreetLight/assets/140998582/aaee6a43-6cda-4311-bcc2-338a89c741ab">  
<img width="750" alt="image" src="https://github.com/Lasya-G/RISCV---AutomaticStreetLight/assets/140998582/99e13fa9-37a2-4659-99a8-ea5224bf1ed9">  



**No Violation Report**:  

<img width="750" alt="image" src="https://github.com/Lasya-G/RISCV---AutomaticStreetLight/assets/140998582/0b71fbd5-7674-4291-bf38-3f40f25a3544">  


### Performance Calculation:

Given a Clock period of 90ns in Json file , setup slack we got after routing is 25.01ns  
```
                              1
Max Performance =  ------------------------
                     clock period - slack(setup)

```

Max Performance = 0.0154 Ghz  

### EXTRAS  

<img width="800" alt="image" src="https://github.com/Lasya-G/RISCV---AutomaticStreetLight/assets/140998582/1eb557a5-91d5-4a38-ad27-bec7358cc79c">  




### OpenLane Interactive Flow:  

```  
cd ASIC/OpenLane/
make mount

./flow.tcl -interactive
package require openlane 0.9
prep -design RISCV_ASL
run_synthesis
run_floorplan
run_placement
run_cts
gen_pdn
run_routing
run_magic
run_magic_spice_export
run_magic_drc
run_antenna_check

```

### OpenLane Non-Interactive Flow:  

```
cd ASIC/OpenLane 
make mount
./flow.tcl -design RISCV_ASL
```




### References  

1. https://github.com/SakethGajawada/RISCV-GNU
2. https://github.com/alwinshaju08/IIITB_Waterlevel_detector
   












  








