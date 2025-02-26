# 🛡️ COGuard - Monitoramento de Monóxido de Carbono

## 📖 Índice

1. [🔍 Sobre o Projeto](#sobre-o-projeto)
2. [🛠️ Tecnologias Utilizadas](#tecnologias-utilizadas)
3. [🔗 Protocolos Utilizados](#protocolos-utilizados)
   - [🏗️ I²C (Inter-Integrated Circuit)](#i²c-inter-integrated-circuit)
   - [🔷 Protocolo Proprietário do WS2812B](#protocolo-proprietário-do-ws2812b)
   - [🎚️ PWM (Pulse Width Modulation)](#pwm-pulse-width-modulation)
   - [📊 ADC (Analog-to-Digital Converter)](#adc-analog-to-digital-converter)
4. [📌 Componentes e Pinagem](#componentes-e-pinagem)
5. [⚙️ Funcionamento](#funcionamento)
6. [📊 Benefícios do COGuard](#benefícios-do-coguard)
7. [🔎 Considerações Finais](#considerações-finais)
8. [📩 Contato](#contato)

## 🔍 Sobre o Projeto <a id="sobre-o-projeto"></a>

COGuard é um sistema altamente eficiente para detecção da concentração de gás monóxido de carbono (CO) em um ambiente, garantindo monitoramento contínuo e alertas automáticos para prevenir intoxicações. O sistema utiliza sensores precisos, protocolos de comunicação eficientes e componentes visuais e sonoros para alertar os usuários sobre a presença de CO em níveis potencialmente perigosos.

## 🛠️ Tecnologias Utilizadas <a id="tecnologias-utilizadas"></a>

- 💻 **Linguagem:** C11
- 🎛️ **Placa:** Raspberry Pi Pico W (BitDogLab)
- 📦 **SDK:** pico-sdk 2.1.1
- 🔧 **Compilador:** gnu-arm-eabi
- 🖥️ **IDE:** VS Code com extensões CMake e Raspberry Pi Pico

## 🔗 Protocolos Utilizados <a id="protocolos-utilizados"></a>

O COGuard faz uso de diversos protocolos de comunicação e controle para interagir eficientemente com seus componentes, garantindo uma operação estável e precisa. Cada protocolo foi escolhido com base em suas vantagens específicas para comunicação de sensores, acionamento de atuadores e controle de sinais analógicos e digitais.

### 🏗️ I²C (Inter-Integrated Circuit) <a id="i²c-inter-integrated-circuit"></a>

📟 O **I²C** é utilizado para a comunicação com o display OLED SSD1306, permitindo a troca eficiente de informações entre o microcontrolador e o display. Esse protocolo opera através de um barramento de dois fios (SDA e SCL), reduzindo a complexidade da fiação e possibilitando a conexão de múltiplos dispositivos com endereços únicos. Sua baixa taxa de consumo de energia torna-o ideal para dispositivos compactos e de baixa potência, como o SSD1306. Com um barramento de dois fios, ele possibilita a comunicação serial entre diversos dispositivos com um único mestre e múltiplos escravos, garantindo simplicidade e economia de conexões físicas.

### 🔷 Protocolo Proprietário do WS2812B <a id="protocolo-proprietário-do-ws2812b"></a>

💡 A matriz de LEDs 5x5 utiliza LEDs **WS2812B**, que possuem um protocolo proprietário projetado para comunicação eficiente através de um único fio de dados. Esse protocolo permite que cada LED seja controlado individualmente, possibilitando a criação de efeitos visuais dinâmicos com alta precisão e velocidade de atualização.

### 🎚️ PWM (Pulse Width Modulation) <a id="pwm-pulse-width-modulation"></a>

🌈 O **PWM** é utilizado para controlar a intensidade do LED RGB **SMD5050**, permitindo variar o brilho de cada canal de cor (vermelho, verde e azul) independentemente. Essa modulação é feita ajustando a largura do pulso do sinal elétrico, proporcionando um controle preciso da intensidade luminosa sem causar superaquecimento. Isso possibilita a criação de diferentes tonalidades de cores e transições suaves, tornando-o ideal para alertas visuais e feedbacks indicativos no COGuard.

### 📊 ADC (Analog-to-Digital Converter) <a id="adc-analog-to-digital-converter"></a>

🕹️ O **ADC** é empregado para converter os sinais analógicos do **sensor MQ-7** e do **joystick**, transformando tensões variáveis em valores digitais compreensíveis pelo microcontrolador. Esse processo permite que o sistema interprete a concentração de CO no ambiente e ajuste seus alertas com precisão. A conversão ocorre de forma contínua, garantindo uma resposta rápida às mudanças nos níveis de gás e melhorando a eficácia do monitoramento.

## 📌 Componentes e Pinagem <a id="componentes-e-pinagem"></a>

| 🏷️ Componente                 | 📌 Pino GPIO | 🔍 Descrição |
|------------------------------|-----------|---------------------------------|
| 🌡️ Sensor MQ-7 (Potenciômetro) | GPIO26 (Entrada ADC) | Sensor de monóxido de carbono com faixa de detecção de 10 a 10.000 ppm. |
| 🔊 Buzzer MLT8530            | GPIO21    | Buzzer compacto de 2700Hz usado para alertas sonoros. |
| 🌈 LED RGB (SMD5050)         | GPIO13, GPIO11 | LED RGB de montagem superficial com alta intensidade luminosa. |
| 💡 Matriz de LEDs 5x5 (WS2812B) | GPIO7     | LEDs endereçáveis individualmente para criar padrões de alerta. |
| 🎮 Joystick (VRY)            | GPIO26    | Controle analógico com dois eixos e botão integrado. |
| 📟 Display SSD1306 (SDA)     | GPIO14    | Display OLED monocromático de 128x64 pixels. |
| 📟 Display SSD1306 (SCL)     | GPIO15    | Comunicação I²C do display OLED SSD1306. |

## ⚙️ Funcionamento <a id="funcionamento"></a>

O COGuard opera monitorando continuamente os níveis de CO no ambiente, analisando as variações na concentração do gás em tempo real. Quando os níveis de CO estão abaixo do limite seguro de 150 ppm, o sistema mantém um estado normal, indicando um ambiente seguro no display OLED. Caso a concentração ultrapasse esse limite, o sistema entra em estado de alerta: o LED RGB muda para vermelho, a matriz de LEDs exibe um padrão de perigo e o buzzer emite um som de aviso. O monitoramento contínuo garante que qualquer alteração nos níveis de CO seja detectada rapidamente, permitindo que ações corretivas sejam tomadas para evitar riscos à saúde.

## 📊 Benefícios do COGuard <a id="benefícios-do-coguard"></a>

O COGuard oferece diversas vantagens em relação a outros sistemas de detecção de monóxido de carbono, incluindo:

- 🚀 **Alta Eficiência:** Monitoramento contínuo e respostas rápidas para garantir a segurança do ambiente.
- 🌍 **Sustentabilidade:** Baixo consumo de energia e componentes otimizados para uso prolongado.
- 🔧 **Facilidade de Integração:** Compatível com IoT e expansão para redes inteligentes de monitoramento.
- 📊 **Visualização Avançada:** Exibição de dados em tempo real no display OLED, permitindo acompanhamento detalhado.
- 🔔 **Alertas Inteligentes:** Utiliza LED RGB, matriz de LEDs e buzzer para fornecer alertas visuais e sonoros eficientes.

## 🔎 Considerações Finais <a id="considerações-finais"></a>

🔬 O COGuard é uma solução robusta e confiável para monitoramento da qualidade do ar, projetado para oferecer segurança em ambientes internos e externos. Seu design modular e sua integração com sensores precisos garantem uma resposta rápida a qualquer alteração nos níveis de monóxido de carbono. Além disso, sua arquitetura baseada na Raspberry Pi Pico W permite futuras expansões, como conectividade com redes IoT para monitoramento remoto e integração com sistemas automatizados de ventilação e alarmes. Dessa forma, o COGuard não apenas detecta níveis inseguros de CO, mas também se posiciona como uma solução escalável e eficiente para diversas aplicações industriais e domésticas.

## 📩 Contato <a id="contato"></a>

📧 **E-mail:** <cvaladao@ecomp.uefs.br>
