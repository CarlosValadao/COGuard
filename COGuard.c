// Inclusão das bibliotecas necessárias para o funcionamento do projeto
#include "pico/stdlib.h"        // Biblioteca padrão da Raspberry Pi Pico
#include "pico/bootrom.h"       // Biblioteca para acesso ao modo BOOTSEL
#include "lib/ssd1306_utils.h"  // Biblioteca para controle do display OLED SSD1306
#include "lib/mlt8530.h"        // Biblioteca para controle do buzzer
#include "lib/rgb.h"            // Biblioteca para controle do LED RGB
#include "lib/push_button.h"    // Biblioteca para controle do botão de pressão
#include "lib/mq7.h"            // Biblioteca para o sensor MQ-7 de monóxido de carbono
#include "lib/ws2812b.h"       // Biblioteca para controle da matriz de LEDs WS2812B
#include "hardware/clocks.h"    // Biblioteca para controle de clocks do hardware
#include <stdio.h>              // Biblioteca para funções de entrada e saída padrão

// Definições dos pinos de controle do LED RGB
#define RED_PIN   13           // Pino para o LED vermelho
#define GREEN_PIN 11           // Pino para o LED verde
#define BLUE_PIN  12           // Pino para o LED azul

// Definições do barramento I2C para o display OLED SSD1306
#define I2C_PORT i2c1          // Define o barramento I2C 1
#define I2C_SDA 14             // Pino SDA para comunicação I2C
#define I2C_SCL 15             // Pino SCL para comunicação I2C
#define DISPLAY_ADDR 0x3C     // Endereço I2C do display SSD1306

// Definição do pino de controle para o sensor MQ-7
#define MQ7_ADC_PIN 26        // Pino ADC para a leitura do MQ-7 (sensor de CO)

// Definição do limite de concentração de CO considerado seguro
#define THRESHOLD_PPM 150     // Limite de concentração de CO em partes por milhão (ppm)

// Definição do pino de controle para a matriz de LEDs WS2812B
#define WS2812B_PIN 7         // Pino de controle para a matriz WS2812B

// Atalho para reinicializar o sistema no modo BOOTSEL para programação via USB
#define set_bootsel_mode() reset_usb_boot(0, 0)

// Protótipo da função chamada quando o botão é pressionado
void on_button_press(uint gpio, uint32_t event);

int main() {
    // Configura o clock do sistema para 128 MHz
    set_sys_clock_khz(128000, false);

    // Inicialização das variáveis e estruturas para os dispositivos
    ws2812b_t ws;           // Estrutura para controle da matriz WS2812B
    ssd1306_t ssd;          // Estrutura para controle do display OLED SSD1306
    rgb_t rgb;              // Estrutura para controle do LED RGB
    uint8_t mq7_adc_channel; // Canal ADC para leitura do sensor MQ-7
    uint16_t co_ppm;        // Variável para armazenar a concentração de CO (ppm)
    char co_ppm_buffer[16]; // Buffer para formatar a string com o valor de CO

    // Inicializa a matriz de LEDs WS2812B
    init_ws2812b(&ws, pio0, WS2812B_PIN);

    // Inicializa o LED RGB com brilho inicial de 100% (1.0) e valor de 2048 para controle de intensidade
    rgb_init_all(&rgb, RED_PIN, GREEN_PIN, BLUE_PIN, 1.0, 2048);

    // Inicializa o buzzer com a configuração padrão
    buzzer_init_default();

    // Configuração do botão A
    pb_config_btn_a();

    // Associa a função de interrupção ao pressionar o botão A
    pb_set_irq_callback(&on_button_press);
    pb_enable_irq(BUTTON_A);

    // Inicializa o sensor MQ-7 e configura o canal ADC
    mq7_init(MQ7_ADC_PIN);
    mq7_adc_channel = ADC_CHANNEL_1;
    mq7_start_heating();    // Inicia o processo de aquecimento do sensor MQ-7

    // Inicializa o display OLED SSD1306 via I2C
    ssd1306_init_all(&ssd, I2C_PORT, 400000, I2C_SDA, I2C_SCL, DISPLAY_ADDR);

    // Desenha a estrutura inicial no display OLED
    ssd1306_rect(&ssd, 0, 0, 128, 64, true, false);  // Retângulo no topo
    ssd1306_hline(&ssd, 0, 127, 12, true);           // Linha horizontal no topo
    ssd1306_rect(&ssd, 32, 0, 128, 12, true, false); // Retângulo para título
    ssd1306_draw_string(&ssd, "status", OLED_COL6, 2);  // Texto "status"
    ssd1306_draw_string(&ssd, "CO Concetration", OLED_COL1, 32); // Texto "CO Concentration"
    ssd1306_send_data(&ssd);  // Envia os dados desenhados para o display

    // Loop principal do programa
    while (true) {
        // Lê o valor da concentração de CO (ppm) do sensor MQ-7
        co_ppm = mq7_get_ppm(mq7_adc_channel);

        // Formata o valor de CO como string
        sprintf(co_ppm_buffer, "%dPPM", co_ppm);

        // Limpa as linhas do display que precisam ser atualizadas
        ssd1306_clear_line(&ssd, OLED_LINE7);  // Limpa a linha do valor do PPM
        ssd1306_clear_line(&ssd, OLED_LINE3);  // Limpa a linha do status

        // Exibe o valor da concentração de CO no display
        ssd1306_draw_string(&ssd, co_ppm_buffer, OLED_COL6, OLED_LINE7);

        // Exibe o status ("SAFE" ou "DANGER") com base na concentração de CO
        ssd1306_draw_string(&ssd, (co_ppm < THRESHOLD_PPM) ? "SAFE" : "DANGER", OLED_COL6, OLED_LINE3);

        // Atualiza o display com os dados mais recentes
        ssd1306_send_data(&ssd);

        // Controle do LED e buzzer com base na concentração de CO
        if (co_ppm < THRESHOLD_PPM) {
            rgb_turn_off_red(&rgb);  // Desliga o LED vermelho
            rgb_turn_on_green(&rgb, 20); // Acende o LED verde com intensidade 20
            ws2812b_turn_off_all(&ws);  // Desliga a matriz de LEDs WS2812B
        } else {
            ws2812b_draw_X(&ws);   // Desenha um "X" na matriz WS2812B indicando perigo
            rgb_turn_off_green(&rgb);  // Desliga o LED verde
            rgb_turn_on_red(&rgb, 20);  // Acende o LED vermelho com intensidade 20
            buzzer_beep_default(100, 2000);  // Emite um bip do buzzer por 100ms com frequência de 2000Hz
            ws2812b_turn_off_all(&ws);  // Desliga a matriz de LEDs WS2812B
        }
    }
    return 0;  // Retorna 0 (não necessário, pois o código entra em um loop infinito)
}

// Função chamada quando o botão é pressionado
void on_button_press(uint gpio, uint32_t event) {
    // Se o debounce do botão terminou, entra no modo BOOTSEL para reprogramação via USB
    if (pb_is_debounce_delay_over()) {
        set_bootsel_mode();
    }
}
