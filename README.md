# Aspirador Inteligente - IA

En esta práctica desarrollé un algoritmo de inteligencia artificial reactiva para recrear el comportamiento de un robot aspirador estilo _"Roomba"_. 
El agente ya compilado contiene un entorno gráfico que permite cargar mapas con diferentes modelos de habitación. 
Esta interfaz comprueba el movimiento del robot según su algoritmo para 2000 movimientos, teniendo en cuenta que la suciedad se va generando aleatoriamente por toda la habitación y se va acumulando a menos que la limpie el robot.

## Algoritmo ##

La clave del algoritmo consiste en diseñar un sistema por el cual el robot pueda crear un mapa virtual de la habitación y recordar donde están los obstáculos, con el fin de no chocar más de una vez con cada uno y ser más eficiente.
El algoritmo, una vez aprendida la habitación irá navegando por ella priorizando las casillas por las que haya pasado más tiempo desde la última vez que pasó.

La memoria PDF adjunta da una explicación más extensa del funcionamiento del algoritmo y además cuenta con una relación de cuál ha sido su eficacia y eficiencia a la hora de limpiar distintos tipos de mapas.

### Variante: Perro busca trufas ###

Este ejercicio contiene una variante al problema del aspirador: En lugar de un aspirador el agente es un perro que en lugar de aspirar suciedad, debe recoger trufas que se generan aleatoriamente en el mapa. 
La dificultad añadida de esta variante es que el perro deberá recoger las trufas de una casilla antes de que pase demasiado tiempo, en caso contrario, las trufas se pudrirán y la casilla quedará inutilizada para el resto de la partida.

## Instalación y requisitos
El algoritmo de la IA está contenido en los archivos `agent.cpp` y `agent.h`. Para ejecutarlo, descomprime cualquiera de los entornos gráficos según tu sistema operativo y sustituye estos archivos por los contenidos en el directorio `Agent_Solucion_Jotaele``.

## Notas
Si eres estudiante de la UGR y te estás enfrentando a esta práctica o una similar, te sugiero que no trates de descargarla o copiarla, ya que los profesores conocen de la existencia de estos repositorios y lo más probable es que te pillen. En su lugar, te sugiero utilizarla como referencia si te quedas atascado. ;)

Si encuentras cualquier error o quieres proponer una mejora en el proyecto, simplemente envía un pull request.


