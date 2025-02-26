/**
 * @file ssd1306_utils.h
 * @brief Este arquivo contém definições e declarações de funções auxiliares para
 *        a manipulação do display OLED SSD1306 (128x64) via protocolo I2C.
 * 
 * @note As funções definidas aqui permitem limpar a tela, imprimir caracteres e
 *       strings, bem como configurar a posição do cursor para escrita automática.
 *       O display é organizado em linhas e colunas, com deslocamentos de 8 pixels.
 * 
 * @author Carlos Valadão
 * @date 09/02/2025
 */

 #ifndef SSD1306_UTILS_H
 #define SSD1306_UTILS_H
 
 #include "ssd1306.h"
 
 // Macro para converter um valor em uint8_t
 #define UINT8_T_CONSTANT1(value) ((uint8_t) (value))
 
 // Definições das coordenadas das linhas do display OLED
 // Cada linha tem um deslocamento vertical de 8 pixels
 #define OLED_LINE1 UINT8_T_CONSTANT1(0)   // Primeira linha do display
 #define OLED_LINE2 UINT8_T_CONSTANT1(8)   // Segunda linha
 #define OLED_LINE3 UINT8_T_CONSTANT1(16)  // Terceira linha
 #define OLED_LINE4 UINT8_T_CONSTANT1(24)  // Quarta linha
 #define OLED_LINE5 UINT8_T_CONSTANT1(32)  // Quinta linha
 #define OLED_LINE6 UINT8_T_CONSTANT1(40)  // Sexta linha
 #define OLED_LINE7 UINT8_T_CONSTANT1(48)  // Sétima linha
 #define OLED_LINE8 UINT8_T_CONSTANT1(56)  // Oitava linha
 
 // Definições das coordenadas das colunas do display OLED
 // Cada coluna tem um deslocamento horizontal de 8 pixels
 #define OLED_COL1  UINT8_T_CONSTANT1(0)   // Primeira coluna do display
 #define OLED_COL2  UINT8_T_CONSTANT1(8)   // Segunda coluna
 #define OLED_COL3  UINT8_T_CONSTANT1(16)  // Terceira coluna
 #define OLED_COL4  UINT8_T_CONSTANT1(24)  // Quarta coluna
 #define OLED_COL5  UINT8_T_CONSTANT1(32)  // Quinta coluna
 #define OLED_COL6  UINT8_T_CONSTANT1(40)  // Sexta coluna
 #define OLED_COL7  UINT8_T_CONSTANT1(48)  // Sétima coluna
 #define OLED_COL8  UINT8_T_CONSTANT1(56)  // Oitava coluna
 #define OLED_COL9  UINT8_T_CONSTANT1(64)  // Nona coluna
 #define OLED_COL10 UINT8_T_CONSTANT1(72)  // Décima coluna
 #define OLED_COL11 UINT8_T_CONSTANT1(80)  // Décima primeira coluna
 #define OLED_COL12 UINT8_T_CONSTANT1(88)  // Décima segunda coluna
 #define OLED_COL13 UINT8_T_CONSTANT1(96)  // Décima terceira coluna
 #define OLED_COL14 UINT8_T_CONSTANT1(104) // Décima quarta coluna
 #define OLED_COL15 UINT8_T_CONSTANT1(112) // Décima quinta coluna
 #define OLED_COL16 UINT8_T_CONSTANT1(120) // Décima sexta coluna
 
 /**
  * @brief Limpa completamente a tela do display OLED.
  * 
  * @param ssd Ponteiro para a estrutura do display SSD1306.
  */
 void ssd1306_clear_screen(ssd1306_t *ssd);
 
 /**
  * @brief Limpa uma linha específica do display OLED.
  * 
  * @param ssd Ponteiro para a estrutura do display SSD1306.
  * @param line Linha a ser apagada (0 a 56, em múltiplos de 8 pixels).
  */
 void ssd1306_clear_line(ssd1306_t *ssd, uint8_t line);
 
 /**
  * @brief Imprime um caractere no display OLED.
  * 
  * @param ssd Ponteiro para a estrutura do display SSD1306.
  * @param c Caractere a ser impresso.
  * @param x Posição horizontal (coluna) do caractere.
  * @param y Posição vertical (linha) do caractere.
  */
 void ssd1306_print_char(ssd1306_t *ssd, char c, uint8_t x, uint8_t y);
 
 /**
  * @brief Imprime uma string no display OLED.
  * 
  * @param ssd Ponteiro para a estrutura do display SSD1306.
  * @param str String a ser exibida.
  * @param x Posição horizontal (coluna) inicial da string.
  * @param y Posição vertical (linha) inicial da string.
  */
 void ssd1306_print_str(ssd1306_t *ssd, const char *str, uint8_t x, uint8_t y);
 
 /**
  * @brief Inicializa o display OLED SSD1306.
  * 
  * @param ssd Ponteiro para a estrutura do display SSD1306.
  * @param i2c Instância do barramento I2C usado.
  * @param baudrate Taxa de comunicação I2C em bits por segundo.
  * @param sda Pino de dados SDA do I2C.
  * @param scl Pino de clock SCL do I2C.
  * @param address Endereço I2C do display SSD1306.
  */
 void ssd1306_init_all(ssd1306_t *ssd, i2c_inst_t *i2c, uint baudrate, uint8_t sda, uint8_t scl, uint8_t address);
 
 /**
  * @brief Escreve automaticamente um caractere na posição atual do cursor.
  * 
  * @param ssd Ponteiro para a estrutura do display SSD1306.
  * @param c Caractere a ser impresso.
  */
 void ssd1306_auto_write_char(ssd1306_t *ssd, char c);
 
 /**
  * @brief Define a posição do cursor para escrita automática de caracteres.
  * 
  * @param col Posição da coluna onde o cursor será posicionado.
  * @param line Posição da linha onde o cursor será posicionado.
  */
 void ssd1306_set_auto_write_cursor(uint8_t col, uint8_t line);
 
 #endif // SSD1306_UTILS_H
 