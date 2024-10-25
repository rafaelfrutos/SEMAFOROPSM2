/*
 * modulo_semaforo.h
 *
 *  Created on: Oct 12, 2024
 *      Author: youno
 */

#ifndef INC_MODULO_SEMAFORO_H_
#define INC_MODULO_SEMAFORO_H_

#include "main.h"
#include "fsm.h"
#include "timer.h"
#include "blink_control.h"
#include "debouncer.h"
#include "edge_detector.h"

typedef enum {
    ESTADO_1,
    ESTADO_2,
    ESTADO_3,
    ESTADO_4
} ModuloSemaforoEstado;

typedef struct {
    FSM fsm;                          // Instancia de la FSM (detalle de implementación)
    BlinkControl LED_Verde_Blink;
    BlinkControl LED_Rojo_Blink;
    DebouncedSwitch Switch_Debouncer;
    EdgeDetector Switch_EdgeDetector;
    Timer timer;
} ModuloSemaforo;

/**
 * @brief Inicializa el módulo.
 *
 * @param semaforo Puntero a la estructura del módulo.
 * @param Luz_Verde_Port Puerto GPIO del LED verde.
 * @param Luz_Verde_Port Pin GPIO del LED verde.
 * @param Luz_Roja_Port Puerto GPIO del LED rojo.
 * @param LUZ_Roja_Pin Pin GPIO del LED rojo.
 * @param SW_Port Puerto del switch.
 * @param SW_Pin Pin del switch.
 */
void modulo_semaforo_init(ModuloSemaforo *semaforo, GPIO_TypeDef *Luz_Verde_Port, uint16_t Luz_Verde_Pin,
      GPIO_TypeDef *Luz_Roja_Port, uint16_t Luz_Roja_Pin, GPIO_TypeDef *SW_Port, uint16_t SW_Pin);

/**
 * @brief Actualiza el módulo.
 *
 * @param semaforo Puntero a la estructura del módulo.
 */
void modulo_semaforo_update(ModuloSemaforo *semaforo);


#endif /* INC_MODULO_SEMAFORO_H_ */
