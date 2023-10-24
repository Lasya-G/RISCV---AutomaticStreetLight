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


