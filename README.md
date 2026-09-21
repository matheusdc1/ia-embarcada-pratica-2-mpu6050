# Leitura do MPU6050 com ESP32-S3

Aplicação embarcada em C para o ESP-IDF que lê aceleração, rotação e temperatura de um MPU6050 simulado no Wokwi. As leituras são enviadas ao monitor serial a cada segundo.

## Circuito

| ESP32-S3 | MPU6050 |
| --- | --- |
| 3V3 | VCC |
| GND | GND |
| GPIO 8 | SDA |
| GPIO 9 | SCL |

O circuito completo está em `diagram.json`.

## Estrutura principal

- `main/main.c`: inicialização do I2C e do MPU6050, validação do dispositivo e laço de leitura.
- `main/idf_component.yml`: dependência `espressif/mpu6050` 1.2.1.
- `diagram.json`: ESP32-S3 e MPU6050 conectados no Wokwi.
- `wokwi.toml`: firmware e símbolos usados pela extensão Wokwi.

O componente MPU6050 é mantido no repositório com uma pequena correção de compatibilidade para o ESP-IDF 6.1: ele também declara o componente legado `driver`, que fornece `driver/i2c.h`. O aviso de descontinuação desse driver foi silenciado porque a biblioteca escolhida na aula ainda depende dessa API; uma migração futura para o ESP-IDF 7 exigirá outra biblioteca ou a atualização do componente.

## Compilar

No VS Code, use o comando **ESP-IDF: Build your project**. Pelo terminal ESP-IDF, o equivalente é:

```powershell
idf.py set-target esp32s3
idf.py build
```

O build deve terminar com `Project build complete` e gerar `build/tarefa.elf` e `build/flasher_args.json`.

## Executar no Wokwi

1. Compile o projeto.
2. Abra a barra lateral **Wokwi Simulator** no VS Code.
3. Clique em **Start Simulation**.
4. Aguarde a inicialização e observe o terminal do Wokwi.

A saída esperada tem este formato:

```text
I (...) mpu6050_app: MPU6050 iniciado corretamente (WHO_AM_I=0x68)
I (...) mpu6050_app: ACC[g] x=  0.00 y=  0.00 z=  1.00 | GYRO[dps] x=   0.00 y=   0.00 z=   0.00 | TEMP[C] 36.53
```

É possível alterar a aceleração e a rotação clicando no MPU6050 durante a simulação.

## Evidências para a entrega

Capture imagens legíveis mostrando:

1. ESP-IDF configurado no VS Code e conta/licença do Wokwi ativa.
2. Circuito completo no Wokwi, com os quatro fios visíveis.
3. Terminal do build exibindo `Project build complete`.
4. Simulação e monitor serial exibindo várias leituras do MPU6050.

Não inclua a pasta `build` no Git. Depois de validar as evidências, publique este projeto em um repositório e envie o respectivo link.
