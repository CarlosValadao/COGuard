#include "mq7.h"
#include "hardware/adc.h"

/**
 * @brief Converte um número de GPIO para o número do canal ADC correspondente.
 *
 * Esta função recebe um número de GPIO e retorna o número do canal ADC associado.
 * Os GPIOs válidos para ADC são 26, 27, 28 e 29, correspondentes aos canais 0, 1, 2 e 3, respectivamente.
 *
 * @note Apenas os GPIOs 26 a 29 são suportados, pois são os únicos pinos com entrada ADC no RP2040.
 * @warning Se um GPIO inválido for passado, a função pode retornar um valor indefinido.
 *
 * @param[in] gpio O número do pino GPIO a ser convertido.
 * @return O número do canal ADC correspondente, ou comportamento indefinido para valores inválidos.
 */
static uint8_t adc_gpio_to_channel_num(uint8_t gpio) {
    switch (gpio)
    {
        case ADC_GPIO_26: return ADC_CHANNEL_1;
        case ADC_GPIO_27: return ADC_CHANNEL_2;
        case ADC_GPIO_28: return ADC_CHANNEL_3;
        case ADC_GPIO_29: return ADC_CHANNEL_4;
    }
}

static uint16_t adc_read_filtered(uint8_t channel, uint8_t deadzone)
{
    adc_select_input(channel);
    uint16_t raw_value = adc_read(); // Leitura do ADC
    uint16_t center = 2048; // Centro do joystick em um ADC de 12 bits
    // Se estiver dentro da deadzone, retorna o centro para evitar ruído
    if (raw_value > (center - deadzone) && raw_value < (center + deadzone))
    {
        return center;
    }
    return raw_value;
}

void mq7_init(uint8_t mq7_pin)
{
    adc_init();
    adc_gpio_init(mq7_pin);
}

void mq7_start_heating()
{
    return;
}

uint16_t mq7_get_ppm(uint8_t mq7_ad_channel)
{
    uint16_t adc_value = adc_read_filtered(mq7_ad_channel, (uint8_t) 120);
    if (adc_value == 2048) return 0;
    else return ((adc_value*1000)/4095);
}