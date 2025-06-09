# Sistema IoT para Monitoramento e Prevenção de Alagamentos

Este projeto consiste em um sistema inteligente baseado em IoT (Internet das Coisas) para o monitoramento em tempo real de variáveis ambientais associadas a riscos de alagamento urbano. Ele faz parte de um ecossistema maior que envolve também uma API em .NET e um modelo de Machine Learning (ML.NET) que auxilia na previsão de enchentes e envio de alertas à população por meio de um aplicativo.

## Visão Geral

A solução foi projetada com foco em cidades sujeitas a inundações. O módulo IoT coleta dados de sensores físicos, envia-os periodicamente para a nuvem e contribui com o sistema central de tomada de decisão.

O sistema é composto por:

- Sensores físicos conectados a um ESP32
- Envio de dados para o ThingSpeak
- Consumo desses dados via API REST em .NET
- Predição de alagamentos com ML.NET
- Aplicativo que alerta a população em tempo real

## Estrutura do Sistema IoT

### Componentes Utilizados

| Componente             | Função                                                             |
|------------------------|--------------------------------------------------------------------|
| ESP32 DevKit V1        | Microcontrolador com conectividade Wi-Fi                          |
| Sensor DHT22           | Mede temperatura e umidade do ar                                  |
| Potenciômetro          | Simula o nível do rio (sensor analógico de variação de altura)    |
| Slide Switch (SPDT)    | Simula a presença de chuva intensa (substitui botão físico)       |
| LED + Resistor         | Indica visualmente quando o nível do rio ultrapassa o limite      |

### Funcionamento

- A cada 15 segundos, o ESP32:
  - Lê os dados de temperatura e umidade (via DHT22)
  - Lê o nível do rio (simulado via potenciômetro)
  - Detecta ocorrência de chuva (via chave deslizante)
  - Acende um LED se o nível do rio estiver acima do valor crítico
  - Envia os dados para o ThingSpeak (fields 1 a 4)

### ThingSpeak (Nuvem)

Os dados são enviados via protocolo HTTP para o canal ThingSpeak, sendo atribuídos da seguinte forma:

| Campo     | Dados enviados         |
|-----------|------------------------|
| field1    | Nível do rio (0 a 4095)|
| field2    | Umidade do ar (%)      |
| field3    | Temperatura (°C)       |
| field4    | Ocorrência de chuva (0 ou 1) |

## Integração com .NET e Machine Learning

O sistema IoT não atua de forma isolada. Os dados armazenados no ThingSpeak são consumidos por uma API .NET, que:

- Consulta os dados mais recentes
- Armazena em banco de dados
- Alimenta um modelo preditivo (ML.NET)
- Avalia o risco de alagamento iminente com base em padrões históricos
- Gera alertas para o aplicativo de monitoramento urbano

## Aplicativo de Alerta

O app, conectado à API, apresenta funcionalidades como:

- Alertas personalizados por localização
- Mapa interativo com pontos de risco
- Denúncia de alagamentos e entupimentos
- Dados climáticos em tempo real

## Finalidade do Projeto

Este sistema foi desenvolvido com o objetivo de:

- Monitorar em tempo real o risco de enchentes
- Prevenir desastres naturais em áreas urbanas
- Fornecer dados confiáveis e automatizados para decisões emergenciais
- Integrar sensores físicos, nuvem, inteligência artificial e mobilidade
- Proteger vidas e reduzir prejuízos com uma abordagem proativa e inteligente

# Vídeo Pitch - IoT:

https://youtu.be/OHnENFurQcU

# Vídeo Pitch - Projeto:

https://youtu.be/x8Oygxk1--8
