#ifndef MQ7_H
#define MQ7_H

#include <stdint.h>

 /**
 * @def UINT8_T_CONSTANT1(num)
 * @brief Macro para converter um número em um valor do tipo uint8_t.
 *
 * Essa macro garante que o número passado seja tratado como um `uint8_t`,
 * evitando problemas de tipo em operações bit a bit e comparação de constantes.
 *
 * @param num O número a ser convertido.
 */
#define UINT8_T_CONSTANT(num) ((uint8_t) (num))

/**
 * @def ADC_GPIO_26
 * @brief Define o GPIO 26 como uma entrada ADC válida.
 */
#define ADC_GPIO_26 UINT8_T_CONSTANT(26)

/**
 * @def ADC_GPIO_27
 * @brief Define o GPIO 27 como uma entrada ADC válida.
 */
#define ADC_GPIO_27 UINT8_T_CONSTANT(27)

/**
 * @def ADC_GPIO_28
 * @brief Define o GPIO 28 como uma entrada ADC válida.
 */
#define ADC_GPIO_28 UINT8_T_CONSTANT(28)

/**
 * @def ADC_GPIO_29
 * @brief Define o GPIO 29 como uma entrada ADC válida.
 */
#define ADC_GPIO_29 UINT8_T_CONSTANT(29)

/**
 * @def ADC_CHANNEL_1
 * @brief Define o canal ADC 1 correspondente a um GPIO configurado como entrada analógica.
 */
#define ADC_CHANNEL_1 UINT8_T_CONSTANT(0)

/**
 * @def ADC_CHANNEL_2
 * @brief Define o canal ADC 2 correspondente a um GPIO configurado como entrada analógica.
 */
#define ADC_CHANNEL_2 UINT8_T_CONSTANT(1)

/**
 * @def ADC_CHANNEL_3
 * @brief Define o canal ADC 3 correspondente a um GPIO configurado como entrada analógica.
 */
#define ADC_CHANNEL_3 UINT8_T_CONSTANT(2)

/**
 * @def ADC_CHANNEL_4
 * @brief Define o canal ADC 4 correspondente a um GPIO configurado como entrada analógica.
 */
#define ADC_CHANNEL_4 UINT8_T_CONSTANT(3)

#define VREF 3.3        // Tensão de referência do ADC
#define ADC_MAX 4095    // Máximo valor ADC (12 bits)

void mq7_init(uint8_t mq7_pin);
void mq7_start_heating();
uint16_t mq7_get_ppm(uint8_t mq7_ad_channel);

#endif //MQ7_H