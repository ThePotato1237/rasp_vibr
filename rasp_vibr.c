#include <stdio.h>
#include "pico/stdlib.h"
#include "pico/time.h"
#include "hardware/gpio.h"
#include "hardware/adc.h"

void adc_inditas() {
    adc_init();
    adc_gpio_init(26); // Initialize GPIO 26 for ADC input
    adc_select_input(0); // Select ADC input channel 0
}



bool adc_olvasas(struct_repeating_timer *t) {
    
    return true; 
}





int main()
{




sleep_ms(1000);

    stdio_init_all();



    while (true) {
        
        sleep_ms(1000);
    }
}
