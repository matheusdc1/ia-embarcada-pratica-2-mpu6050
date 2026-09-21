---
id: 3ba75968-318e-413f-b8b8-60ef21c29fb6
slug: embedded
type: scar
title: MPU6050 1.2.1 precisa do componente driver no ESP-IDF 6.1
tags: esp-idf, mpu6050, i2c, build
provenance: observado
evidence: C:\Users\mdc\tarefa\managed_components\espressif__mpu6050\CMakeLists.txt
decay: seasonal
created: 2026-09-21T22:00:24.353093900+00:00
updated: 2026-09-21T22:00:24.353093900+00:00
validated: 2026-09-21T22:00:24.353093900+00:00
links:
---

No ESP-IDF 6.1, o componente espressif/mpu6050 1.2.1 falha ao compilar com `driver/i2c.h: No such file or directory` porque seu CMake declara apenas `esp_driver_gpio` e `esp_driver_i2c`. Para manter a biblioteca usada na aula, inclua também `driver` na variável `REQ` para IDF >= 5.3 e versione o componente corrigido; depois reconfigure o projeto. O driver I2C legado está EOL no IDF 6 e exigirá migração antes do IDF 7.
