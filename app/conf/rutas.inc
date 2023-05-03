<?php

// Vector multidimensional con rutas a controlador y método que debe
// atender cada enlace
/* formato:
    Primera dimensaión: nombre del enlace pasado mediante variable GET 'ctl'
     'nombreEnlace' => array() segunda dimesion con información del controlador
                       que atiende esa petición, clave 'controller', y del
                       método concreto que está especializado en su tratamiento,
                       clave 'action'
  Se debe agregar una ruta por cada valor diferente que tome la variable 'ctl'.
  La clave 'inicio' referencia la página home de la aplicación y especifica
    el controlador que debe decidir cuál es la vista que se debe mostrar
*/
$mapeoRutas =
  array(
    'inicio' => array('controller' => 'app\AlquilerCoches\controlador\DefaultController', 'action' => 'inicio'),

    'login' => array('controller' => 'app\AlquilerCoches\controlador\formulariosController', 'action' => 'login'),
    'logout' => array('controller' => 'app\AlquilerCoches\controlador\formulariosController', 'action' => 'logout'),
    'compras' => array('controller' => 'app\AlquilerCoches\controlador\ClientesController', 'action' => 'compras'),

    'registro' => array('controller' => 'app\AlquilerCoches\controlador\formulariosController', 'action' => 'registroCli'),
    'cliente' => array('controller' => 'app\AlquilerCoches\controlador\ClientesController', 'action' => 'coches'),

    'coche' => array('controller' => 'app\AlquilerCoches\controlador\ClientesController', 'action' => 'alquilar'),
  );
