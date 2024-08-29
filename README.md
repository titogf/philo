
# Problema de los Filósofos

Este proyecto implementa la solución al clásico problema de los filósofos utilizando programación en C, con hilos y mutex para manejar la sincronización entre los filósofos que compiten por los recursos (tenedores).

## Descripción

En este problema, cinco filósofos se sientan en una mesa redonda. Cada filósofo tiene un tenedor a su izquierda y su derecha. Para poder comer, un filósofo necesita ambos tenedores, pero solo puede tomar un tenedor a la vez. El reto es evitar el interbloqueo (deadlock) y la inanición (starvation) de los filósofos mientras intentan comer y pensar alternativamente.


En esta representación:
- Cada filósofo puede estar "pensando" o "comiendo".
- Los tenedores son los recursos compartidos que los filósofos necesitan para comer.

## Instalación

Para compilar el proyecto, se incluye un `Makefile` que simplifica la compilación. Asegúrate de tener `make` instalado en tu sistema. Luego, puedes compilar el proyecto con el siguiente comando:
<br>`make`<br>
Esto generará un ejecutable llamado philosopher.

Si en algún momento deseas limpiar los archivos compilados, puedes usar:
<br>`make clean`


## Uso
Una vez compilado, puedes ejecutar el programa con el siguiente comando:

```
./philosopher [nb_de_filosofos] [time_to_die] [time_to_eat] [number_of_times_each_philosopher_must_eat]
```
nb_de_filosofos: Número de filósofos (y tenedores) en la mesa.
time_to_die: Tiempo (en milisegundos) que un filósofo puede estar sin comer antes de morir.
time_to_eat: Tiempo (en milisegundos) que tarda un filósofo en comer.
number_of_times_each_philosopher_must_eat: Número de veces que cada filósofo debe comer antes de que termine el programa. (Opcional, si no se especifica, el programa seguirá hasta que se interrumpa manualmente.)
Ejemplo de ejecución:
```
./philosopher 5 800 200 5
```
En este ejemplo:
Habrá 5 filósofos en la mesa.
Un filósofo morirá si no come en 800 ms.
Un filósofo tardará 200 ms en comer.
Cada filósofo debe comer 5 veces antes de que el programa termine.
