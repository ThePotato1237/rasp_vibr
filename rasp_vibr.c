#include <stdio.h>
#include "pico/stdlib.h"
#include "pico/time.h"
#include "hardware/gpio.h"
#include "hardware/adc.h"
#include "pico/multicore.h"
#include "pico/cyw43_arch.h"
#include "pico/btstack_cyw43.h"


#define tomb_meret 50


volatile uint16_t tomb_A[tomb_meret];
volatile uint16_t tomb_B[tomb_meret];

volatile uint16_t* akt_tomb = tomb_A;
volatile uint8_t szamlalo = 0;

//adc beállítása
void adc_inditas() {
    adc_init();
    adc_gpio_init(26); 
    adc_select_input(0); 
}



bool adc_olvasas(struct repeating_timer *t) {
    uint16_t result = adc_read();

    akt_tomb[szamlalo] = result;
    szamlalo++;

     if(szamlalo >= tomb_meret) {
        szamlalo = 0;

        multicore_fifo_push_blocking((uint16_t)akt_tomb);

        if(akt_tomb == tomb_A) {
            akt_tomb = tomb_B;
        } else {
            akt_tomb = tomb_A;
        }


    }

    return true; 
}

void Core1_entry() {



}





int main()
{



    while (true) {
        
       
            
           
            stdio_init_all();
            adc_inditas();
            ble_init();

            sleep_ms(1000);

           


           
                multicore_launch_core1(Core1_entry);

                struct repeating_timer timer;
                add_repeating_timer_us(-200, adc_olvasas, NULL,&timer );

           
    

        


        sleep_ms(1000);
    }
}
