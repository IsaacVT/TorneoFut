# README

```
                    .:lccccccccccccccl:.                    
                    'dl......''......ld.                    
                    'd:     .:c.     cd.                    
                    'd:    .,ll,.    cd.                    
                    'd:   .clc:cc'   cd.                    
.,::::::::::::::::::co,   'l:;;;c,   ;oc::::::::::::::::::,.
           ....           .:lllcc.           ....           
            ,:cc,',.    .,;.,ll,';,.   .',',cc:'            
      ..    :dkOkdo;    'ddc;;;:cdo'   .:ddkOxd,   ...      
    .okko. .oOkOl....';ccll:;;;;:llcc;'...'oOkOl. 'dkkl.    
  .'dOOOO; .lOOOo;cxkOkolxOx,..;xOxloOOkdc:dOOO:  cOOOOo..  
.cddo,cOo. .lOOOOkodxc..:O0x,  ,k0O:..ckxdkOOOO:  'xkc;ddd: 
.;c,. :Ol..;dkxxxOkl'   cO0x,..;k0O:   ,dOkxxxko,..ok, .;l, 
     .:ddlddxOd:'ckOo'.'cdOx,  ,kOd:..,dOx:':xOxdoodo;      
       .l0Oddk:   .,:cod::ll'..'ll:cdoc:,.  .ckddOOc.       
     .,cx0kdkx,       ',.          .,.       ;kxdkOx:,.     
    ;kkxkxxxdc.                              .ldxxxxxkx,    
    ,kd,.,xx,                                 .:kd,.;xx'    
     ;dc..,dl.                               .'od'..ld,     
      .cl:'.coc,                           .,co:.,coc.      
 .,,,,,;::;,;:::;,,,,,,,,,,,,,,,,,,,,,,,,,,;:::;;;::;,,,,,. 
.loooooooddooddoooooooooooooooooooooooooooooooooooooooooodl.
```

# Simulador de Torneo de futbol

> *Creado por Isaac Vega, proyecto final para Estructura de datos, Universidad Iberiamericana.*
> 

## Descripción

Se aplicaron temas como pilas, colas, árboles, ordenamiento, busqueda, etc...

La idea de este proyecto es poder “jugar” un torneo de futból. Es decir, nosotros solo nos dedicaremos a “anotar” los goles de cada equipo, el programa hará el resto.

## ¿Como?

Una ves ejecutado el programa.

Dentro de la carpeta listasEquipos, contamos con archivos .fut. Nosotros escogeremos cuál archivo cargar, cada uno de estos archivos contiene un total de 32 equipos ([crear o borrar lista](https://www.notion.so/README-07799a509e2b431ca2bb9a5d872db02b)).

Una ves cargado el archivo, se creara una `pila` con los nombres de cada equipo contenido en el archivo, terminado el proceso, podremos visualizar los equipos cargados.

El comenzar a jugar, el programa usará `cola`, para creará 8 grupos, tomando 4 equipos aleatorios de la `pila` creada, esto generará la tabla de clasificaciones, al término de la creación podremos ver los grupos creados.

Creados los grupos, comenzamos a jugar, colocando la cantidad de goles de cada equipo, en cada uno de los grupos.

Para comenzar el `torneo`, se seleccionan los 2 mejores equipos de cada grupo, para ello, el programa se encargará de ordenar cada uno de los grupos, de mayor a menor.

El término de la etapa clasificatoria, procedemos a jugar el `torneo` , internamente, el programa creará 4 `árboles binarios`, extrayendo los 2 mejores equipos de cada bloque de la `cola`.

Finalizado el proceso, podremos decidir el resultado de cada uno de estos nuevos grupos.

Para los partidos finales, se creará un ultimo `árbol binario`, el cual contendra los finalistas de cada uno de los `árboles` anteriores, de este modo podremos jugar la `gran final`.

Una vez terminado el torneo, se limpiaran los datos de la `cola` y todos los `árboles` creados, permanecerá la `pila` con los equipos, en caso de que se quiera volvera jugar con los mismos equipos, en caso de querer cambiar la lista, se puede hacer en cargar lista.

## Limitaciones / posibles actualizaciones

El programa no puede cargar más de 32 equipos.

Una ves comienza el juego, no se puede regresar al menú principal.

Para los partidos finales, no hay un partido para conseguir el 3er lugar.

## Comandos / extras / bugs

- Crear una nueva lista
    
    Entramos a la opción 1 del menú (Cargar lista de equipos).
    
    Si queremos crear alguna lista nueva, escribiremos el comando `#new_` seguido del nombre de nuestra lista, quedandonos algo como : `#new_equiposFav`. 
    
    Daremos `enter` para comenzar a llenar los datos de la lista.
    
    Una ves hayamos concluido el proceso, volveremos al menú prinicipal. 
    
    Si volvemos a entrar a la opción 1 del menú, podremos observar que nuestra nueva lista, ya se muestra en pantalla y podremos cargala sin problema.
    
- Borrar una lista
    
    Entramos a la opción 1 del menú (Cargar lista de equipos).
    
    Si queremos borrar alguna lista, escribiremos el comando `#delete_` seguido del nombre de la lista, quedandonos algo como : `#delete_equiposFav`.
    
    Daremos `enter` para continuar.
    
    Nos preguntará si queremos borrar o no, y precionaremos la opción deseada.
    
- En ocasiones al cargar la lista, se podrá visualizar algún equipo de manera extraña, pruebe con cargar de nuevo la lista o cerrar y comenzar de nuevo.
- Este juego, está basado en la plantilla :

[https://whimsical.com/torneo-fut-NRKHfFN6FqQgo5jMntAs6h](https://whimsical.com/torneo-fut-NRKHfFN6FqQgo5jMntAs6h)