# Tarefa 1 Clock - Embarcatech

Este projeto implementa um semáforo utilizando o Raspberry Pi Pico e a função add_repeating_timer(). O temporizador controla a mudança de estados do semáforo, garantindo que cada LED permaneça aceso por 3 segundos antes de passar para o próximo estado.

## Requisitos

- Placa Bitdoglab
- Compilador C
- VS Code instalado
- Pico SDK configurado
- Simulador Wokwi integrado ao VS Code
- Git instalado
- Extensão C/C++ instalada no VS Code
- Extensão Raspberry Pi Tools instalada no VS Code

## Funcionamento

- O sistema utiliza três LEDs para representar as cores do semáforo: vermelho, amarelo e verde.
- A cada 3 segundos, o temporizador alterna para o próximo LED na sequência correta do semáforo.
- O ciclo é contínuo, simulando o funcionamento de um semáforo real.

## Como executar

1. Clone o repositório:

```bash
git clone [https://github.com/matheusssilva991/tarefa_interrupcao_U4C4.git]
```

2. Configure o ambiente de desenvolvimento seguindo as instruções do Pico SDK

3. Abra o projeto no VS Code

4. Importe o projeto através da extensão Raspberry Pi Tools

5. Execute a simulação através do Wokwi ou da placa Bitdoglab

## 🤝 Equipe

Membros da equipe de desenvolvimento do projeto:
<table>
  <tr>
    <td align="center">
      <a href="https://github.com/matheusssilva991">
        <img src="https://github.com/matheusssilva991.png" width="100px;" alt="Foto de Matheus Santos Silva no GitHub"/><br>
        <b>Matheus Santos Silva (matheusssilva991)</b>
        <p>Desenvolvedor Back-end - NestJS</p>
      </a>
    </td>
  <tr>
</table>
