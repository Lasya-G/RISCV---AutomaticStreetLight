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

int main() {
    while(1) {
        read();
    }
    return 0;
}

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


```




### Assembly code  

```

out:     file format elf32-littleriscv


Disassembly of section .text:

00010074 <main>:
   10074:	ff010113          	add	sp,sp,-16
   10078:	00112623          	sw	ra,12(sp)
   1007c:	00812423          	sw	s0,8(sp)
   10080:	01010413          	add	s0,sp,16
   10084:	0c0000ef          	jal	10144 <read>
   10088:	ffdff06f          	j	10084 <main+0x10>

0001008c <read_pir_sensor>:
   1008c:	fe010113          	add	sp,sp,-32
   10090:	00812e23          	sw	s0,28(sp)
   10094:	02010413          	add	s0,sp,32
   10098:	001f6793          	or	a5,t5,1
   1009c:	fef42623          	sw	a5,-20(s0)
   100a0:	00000013          	nop
   100a4:	00078513          	mv	a0,a5
   100a8:	01c12403          	lw	s0,28(sp)
   100ac:	02010113          	add	sp,sp,32
   100b0:	00008067          	ret

000100b4 <read_ldr_sensor>:
   100b4:	fe010113          	add	sp,sp,-32
   100b8:	00812e23          	sw	s0,28(sp)
   100bc:	02010413          	add	s0,sp,32
   100c0:	001f6793          	or	a5,t5,1
   100c4:	fef42623          	sw	a5,-20(s0)
   100c8:	00000013          	nop
   100cc:	00078513          	mv	a0,a5
   100d0:	01c12403          	lw	s0,28(sp)
   100d4:	02010113          	add	sp,sp,32
   100d8:	00008067          	ret

000100dc <controller>:
   100dc:	fe010113          	add	sp,sp,-32
   100e0:	00812e23          	sw	s0,28(sp)
   100e4:	02010413          	add	s0,sp,32
   100e8:	fec42783          	lw	a5,-20(s0)
   100ec:	02078663          	beqz	a5,10118 <controller+0x3c>
   100f0:	fe842783          	lw	a5,-24(s0)
   100f4:	02078263          	beqz	a5,10118 <controller+0x3c>
   100f8:	00100793          	li	a5,1
   100fc:	fef42223          	sw	a5,-28(s0)
   10100:	fe442783          	lw	a5,-28(s0)
   10104:	00579793          	sll	a5,a5,0x5
   10108:	fef42023          	sw	a5,-32(s0)
   1010c:	fe042783          	lw	a5,-32(s0)
   10110:	00ff7f33          	and	t5,t5,a5
   10114:	0200006f          	j	10134 <controller+0x58>
   10118:	fe042223          	sw	zero,-28(s0)
   1011c:	fe442783          	lw	a5,-28(s0)
   10120:	00579793          	sll	a5,a5,0x5
   10124:	fef42023          	sw	a5,-32(s0)
   10128:	fe042783          	lw	a5,-32(s0)
   1012c:	00ff7f33          	and	t5,t5,a5
   10130:	00000013          	nop
   10134:	00000013          	nop
   10138:	01c12403          	lw	s0,28(sp)
   1013c:	02010113          	add	sp,sp,32
   10140:	00008067          	ret

00010144 <read>:
   10144:	ff010113          	add	sp,sp,-16
   10148:	00112623          	sw	ra,12(sp)
   1014c:	00812423          	sw	s0,8(sp)
   10150:	01010413          	add	s0,sp,16
   10154:	f89ff0ef          	jal	100dc <controller>
   10158:	00000013          	nop
   1015c:	00c12083          	lw	ra,12(sp)
   10160:	00812403          	lw	s0,8(sp)
   10164:	01010113          	add	sp,sp,16
   10168:	00008067          	ret

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


