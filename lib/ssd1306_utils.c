#include "ssd1306_utils.h"

// Variáveis estáticas para armazenar a posição do cursor no display
static uint8_t cursor_col = 0;  // Coluna atual do cursor
static uint8_t cursor_row = 0;  // Linha atual do cursor
static uint8_t aux_col = 0;     // Coluna auxiliar para escrita automática
static uint8_t aux_row = 0;     // Linha auxiliar para escrita automática

/**
 * @brief Limpa completamente o conteúdo do display OLED SSD1306.
 * 
 * @param ssd Ponteiro para a estrutura do display SSD1306.
 */
void ssd1306_clear_display(ssd1306_t *ssd)
{
    ssd1306_fill(ssd, false);   // Preenche a tela com fundo apagado
    ssd1306_send_data(ssd);     // Envia os dados para atualização do display
}

/**
 * @brief Limpa uma linha específica do display, apagando todos os pixels nela contidos.
 * 
 * @param ssd Ponteiro para a estrutura do display SSD1306.
 * @param line Linha a ser apagada (0 a 56, em múltiplos de 8 pixels).
 */
void ssd1306_clear_line(ssd1306_t *ssd, uint8_t line)
{
    // Itera por todas as posições da linha no display e apaga os pixels
    for(uint8_t l = line; l <= line + 8; l++)
    {
        for (uint8_t x = 0; x < ssd->width; ++x) {
            ssd1306_pixel(ssd, x, l, 0); // Define o pixel como apagado (0)
        }
    }
}

/**
 * @brief Imprime um caractere no display OLED em uma posição específica.
 * 
 * @param ssd Ponteiro para a estrutura do display SSD1306.
 * @param c Caractere a ser impresso.
 * @param x Posição horizontal (coluna) do caractere.
 * @param y Posição vertical (linha) do caractere.
 */
void ssd1306_print_char(ssd1306_t *ssd, char c, uint8_t x, uint8_t y)
{
    ssd1306_draw_char(ssd, c, x, y); // Desenha o caractere na posição desejada
    ssd1306_send_data(ssd);          // Atualiza o display para refletir a alteração
}

/**
 * @brief Imprime uma string no display OLED a partir de uma posição específica.
 * 
 * @param ssd Ponteiro para a estrutura do display SSD1306.
 * @param str String a ser exibida.
 * @param x Posição horizontal (coluna) inicial da string.
 * @param y Posição vertical (linha) inicial da string.
 */
void ssd1306_print_str(ssd1306_t *ssd, const char *str, uint8_t x, uint8_t y)
{
    ssd1306_draw_string(ssd, str, x, y); // Desenha a string na posição especificada
    ssd1306_send_data(ssd);              // Atualiza o display para exibir a string
}

/**
 * @brief Inicializa o display OLED SSD1306 e configura os pinos de comunicação I2C.
 * 
 * @param ssd Ponteiro para a estrutura do display SSD1306.
 * @param i2c Instância do barramento I2C usado.
 * @param baudrate Taxa de comunicação I2C em bits por segundo.
 * @param sda Pino de dados SDA do I2C.
 * @param scl Pino de clock SCL do I2C.
 * @param address Endereço I2C do display SSD1306.
 */
void ssd1306_init_all(ssd1306_t *ssd, i2c_inst_t *i2c, uint baudrate, uint8_t sda, uint8_t scl, uint8_t address)
{
    i2c_init(i2c, baudrate);         // Inicializa a comunicação I2C com a taxa especificada
    gpio_set_function(sda, GPIO_FUNC_I2C); // Define os pinos SDA e SCL para função I2C
    gpio_set_function(scl, GPIO_FUNC_I2C);
    gpio_pull_up(sda);               // Habilita pull-up nos pinos I2C
    gpio_pull_up(scl);
    ssd1306_init(ssd, WIDTH, HEIGHT, false, address, i2c); // Inicializa o display SSD1306
    ssd1306_config(ssd);             // Configura o display
    ssd1306_send_data(ssd);          // Atualiza o display
}

/**
 * @brief Escreve automaticamente um caractere no display OLED na posição atual do cursor.
 *        Se a linha estiver cheia, move o cursor para a próxima linha.
 * 
 * @param ssd Ponteiro para a estrutura do display SSD1306.
 * @param c Caractere a ser impresso.
 */
void ssd1306_auto_write_char(ssd1306_t *ssd, char c)
{
    // Se a posição atual do cursor atinge a largura do display, move para a próxima linha
    if (aux_col == WIDTH) {
        aux_col = OLED_COL1; // Reinicia a coluna
        aux_row += 8;        // Move para a próxima linha
        if(aux_row == HEIGHT) { // Se atingir o final da tela, reinicia a posição
            aux_col = cursor_col;
            aux_row = cursor_row;
        }
    }
    ssd1306_print_char(ssd, c, aux_col, aux_row); // Imprime o caractere
    aux_col += 8; // Avança para a próxima posição da coluna
}

/**
 * @brief Define a posição do cursor para escrita automática de caracteres.
 * 
 * @param col Posição da coluna onde o cursor será posicionado.
 * @param line Posição da linha onde o cursor será posicionado.
 */
void ssd1306_set_auto_write_cursor(uint8_t col, uint8_t line)
{
    cursor_col = col;  // Atualiza a posição da coluna
    cursor_row = line; // Atualiza a posição da linha
    aux_col = cursor_col;  // Define a posição auxiliar do cursor
    aux_row = cursor_row;
}
