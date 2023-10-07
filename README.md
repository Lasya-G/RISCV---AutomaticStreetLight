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
void read();
void controller

int read_pir_sensor() {
int pir_value;
asm (
            "ori %0, x30, 1\n\t"
            :"=r"(pir_value)
        );
    // Implement logic to read PIR sensor and return its value.
}

int read_ldr_sensor() {
int ldr_value;
asm (
            "ori %0, x30, 1\n\t"
            : "=r"(ldr_value)
        );
    // Implement logic to read LDR sensor and return its value.
}

void controller() {
int pir_value;
int ldr_value;
int* control_light;
int* control;
    if (pir_value && ldr_value) { 
        // PIR sensor gives 1 when motion is detected, and LDR sensor outputs 1 when there is no light intensity
        *control = 1;
        *control_light = *control * 32;
        asm(
		"and x30, x30, %0 \n\t"
		:"=r"(control_light));
    }
    else { 
        *control = 0;
        *control_light = *control * 32;
        asm(
		"and x30, x30, %0 \n\t"
		:"=r"(control_light));
    }
}

void read() {
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
automaticstreetlight.o:     file format elf32-littleriscv


Disassembly of section .text:

00000000 <read_pir_sensor>:
   0:	fe010113          	add	sp,sp,-32
   4:	00812e23          	sw	s0,28(sp)
   8:	02010413          	add	s0,sp,32
   c:	001f6793          	or	a5,t5,1
  10:	fef42623          	sw	a5,-20(s0)
  14:	00000013          	nop
  18:	00078513          	mv	a0,a5
  1c:	01c12403          	lw	s0,28(sp)
  20:	02010113          	add	sp,sp,32
  24:	00008067          	ret

00000028 <read_ldr_sensor>:
  28:	fe010113          	add	sp,sp,-32
  2c:	00812e23          	sw	s0,28(sp)
  30:	02010413          	add	s0,sp,32
  34:	001f6793          	or	a5,t5,1
  38:	fef42623          	sw	a5,-20(s0)
  3c:	00000013          	nop
  40:	00078513          	mv	a0,a5
  44:	01c12403          	lw	s0,28(sp)
  48:	02010113          	add	sp,sp,32
  4c:	00008067          	ret

00000050 <controller>:
  50:	fe010113          	add	sp,sp,-32
  54:	00812e23          	sw	s0,28(sp)
  58:	02010413          	add	s0,sp,32
  5c:	fec42783          	lw	a5,-20(s0)
  60:	02078c63          	beqz	a5,98 <.L4>
  64:	fe842783          	lw	a5,-24(s0)
  68:	02078863          	beqz	a5,98 <.L4>
  6c:	fe442783          	lw	a5,-28(s0)
  70:	00100713          	li	a4,1
  74:	00e7a023          	sw	a4,0(a5)
  78:	fe442783          	lw	a5,-28(s0)
  7c:	0007a783          	lw	a5,0(a5)
  80:	00579713          	sll	a4,a5,0x5
  84:	fe042783          	lw	a5,-32(s0)
  88:	00e7a023          	sw	a4,0(a5)
  8c:	00ff7f33          	and	t5,t5,a5
  90:	fef42023          	sw	a5,-32(s0)
  94:	02c0006f          	j	c0 <.L5>

00000098 <.L4>:
  98:	fe442783          	lw	a5,-28(s0)
  9c:	0007a023          	sw	zero,0(a5)
  a0:	fe442783          	lw	a5,-28(s0)
  a4:	0007a783          	lw	a5,0(a5)
  a8:	00579713          	sll	a4,a5,0x5
  ac:	fe042783          	lw	a5,-32(s0)
  b0:	00e7a023          	sw	a4,0(a5)
  b4:	00ff7f33          	and	t5,t5,a5
  b8:	fef42023          	sw	a5,-32(s0)
  bc:	00000013          	nop

000000c0 <.L5>:
  c0:	00000013          	nop
  c4:	01c12403          	lw	s0,28(sp)
  c8:	02010113          	add	sp,sp,32
  cc:	00008067          	ret

000000d0 <read>:
  d0:	ff010113          	add	sp,sp,-16
  d4:	00112623          	sw	ra,12(sp)
  d8:	00812423          	sw	s0,8(sp)
  dc:	01010413          	add	s0,sp,16
  e0:	00000097          	auipc	ra,0x0
  e4:	000080e7          	jalr	ra # e0 <read+0x10>
  e8:	00000013          	nop
  ec:	00c12083          	lw	ra,12(sp)
  f0:	00812403          	lw	s0,8(sp)
  f4:	01010113          	add	sp,sp,16
  f8:	00008067          	ret

000000fc <main>:
  fc:	ff010113          	add	sp,sp,-16
 100:	00112623          	sw	ra,12(sp)
 104:	00812423          	sw	s0,8(sp)
 108:	01010413          	add	s0,sp,16

0000010c <.L8>:
 10c:	00000097          	auipc	ra,0x0
 110:	000080e7          	jalr	ra # 10c <.L8>
 114:	ff9ff06f          	j	10c <.L8>

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


