Para hacer esta shell se implementaron algunas librerias y funciones.
Primero se inicializa la shell con un dibujo ilustrativo de bienvenida en ascii, el USER y HOSTNAME
Si myshell fue llamada sin argumentos <./myshell>, automaticamente se lanza el prompt con la direccion actual esperando que el usuario ingrese comandos por teclado en un loop while, cada vez que el usuario ingrese un comando, este intentara ejecutarse ya sea por comandos internos implementados mediante codigo o externos mediante execv. Si se pudo ejecutar, se vera la ejecucion, sino un mensaje de error y se pedira nuevamente un comando en el loop while.

Si myshell es llamada con argumentos: ./myshell ejemplo.txt 
Se detecta en el main el argumento extra y se ejecutara otra parte del codigo. Se iniciara la shell como antes pero en vez de esperar por comandos por teclado, se abre el ejemplo.txt y se leen los comandos linea por linea para ser ejecutados de a uno.

Para la parte de comandos internos tenemos el cd, echo, clr y quit. Al ingresar comandos por teclado, estos se leen mediante la funcion readline, y mediante strsep() se separan en un arreglo de strings. Luego se evalua el primer string en busca de alguna coincidencia con los comandos internos y se intentara ejecutar el que corresponda segun los criterios establecidos. En caso de no haber ninguna coincidencia se pasaran los comandos a la parte de comandos externos.

Para la parte de comandos externos se uso execv de la siguiente manera: Ya que se requiere que un argumento del execv sea el Path, lo que hago primero es preguntar si el path fue dado por el usuario en los comandos, como relativo "./" o absoluto con el path completo e intento ejecutar de estas dos maneras. Si no hay un path en los comandos, se busca en la variable de entorno PATH el path que contenga el programa ingresado. Mediante un bucle for intento ejecutar por cada path contenida en la variable hasta tener exito o agotar las direcciones. En este ultimo caso un error se imprime ya que no hay mas alternativas y se vuelve al main.

Esta parte se implemento mediante el metodo fork, es decir, el hijo creado intenta ejecutar el comando y el padre espera mediante wait la ejecucion y terminacion del hijo para limpiarlo. Luego el padre es quien vuelve al main a seguir en el bucle while a pedir mas comandos.

En el caso de que se inserte un '&' al final de los comandos, se habilita una flag de background con la cual los hijos que se crean mediante fork, no son esperados por el padre mediante el metodo wait, sino que se los deja correr en background mientras que el padre vuelve al main a activar el prompt y pedir nuevos comandos.

Para evitar zombies en este ultimo caso, se utilizo la signal de sigchld, de modo que cuando un hijo que fue lanzado en background termine su ejecucion y muera y pueda ser limpiado, el handler del sigchld se encarga de hacer un llamado al wait del ultimo hijo quien mando la signal, mediante este wait logramos limpiar el zombie e imprimimos por pantalla el pid y estado de terminacion del hijo.

Si al lanzar programas en background intentamos cerrar myshell por el comando quit, se implemento una funcion de salida que se encargue de esperar a estos hijos en background y no cerrar la shell hasta que estos hayan terminado y sido limpiados, para evitar dejar zombies en el sistema.

Actualizacion TP6:

Se implementaron las signals de  (SIGINT, SIGTSTP, SIGQUIT) para que sean ignoradas por el proceso main y que sean atendidas por los procesos hijos.



Los pipes son creados mediante el sistema de llamadas pipe(). No tienen una representación física en el sistema de archivos y no tienen atributos de archivos como permisos, propietarios o ubicaciones en el sistema de archivos.

Cuando se crea un pipe, se obtiene un par de descriptores de archivo: uno para lectura (pipefd[0]) y otro para escritura (pipefd[1]). Estos descriptores de archivo se utilizan para enviar datos desde el extremo de escritura del pipe al extremo de lectura del pipe.
Se usa la funcion dup2 para duplicar y cerrar los extremos no utilizados de los file descriptors

En esta implementacion solo se aceptan comandos de hasta 1 pipe (comando 1 | comando 2).

Se implemento la redireccion del STDIN y STDOUT mediante las funciones dup y dup2. El comando echo funciona con esta implementacion.

Bugs & issues:

Se corrijieron la mayoria de errores de crasheo y manipulacion de strings. No se garantiza el correcto funcionamiento segun la entrada por teclado con ingresos erroneos o defectuosos.

La funcionalidad de pipe solo funciona con dos comandos conectados (comando 1 | comando 2)
