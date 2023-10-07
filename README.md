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
//#include<stdio.h>

void read();
void controller();

int read_pir_sensor() {
int pir_value;
asm volatile(
            "or %0, x30, 1\n\t"
            :"=r"(pir_value)
        );
    // Implement logic to read PIR sensor and return its value.
}

int read_ldr_sensor() {
int ldr_value;
asm volatile(
            "or %0, x30, 1\n\t"
            : "=r"(ldr_value)
        );
    // Implement logic to read LDR sensor and return its value.
}

void controller() {
int pir_value;
int ldr_value;
int control_light;
int control;
    if (pir_value && ldr_value) { 
        // PIR sensor gives 1 when motion is detected, and LDR sensor outputs 1 when there is no light intensity
        control = 1;
        control_light = control * 32;
        asm volatile(
		"and x30, x30, %0 \n\t"
		:
		:"r"(control_light)
		:"x30"
		);
    }
    else { 
        control = 0;
        control_light = control * 32;
        asm volatile(
		"and x30, x30, %0 \n\t"
		:
		:"r"(control_light)
		:"x30"
		);
    }
}

void read() {
 //   int pir_value = read_pir_sensor(); // Implement this function to read PIR sensor.
   // int ldr_value = read_ldr_sensor(); // Implement this function to read LDR sensor.
   // int control_ip;
    controller();
}

int main() {
    while(1) {
        read();
    }
    return 0;
}
```



Use below code to convert c code to assembly language:
```
/home/lasya/riscv32-toolchain/bin/riscv32-unknown-elf-gcc -c -mabi=ilp32 -march=rv32im -ffreestanding -o automaticstreetlight.o automaticstreetlight.c
/home/lasya/riscv32-toolchain/bin/riscv32-unknown-elf-objdump -d automaticstreetlight.o > automaticstreetlight.txt
```

### Assembly code  

```

out:     file format elf32-littleriscv


Disassembly of section .text:

00010074 <read_pir_sensor>:
   10074:	fe010113          	add	sp,sp,-32
   10078:	00812e23          	sw	s0,28(sp)
   1007c:	02010413          	add	s0,sp,32
   10080:	001f6793          	or	a5,t5,1
   10084:	fef42623          	sw	a5,-20(s0)
   10088:	00000013          	nop
   1008c:	00078513          	mv	a0,a5
   10090:	01c12403          	lw	s0,28(sp)
   10094:	02010113          	add	sp,sp,32
   10098:	00008067          	ret

0001009c <read_ldr_sensor>:
   1009c:	fe010113          	add	sp,sp,-32
   100a0:	00812e23          	sw	s0,28(sp)
   100a4:	02010413          	add	s0,sp,32
   100a8:	001f6793          	or	a5,t5,1
   100ac:	fef42623          	sw	a5,-20(s0)
   100b0:	00000013          	nop
   100b4:	00078513          	mv	a0,a5
   100b8:	01c12403          	lw	s0,28(sp)
   100bc:	02010113          	add	sp,sp,32
   100c0:	00008067          	ret

000100c4 <controller>:
   100c4:	fe010113          	add	sp,sp,-32
   100c8:	00812e23          	sw	s0,28(sp)
   100cc:	02010413          	add	s0,sp,32
   100d0:	fec42783          	lw	a5,-20(s0)
   100d4:	02078663          	beqz	a5,10100 <controller+0x3c>
   100d8:	fe842783          	lw	a5,-24(s0)
   100dc:	02078263          	beqz	a5,10100 <controller+0x3c>
   100e0:	00100793          	li	a5,1
   100e4:	fef42223          	sw	a5,-28(s0)
   100e8:	fe442783          	lw	a5,-28(s0)
   100ec:	00579793          	sll	a5,a5,0x5
   100f0:	fef42023          	sw	a5,-32(s0)
   100f4:	fe042783          	lw	a5,-32(s0)
   100f8:	00ff7f33          	and	t5,t5,a5
   100fc:	0200006f          	j	1011c <controller+0x58>
   10100:	fe042223          	sw	zero,-28(s0)
   10104:	fe442783          	lw	a5,-28(s0)
   10108:	00579793          	sll	a5,a5,0x5
   1010c:	fef42023          	sw	a5,-32(s0)
   10110:	fe042783          	lw	a5,-32(s0)
   10114:	00ff7f33          	and	t5,t5,a5
   10118:	00000013          	nop
   1011c:	00000013          	nop
   10120:	01c12403          	lw	s0,28(sp)
   10124:	02010113          	add	sp,sp,32
   10128:	00008067          	ret

0001012c <read>:
   1012c:	ff010113          	add	sp,sp,-16
   10130:	00112623          	sw	ra,12(sp)
   10134:	00812423          	sw	s0,8(sp)
   10138:	01010413          	add	s0,sp,16
   1013c:	f89ff0ef          	jal	100c4 <controller>
   10140:	00000013          	nop
   10144:	00c12083          	lw	ra,12(sp)
   10148:	00812403          	lw	s0,8(sp)
   1014c:	01010113          	add	sp,sp,16
   10150:	00008067          	ret

00010154 <main>:
   10154:	ff010113          	add	sp,sp,-16
   10158:	00112623          	sw	ra,12(sp)
   1015c:	00812423          	sw	s0,8(sp)
   10160:	01010413          	add	s0,sp,16
   10164:	fc9ff0ef          	jal	1012c <read>
   10168:	ffdff06f          	j	10164 <main+0x10>

```


### Unique Instructions
To find the number of unique instructions make sure to rename the filename as sample_assembly.txt since the python script that we are using is opening the file name with sample_assembly.txt and both files should be in the same directory. The python script I am using is already uploaded. Now follow the command to get the number of different instructions used.
```
$ python3 instruction_counter.py // use this command after ensuring we are in the same directory as the script
```
Number of different instructions: 13  
List of unique instructions:  
add  
beqz  
lw  
and  
or  
ret  
jal  
li  
sll  
mv  
j  
nop  
sw  


