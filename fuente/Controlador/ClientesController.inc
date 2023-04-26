<?php

namespace app\AlquilerCoches\controlador;

use app\AlquilerCoches\repositorio\cochesRepositorio;

class clientesController
{
    public function coches()
    {
        $datos =  (new cochesRepositorio())->allCategorias();
        // var_dump($datos);

        require __DIR__ . '/../../app/plantillas/cliente.php';
    }
}
