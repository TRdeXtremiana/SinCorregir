<?php
//index.php
declare(strict_types=1);
session_start();
error_reporting(E_ALL);

$_SESSION['usuario'] = 'anonimo';

function addFuentes(string $clase): void
{
  if (strpos($clase, 'app\\AlquilerCoches\\') === 0) {
    //die(var_dump($clase));
    $ruta = str_replace('app\\AlquilerCoches\\', '', $clase);
    $ruta = str_replace('\\', '//', $ruta);
    require_once __DIR__ . '/fuente/' . $ruta . '.inc';
  }
}
spl_autoload_register('addfuentes');


function addCores(string $clase): void
{
  if (str_starts_with($clase, 'app\\conf\\conexiones\\')) {
    //die(var_dump($clase));
    $ruta = str_replace('app\\conf\\conexiones', '', $clase);
    $ruta = str_replace('\\', DIRECTORY_SEPARATOR, $ruta);
    require_once __DIR__ . '/' . $ruta . '.inc';
  }
}
spl_autoload_register('addCores');

//TODO namespace configuraciones
// function addCores(string $clase): void
// {
//   if (str_starts_with($clase, 'app\\conf\\conexiones\\')) {
//     //die(var_dump($clase));
//     $ruta = str_replace('app\\conf\\conexiones', '', $clase);
//     $ruta = str_replace('\\', DIRECTORY_SEPARATOR, $ruta);
//     require_once __DIR__ . '/' . $ruta . '.inc';
//   }
// }
// spl_autoload_register('addCores');

// require_once __DIR__ . '/fuente/Controlador/defaultController.inc'; /*controlador */
// require_once __DIR__ . '/fuente/Controlador/formulariosController.inc'; /*controlador */
require_once __DIR__ . '/app/conf/rutas.inc'; /*Ubicación del archivo de rutas*/

// Parseo de la ruta
if (isset($_GET['ctl'])) {
  if (isset($mapeoRutas[$_GET['ctl']])) {
    $ruta = $_GET['ctl'];
  } else {
    header('Status: 404 Not Found');
    echo '<html><body><h1>Error 404: No existe la ruta <i>' .
      $_GET['ctl'] .
      '</p></body></html>';
    exit;
  }
} else {
  $ruta = 'inicio';
}

$controlador = $mapeoRutas[$ruta];
// Ejecución del controlador asociado a la ruta

if (method_exists($controlador['controller'], $controlador['action'])) {
  call_user_func(array(new $controlador['controller'], $controlador['action']));
} else {
  header('Status: 404 Not Found');
  echo '<html><body><h1>Error 404: El controlador <i>' .
    $controlador['controller'] .
    '->' . $controlador['action'] .
    '</i> no existe</h1></body></html>';
}
