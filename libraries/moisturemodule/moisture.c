/*
 * Copyright 2019, Cypress Semiconductor Corporation or a subsidiary of
 * Cypress Semiconductor Corporation. All Rights Reserved.
 *
 * This software, including source code, documentation and related
 * materials ("Software"), is owned by Cypress Semiconductor Corporation
 * or one of its subsidiaries ("Cypress") and is protected by and subject to
 * worldwide patent protection (United States and foreign),
 * United States copyright laws and international treaty provisions.
 * Therefore, you may use this Software only as provided in the license
 * agreement accompanying the software package from which you
 * obtained this Software ("EULA").
 * If no EULA applies, Cypress hereby grants you a personal, non-exclusive,
 * non-transferable license to copy, modify, and compile the Software
 * source code solely for use in connection with Cypress's
 * integrated circuit products. Any reproduction, modification, translation,
 * compilation, or representation of this Software except as specified
 * above is prohibited without the express written permission of Cypress.
 *
 * Disclaimer: THIS SOFTWARE IS PROVIDED AS-IS, WITH NO WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING, BUT NOT LIMITED TO, NONINFRINGEMENT, IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE. Cypress
 * reserves the right to make changes to the Software without notice. Cypress
 * does not assume any liability arising out of the application or use of the
 * Software or any product or circuit described in the Software. Cypress does
 * not authorize its products for use in any products where a malfunction or
 * failure of the Cypress product may reasonably be expected to result in
 * significant property damage, injury or death ("High Risk Product"). By
 * including Cypress's product in a High Risk Product, the manufacturer
 * of such system or application assumes all risk of such use and in doing
 * so agrees to indemnify Cypress against all liability.
 */
#include "wiced_bt_trace.h"
#include "wiced_hal_gpio.h"
#include "wiced_moisture.h"
#include "wiced_platform.h"
#include "wiced_hal_adc.h"

// choose which ref resistance you use
#define THERM_10K

typedef struct 
{
    uint16_t                high_pin;           /*  A/D input high pin    */
    uint16_t                low_pin;            /*  A/D input low pin     */
    uint16_t                adc_power_pin;      /*  ADC power pin         */
} moisture_cfg_t;

moisture_cfg_t moisture_cfg =
{
    .high_pin       = ADC_INPUT_P14,
    .low_pin        = ADC_INPUT_P13,
    .adc_power_pin  = WICED_P09,
};

/**********************************************************************************************************
Variables Definitions
**********************************************************************************************************/

/**********************************************************************************************************
Function Declarations
**********************************************************************************************************/

/******************************************************************************
* Function Name: moisture_init
***************************************************************************//**
* init moisture.
*
* \param None.
*
* \return None
******************************************************************************/
void moisture_init(void)
{
    wiced_hal_adc_init();
}

/******************************************************************************
* Function Name: moisture_read
***************************************************************************//**
* The function reads the moisture temperature.
*
* Return temperature in degrees Celsius * 100
*
******************************************************************************/
long int moisture_read(void)
{
    long int  voltage_val_low = 0, voltage_val_high = 0, therm_cal_value = 0;


    // open ADC

    voltage_val_low  = wiced_hal_adc_read_voltage(moisture_cfg.low_pin);

    WICED_BT_TRACE("moisture_read high:%d low:%d cal:%d\n", voltage_val_high, voltage_val_low, therm_cal_value);

    return voltage_val_low/10;

}
