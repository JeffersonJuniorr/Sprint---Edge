Jefferson Junior Alvarez rm558497 | Arthur Galvão Alves rm554462 | Felipe Braunstein e Silva rm554483 | Eduardo da Silva Lima rm554804


## Dependências
- **Arduino IDE**: Ambiente de desenvolvimento para programação do Arduino.
- **Placa Arduino**: Qualquer placa compatível (por exemplo, Arduino Uno, Nano, etc.).
- **Sensores Ultrassônicos**: Sensores HC-SR04 ou similares para medição de distância.
- **Display LCD 20x4 (I2C)**: Para exibição das direções dos objetos detectados.
- **LEDs**: Indicadores visuais para representar as direções dos objetos próximos.
- **Componentes Eletrônicos**: Resistores, jumpers, etc.

## Como Reproduzir
Para reproduzir este projeto, siga as etapas abaixo:

1. **Montagem dos Componentes**:
   - Conecte os sensores ultrassônicos aos pinos especificados no código.
   - Conecte o display LCD 20x4 ao Arduino via interface I2C.
   - Conecte os LEDs aos pinos correspondentes para indicar as direções.

2. **Configuração do Código**:
   - Verifique e compile o código para garantir que não haja erros.
   - Faça o upload do código para o Arduino.

3. **Teste e Operação**:
   - Após o upload, observe o display LCD e os LEDs para verificar o funcionamento.
   - Simule a presença de obstáculos próximos ao veículo para testar a detecção e o feedback visual.

## Funcionamento
O sistema opera da seguinte maneira:

- **Leitura de Distância**: Os sensores ultrassônicos medem a distância dos objetos em várias direções (frente, trás, esquerda, direita).
- **Feedback Visual**: LEDs indicam a direção da qual os objetos detectados estão se aproximando.
- **Feedback no LCD**: Um display LCD 20x4 exibe uma representação gráfica das direções dos objetos detectados.
- **Alerta de Colisão**: Quando um objeto se aproxima perigosamente, o LED correspondente acende e a representação gráfica no LCD é atualizada.

Link do projeto:https://wokwi.com/projects/400877359941740545
