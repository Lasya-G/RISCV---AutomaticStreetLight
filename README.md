![Screenshot from 2023-10-05 09-32-06](https://github.com/Lasya-G/RISCV---AutomaticStreetLight/assets/140998582/8e466730-2be4-4e99-ab77-13d292882376)## AutomaticStreetLight

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



### Assembly code
