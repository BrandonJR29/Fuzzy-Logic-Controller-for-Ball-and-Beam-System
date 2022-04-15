# Fuzzy Logic Controller for the Quanser's Ball and Beam System

Implementation and simulation of fuzzy logic controllers for the ball and beam system of Quanser.

The fuzzy logic controllers were designed and optimized using patern search method (iterative method) implemented in Matlab and Simulink.

The controllers were embedded in a ESP32 microcontroller, using a library for fuzzy logic [eFFL](https://github.com/zerokol/eFLL) using a custom membership function designed in this project.

If you want to know more details about the implementation, theory or any deatils please consult the [document](./tomo) (It is in spanish).

## Demo

The test videos are in this [link](https://www.youtube.com/watch?v=K9Vu6w_IInE&list=PL-Z_5Zx_UY59NFn0tXmD-8x4Mgz_DTYgh)

## Block diagram of the controll system

![esquema-de-control](./imagenes/esquema.png)

## Control Topology.

### Double loop.

![doble-lazo](./imagenes/dobleLazo.png)

### Fuzzy Logic controller with three inputs.

![tres-entradas](./imagenes/tresEntradas.png)

## Simulation results.

| Controller | PD | Fuzzy |
| ------ | ------ | ------- |
| Settling time [s] | 2.3404 | 1.6107 |
| Rise time [s] | 0.6812 | 1.1030 |
| Overshoot [%] | 12.0648 | 0.9372 |

![resultado-simulacion](./imagenes/simulacion.png)

## Implementation results.

| Controller | PD | Fuzzy |
| ------ | ------ | ------- |
| Settling time [s] | 2.3618 | 1.9159 |
| Rise time [s] | 0.7576 | 1.4304 |
| Overshoot [%] | 12.5931 | 0 |

![resultado-implementación](./imagenes/resultadoFinal.png)

