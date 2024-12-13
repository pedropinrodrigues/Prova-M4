# Prova-M4
Prova do módulo 4. Parte prática.

## Imagem do Projeto final
![image](https://github.com/user-attachments/assets/095491bd-d562-4428-8074-91fc20b8e462)

O projeto contém três leds, um Esp32, um PushButton e um sensor LDR. 

Ele pode estar em dois modos diferentes. Caso o LDR, reconheça que a luminosidade está inferior à 600, será ligado o modo Noturno, no qual o Led AMARELO ficará piscando a cada 1 segundo. Caso ele reconheça um valor superior, será ativado o modo diurno, no qual haverá uma temporização alternando entre verde (3 segundos), amarelo (2 segundos) e vermelho (5 segundos). Além disso, o ESP é capaz de se conectar e desconectar com a Internet. Além disso, foi implementado uma lógica de debounce usando millis() para o botão.

![image](https://github.com/user-attachments/assets/b1d63a1b-f90a-4d29-9872-2d36d96413e3)
![image](https://github.com/user-attachments/assets/482072f2-3451-4358-bc76-b834b07506ae)
![image](https://github.com/user-attachments/assets/3542c733-141d-4631-ae84-c01dd0e67db3)
