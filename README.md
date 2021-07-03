# Control-Difuso-para-Sistema-Ball-and-Beam

Implementación y simulación de controladores difusos en el sistema Ball and Beam de Quanser.

Los controladores difusos fueron diseñados y optimizados por el método de patrón de búsqueda
implementado en Matlab y Simulink mediante un proceso iterativo.

La implementación se llevo a cabo usando el microcontrolador ESP32, usando la librería de lógica
difusa [eFFL](https://github.com/zerokol/eFLL) modificada para poder usar la función unica propuesta
en este trabajo.

Para obtener más información acerca del sistema Ball and Beam de Quanser, hardware implementado o del firmware
se puede observar con mayor detalle en este [documento](./tomo)

## Demo

Si desea ver como se obtuvieron los resultados, puede verlos en este [enlace](https://www.youtube.com/watch?v=K9Vu6w_IInE&list=PL-Z_5Zx_UY59NFn0tXmD-8x4Mgz_DTYgh)

## Esquema del sistema de control

![esquema-de-control](./imagenes/esquema.png)

## Topologias de control

### Doble lazo

![doble-lazo](./imagenes/dobleLazo.png)

### Controlador Difuso con tres entradas

![tres-entradas](./imagenes/tresEntradas.png)

## Resultado de simulación

| Controlador | PD | Difuso |
| ------ | ------ | ------- |
| Tiempo de establecimiento [s] | 2.3404 | 1.6107 |
| Tiempo de alza [s] | 0.6812 | 1.1030 |
| Sobre pico [%] | 12.0648 | 0.9372 |

![resultado-simulacion](./imagenes/simulacion.png)

## Resultado de implementación.

| Controlador | PD | Difuso |
| ------ | ------ | ------- |
| Tiempo de establecimiento [s] | 2.3618 | 1.9159 |
| Tiempo de alza [s] | 0.7576 | 1.4304 |
| Sobre pico [%] | 12.5931 | 0 |

![resultado-implementación](./imagenes/resultadoFinal.png)

