/*
 * modulo_semaforo.c
 *
 *  Created on: Oct 24, 2024
 */

#include "modulo_semaforo.h"

/**
 * @brief Condición para pasar del estado 1 al estado 2.
 */
static int condicion_estado1_a_estado2(void *context) {
  ModuloSemaforo *semaforo = (ModuloSemaforo*)context;
  return HAL_GPIO_ReadPin(semaforo->Switch_Debouncer.GPIOx, semaforo->Switch_Debouncer.GPIO_Pin) == GPIO_PIN_SET;
}

/**
 * @brief Condición para pasar del estado 2 al estado 3.
 */
static int condicion_estado2_a_estado3(void *context) {
  ModuloSemaforo *semaforo = (ModuloSemaforo*)context;
  return timer_has_expired(&semaforo->timer);
}

/**
 * @brief Condición para pasar del estado 3 al estado 4.
 */
static int condicion_estado3_a_estado4(void *context) {
  ModuloSemaforo *semaforo = (ModuloSemaforo*)context;
  return timer_has_expired(&semaforo->timer);
}

/**
 * @brief Condición para pasar del estado 4 al estado 1.
 */
static int condicion_estado4_a_estado1(void *context) {
  ModuloSemaforo *semaforo = (ModuloSemaforo*)context;
  return timer_has_expired(&semaforo->timer);
}


/**
 * @brief Estado 1: Encender LED verde.
 */
void on_state_estado1(void *context) {
  ModuloSemaforo *semaforo = (ModuloSemaforo*)context;

  // Encender el LED verde y apagar el rojo
  HAL_GPIO_WritePin(semaforo->LED_Verde_Blink.LED_Port, semaforo->LED_Verde_Blink.LED_Pin, GPIO_PIN_RESET);
  HAL_GPIO_WritePin(semaforo->LED_Rojo_Blink.LED_Port, semaforo->LED_Rojo_Blink.LED_Pin, GPIO_PIN_SET);
}

/**
 * @brief Estado 2: Blink LED verde.
 */
void on_state_estado2(void *context) {
  ModuloSemaforo *semaforo = (ModuloSemaforo*)context;

  //Apagar el LED rojo mientras el verde parpadea
    HAL_GPIO_WritePin(semaforo->LED_Rojo_Blink.LED_Port, semaforo->LED_Rojo_Blink.LED_Pin, GPIO_PIN_SET); // Apagar el rojo

  // Iniciar al timer con una duración de 1s
  timer_start(&semaforo->timer, 1000);
}

/**
 * @brief Estado 3: Encender LED rojo.
 */
void on_state_estado3(void *context) {
  ModuloSemaforo *semaforo = (ModuloSemaforo*)context;

  // Apagar el LED verde y encender el rojo
  HAL_GPIO_WritePin(semaforo->LED_Verde_Blink.LED_Port, semaforo->LED_Verde_Blink.LED_Pin, GPIO_PIN_SET);
  HAL_GPIO_WritePin(semaforo->LED_Rojo_Blink.LED_Port, semaforo->LED_Rojo_Blink.LED_Pin, GPIO_PIN_RESET);

  // Iniciar al timer con una duración de 3s
  timer_start(&semaforo->timer, 3000);
}

/**
 * @brief Estado 4: Blink LED rojo.
 */
void on_state_estado4(void *context) {
  ModuloSemaforo *semaforo = (ModuloSemaforo*)context;

  // Apagar el LED verde mientras el rojo parpadea
    HAL_GPIO_WritePin(semaforo->LED_Verde_Blink.LED_Port, semaforo->LED_Verde_Blink.LED_Pin, GPIO_PIN_SET); // Apagar el verde

  // Iniciar al timer con una duración de 1s
  timer_start(&semaforo->timer, 1000);
}



// Transiciones desde ESTADO_1
static Transition Estado1Transitions[] =
{
    {condicion_estado1_a_estado2, ESTADO_2}, // Transición al estado 2
};

// Transiciones desde ESTADO_2
static Transition Estado2Transitions[] =
{
    {condicion_estado2_a_estado3, ESTADO_3}, // Transición al estado 3
};

// Transiciones desde ESTADO_3
static Transition Estado3Transitions[] =
{
    {condicion_estado3_a_estado4, ESTADO_4} // Transición al estado 4
};

// Transiciones desde ESTADO_4
static Transition Estado4Transitions[] =
{
    {condicion_estado4_a_estado1, ESTADO_1} // Transición al estado 1
};

static FSMState ModuloSemaforoEstados[] =
{
    {Estado1Transitions, 1, on_state_estado1}, // Estado 1: tiene 1 transición y ejecuta una acción
    {Estado2Transitions, 1, on_state_estado2}, // Estado 2: tiene 1 transición y ejecuta una acción
    {Estado3Transitions, 1, on_state_estado3}, // Estado 3: tiene 1 transición y ejecuta una acción
    {Estado4Transitions, 1, on_state_estado4}, // Estado 4: tiene 1 transición y ejecuta una acción
};

/**
 * @brief Inicializa el módulo.
 */
void modulo_semaforo_init(ModuloSemaforo *semaforo, GPIO_TypeDef *Luz_Verde_Port,
    uint16_t Luz_Verde_Pin, GPIO_TypeDef *Luz_Roja_Port, uint16_t Luz_Roja_Pin,
    GPIO_TypeDef *SW_Port, uint16_t SW_Pin) {

  blink_control_init(&semaforo->LED_Verde_Blink, Luz_Verde_Port, Luz_Verde_Pin, 200);//Frecuencia de parpadeo led verde
  blink_control_init(&semaforo->LED_Rojo_Blink, Luz_Roja_Port, Luz_Roja_Pin, 200);//Frecuencia de parpadeo led rojo
  debounced_switch_init(&semaforo->Switch_Debouncer, SW_Port, SW_Pin);
  edge_detector_init(&semaforo->Switch_EdgeDetector, &semaforo->Switch_Debouncer);

  fsm_init(&semaforo->fsm, ModuloSemaforoEstados, ESTADO_1, semaforo);

  // Encender el LED verde y apagar el rojo
  HAL_GPIO_WritePin(semaforo->LED_Verde_Blink.LED_Port, semaforo->LED_Verde_Blink.LED_Pin, GPIO_PIN_RESET);
  HAL_GPIO_WritePin(semaforo->LED_Rojo_Blink.LED_Port, semaforo->LED_Rojo_Blink.LED_Pin, GPIO_PIN_SET);
}

/**
 * @brief Actualiza el módulo.
 */
void modulo_semaforo_update(ModuloSemaforo *semaforo) {
  fsm_update(&semaforo->fsm);  // Llamar a fsm_update para gestionar las transiciones

  // Realizar el blink update en los estados 2 y 4
  if (semaforo->fsm.currentState == ESTADO_2) {
	  // Asegúrate de que el LED rojo esté apagado mientras el verde parpadea
	  HAL_GPIO_WritePin(semaforo->LED_Rojo_Blink.LED_Port, semaforo->LED_Rojo_Blink.LED_Pin, GPIO_PIN_SET);
    blink_control_update(&semaforo->LED_Verde_Blink);
  }

  if (semaforo->fsm.currentState == ESTADO_4) {
	  // Asegúrate de que el LED verde esté apagado mientras el rojo parpadea
	   HAL_GPIO_WritePin(semaforo->LED_Verde_Blink.LED_Port, semaforo->LED_Verde_Blink.LED_Pin, GPIO_PIN_SET);
    blink_control_update(&semaforo->LED_Rojo_Blink);
  }
}

