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

Bugs & issues:
Al comprobar el comando interno "cd" sin argumentos mediante la funcion strcmp, obtenia un segmentation fault. Esto se tuvo que resolver hardcodeando, preguntando por este caso en especifico y salvandolo colocando un string vacio " " luego del comando cd.

Al lanzar un hijo en background, se hace un sleep(1) por el padre, para demorar la salida en pantalla del prompt y que no se solapen con salidas de los hijos ejecutandose en background, sin embargo si el hijo continua imprimiendo por pantalla probablemente se solapen con el prompt del padre, dejando un poco incomodo a la vista al prompt.