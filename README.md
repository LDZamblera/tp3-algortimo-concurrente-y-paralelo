# tp3-algortimo-concurrente-y-paralelo

1	Objetivo

El objetivo principal de esta actividad consiste en que el estudiante trabaje en posibles soluciones e implemente una solución a la problemática planteada, en la cual pondrá en juego las competencias de la materia. Puntualmente, trabajará con concurrencia y paralelismo, en memoria compartida y distribuida mediante procesos, subprocesos, hilos pipes y sockets.

2	Situación problemática

A continuación se presenta un caso. Lee con atención el mismo, teniendo presente cada uno de los contenidos que hemos desarrollado en el módulo, ya que luego tendrás que resolver una actividad retomándolos. Haz clic sobre el siguiente enlace para descargar el enunciado:

Trabajo Práctico
Enunciado de la actividad
En el desarrollo de sistemas actuales es indispensable poder diseñar, implementar y
mantener sistemas basados en algoritmos eficientes que utilicen de forma adecuada los
recursos subyacentes. En este sentido, el dominio de la concurrencia y el paralelismo
son competencias sumamente necesarias.
En este trabajo práctico, deberás analizar el problema planteado, diseñando y
desarrollando una aplicación que simula partidas del juego siete y medio. Para compilar
un programa que utilice la librería pthreads, debes utilizar la opción de enlace –lpthread.

03	Consignas de la actividad

Este trabajo es de entrega individual, pero requiere para su realización haber participado del Foro de Discusión Grupal TP3 como condición obligatoria, dado que el desarrollo de competencias para la construcción colectiva es central en nuestra asignatura.

Es muy importante que sepas que, si entregas el TP2 sin haber participado previamente en el Foro de Discusión Grupal TP3, tu calificación será de uno (1) para el TP3 sin excepción. Por ello, respeta las siguientes consignas y su orden para tener mejores resultados. 

¡Adelante!

 

1| Para participar en el Foro de Discusión Grupal TP3 deberás tener en cuenta lo solicitado en las preguntas que se desarrollan a continuación:

 

¿Cuál es su opinión sobre el uso de concurrencia y paralelismo en aplicaciones que gestionan memoria compartida o distribuida, mediante procesos, subprocesos, hilos, pipes y sockets? ¿Qué desafíos y ventajas ve en la implementación de estas técnicas en proyectos de software?
 

Es muy importante utilizar un lenguaje adecuado y acorde a lo planteado en la actividad, respetando la palabra del otro desde la cordialidad en un diálogo compartido. Los aportes de cada uno de ustedes será una instancia de enriquecimiento para la elaboración de su trabajo práctico individual. 

No serán consideradas las respuestas que simplemente expresen estar de acuerdo o en desacuerdo con las ideas de sus compañeros/as sin proporcionar su propia visión justificada en forma clara. (Extensión máxima de 1500 caracteres).

 

2| Solo si ya has realizado tus aportes en el Foro de Discusión Grupal TP3 y revisado los aportes de tus compañeros, llegó el momento de que realices el TP3, que es de construcción y entrega individual y deberás entregar en el espacio identificado como entregar tarea.

Recuerda que aun cuando realices este punto 2, y lo entregues en tiempo y forma, sin haber realizado previamente el punto 1 en el foro, tu calificación será igual a uno (1) sin excepción.

Por el contrario, si ya has realizado tu aporte en el foro, llegó el momento de hacer y subir el TP3. Para ello, deberás resolver las siguientes consignas:

 

a. Diseña y desarrolla una aplicación que permita simular el juego de cartas del siete y medio. La aplicación deberá operar con varios procesos mediante un modelo cliente/servidor, clientes = jugadores, y servidor = {distribuir las cartas, recoger las decisiones de los jugadores, hasta que se declare un ganador}.

La ejecución de la partida será mediante el comando: iniciar_juego N. N será el número de jugadores que participan en la primera partida. Como resultado de la ejecución, se publica el ganador de la partida, así como una tabla describiendo la situación de cada jugador (cuántos puntos posee, se plantó o abandonó).

El proceso iniciar_juego será el encargado de gestionar la partida, será el que repartirá las cartas por turnos, mantendrá el estado de la partida a partir de las decisiones de los jugadores, y decidirá finalmente el ganador de la partida.

El proceso jugador será el que implementará la lógica del jugador en la partida, de acuerdo a las cartas que reciba del repartidor (iniciar_juego), y de su propio estado (puntos), decidirá si continúa en el juego pidiendo más cartas, se queda ahí, o abandona (porque se pasó). Esta lógica de juego se deja abierta, de forma que se implemente como cada grupo lo decida, pudiendo llegar a ser simplemente aleatoria: según un número aleatorio, el jugador decide plantarse, pedir carta, o abandonar.

Recuerda que la generación de los N procesos jugadores deberá realizarse a través del uso de forks, y la comunicación repartidor/jugador se efectuará mediante pipes.

 

b. Implementa una segunda versión mediante fork y comunicación a través de sockets.

 

Revisa el punto 4, donde te especifico las condiciones del entregable. El punto 2a es de entrega individual. En el caso de que ninguno de tus compañeros de grupo hubiese realizado aporte en el Foro de Discusión Grupal TP3, pero tú sí lo hubieses hecho y realizas esta entrega, corregiré la misma de acuerdo a la rúbrica de evaluación que te comparto en el siguiente punto.

Recuerda que estoy siempre disponible para responder cualquier inquietud. Me tienes a un mensaje de distancia. Te espero por allí y te estaré leyendo en el foro.

4	Formato entregable

Deberás entregar un fichero .zip que contenga el código fuente desarrollado. Se valorará la claridad del código y que esté debidamente comentado. Adicionalmente, se considerará mayor puntaje si se incluye tratamiento correcto de errores, es decir, en caso de producirse errores, deberás informar al usuario del tipo de error ocurrido. Por último, deberás elaborar un breve informe (entrega en PDF) que incluya el trabajo teórico realizado y la resolución/análisis de los ejercicios planteados.
