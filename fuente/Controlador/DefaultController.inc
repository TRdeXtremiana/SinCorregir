<?php
// Ejemplo de controlador para página home de la aplicación
namespace app\AlquilerCoches\controlador;

class DefaultController
{
  public function inicio()
  {
    require __DIR__ . '/../../app/plantillas/inicio.php';
  }
}
