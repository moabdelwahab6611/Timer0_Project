/* 
 * File     : application.c
 * Author   : Mohamed Ahmed Abdel Wahab
 * LinkedIn : https://www.linkedin.com/in/mohamed-abdel-wahab-162413253/
 * Github   : https://github.com/moabdelwahab6611
 * Created on May 21, 2023, 5:38 PM
 */

/**************************Includes-Section*****************************/
#include "application.h"
#include "MCAL_Layer/ADC/hal_adc.h"
#include "ECU_Layer/Chr_LCD/ecu_chr_lcd.h"
#include "MCAL_Layer/Timer0/hal_timer0.h"
/***********************************************************************/

/***********************************************************************/
volatile uint16 timer0_counter_value = ZERO_INT;

void Timer0_DefaultInterruptHandler(void)
{
   led_turn_toggle(&led1);
}

timer0_t timer0_timer_obj = 
{
    .TMR0_InterruptHandler = Timer0_DefaultInterruptHandler,
    .timer0_mode = TIMER0_TIMER_MODE,
    .timer0_register_size = TIMER0_16BIT_REGISTER_MODE,
    .prescaler_status_cfg = TIMER0_ENABLE_PRESCALER_CFG,
    .prescaler_value = TIMER0_PRRESCALER_DIV_BY_8,
    .timer0_preload_value = 3036
};

timer0_t timer0_counter_obj = 
{
    .TMR0_InterruptHandler = Timer0_DefaultInterruptHandler,
    .timer0_mode = TIMER0_COUNTER_MODE,
    .timer0_counter_edge = TIMER0_RISING_EDGE_CFG,
    .timer0_register_size = TIMER0_16BIT_REGISTER_MODE,
    .prescaler_status_cfg = TIMER0_DISABLE_PRESCALER_CFG,
    .timer0_preload_value = 0
};

led_t led1 = {.port_name = PORTC_INDEX, .pin = GPIO_PIN0, .led_status = GPIO_LOW};
/***********************************************************************/

/***********************Main Function-Section***************************/
int main() 
{ 
    Std_ReturnType ret = E_NOT_OK;
    application_intialize();
    //ret = Timer0_Init(&timer0_timer_obj);
    ret = Timer0_Init(&timer0_counter_obj);
    ret = led_initialize(&led1);
    while(1)
    {   
       ret = Timer0_Read_Value(&timer0_counter_obj, &timer0_counter_value); 
    }
    return (EXIT_SUCCESS);
}
/***********************************************************************/

/*************************Functions-Section*****************************/
void application_intialize(void)
{
    Std_ReturnType ret = E_NOT_OK;   
    ecu_layer_intialize();
}
/***********************************************************************/