<?php

namespace app\AlquilerCoches\controlador;

use app\AlquilerCoches\repositorio\cochesRepositorio;

class clientesController
{
    public function coches()
    {
        $categorias =  (new cochesRepositorio())->allCategorias();
        // $vehiculos =  (new cochesRepositorio())->allVehiculos();
        // $coches =  (new cochesRepositorio())->allCoches();
        $tablaCli = (new cochesRepositorio())->tablaClientes();
        // var_dump($tablaCli);

        if (isset($_POST['okCoche'])) {

            $_SESSION['coche'] = (new cochesRepositorio())->findCoche($_POST['okCoche']);
            // var_dump($_SESSION['coche']);

            header('Location: index.php?ctl=coche');
        }

        require __DIR__ . '/../../app/plantillas/cliente.php';
    }


    public function alquilar() //Coches
    {
        var_dump($_SESSION['coche']);

        if (isset($_POST['okAlquiler'])) {
            $inicio = $_POST['alquilerDiaInicio'];
            $devolucion = $_POST['alquilerDiaDevolucion'];

            $timestamp1 = strtotime($inicio);
            $timestamp2 = strtotime($devolucion);

            $diferencia = abs($timestamp2 - $timestamp1);
            $dias = floor($diferencia / (60 * 60 * 24));

            $texto = "$dias dias";

        }

        require __DIR__ . '/../../app/plantillas/coche.php';
    }


    public function compras() //Historial de compras
    {
        require __DIR__ . '/../../app/plantillas/historialCompras.php';
    }
}
