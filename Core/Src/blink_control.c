/*
 * blink_control.c
 *
 *  Created on: Oct 2, 2024
 *      Author: apojo
 */

#include "blink_control.h"
#include "timer.h"
#include "main.h"

// Condition functions for state transitions
static int timer_expired(void *context) {
    BlinkControl *blink_control = (BlinkControl *)context;
    return timer_has_expired(&blink_control->blink_timer);
}

// on_state functions for each state
void on_state_led_off(void *context) {
    BlinkControl *blink_control = (BlinkControl *)context;
    HAL_GPIO_WritePin(blink_control->LED_Port, blink_control->LED_Pin, GPIO_PIN_SET);  // Turn LED OFF
    timer_restart(&blink_control->blink_timer);
}

void on_state_led_on(void *context) {
    BlinkControl *blink_control = (BlinkControl *)context;
    HAL_GPIO_WritePin(blink_control->LED_Port, blink_control->LED_Pin, GPIO_PIN_RESET);  // Turn LED ON
    timer_restart(&blink_control->blink_timer);
}

// Transition arrays for each state
static Transition LEDOffTransitions[] = {
    {timer_expired, LED_ON}  // Transition from OFF to ON when the timer expires
};

static Transition LEDOnTransitions[] = {
    {timer_expired, LED_OFF}  // Transition from ON to OFF when the timer expires
};

// FSM states with actions
static FSMState BlinkFSMStates[] = {
    {LEDOffTransitions, 1, on_state_led_off},           // LED_OFF state
    {LEDOnTransitions, 1, on_state_led_on}              // LED_ON state
};

// Initialize the BlinkControl FSM
void blink_control_init(BlinkControl *blink_control, GPIO_TypeDef *LED_Port, uint16_t LED_Pin, uint32_t initial_period) {
    fsm_init(&blink_control->fsm, BlinkFSMStates, LED_OFF, blink_control);  // Initialize FSM starting at LED_OFF
    blink_control->LED_Port = LED_Port;
    blink_control->LED_Pin = LED_Pin;
    timer_start(&blink_control->blink_timer, initial_period);  // Start blink timer
}

// Update the FSM
void blink_control_update(BlinkControl *blink_control) {
    fsm_update(&blink_control->fsm);
}

// Set blink period
void blink_control_set_period(BlinkControl *blink_control, uint32_t period) {
    timer_update_duration(&blink_control->blink_timer, period);
}
