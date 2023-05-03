<?php

namespace app\AlquilerCoches\controlador;

use app\AlquilerCoches\repositorio\cochesRepositorio;

class clientesController
{
    public function coches()
    {
        $categorias =  (new cochesRepositorio())->allCategorias();
        $vehiculos =  (new cochesRepositorio())->allVehiculos();
        $coches =  (new cochesRepositorio())->allCoches();

        $tablaCli = (new cochesRepositorio())->tablaClientes();
        // var_dump($tablaCli);

        if (isset($_POST['okCoche'])) {

            $_SESSION['coche'] = (new cochesRepositorio())->findCoche();
            var_dump($_SESSION['coche']);

            // $marca = $_SESSION['coche']['marca'];
            // header('Location: index.php?ctl=coche');
        }

        require __DIR__ . '/../../app/plantillas/cliente.php';
    }

    public function compras()
    {

        require __DIR__ . '/../../app/plantillas/historialCompras.php';
    }

    public function alquilar()
    {

        require __DIR__ . '/../../app/plantillas/coche.php';
    }
}
