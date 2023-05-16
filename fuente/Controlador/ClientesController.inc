<?php

namespace app\AlquilerCoches\controlador;

use app\AlquilerCoches\repositorio\cochesRepositorio;
use app\AlquilerCoches\modelo\UbicacionesAlquiler;
use DateTime;

class clientesController
{
    public function coches()
    {
        $categorias =  (new cochesRepositorio())->allCategorias();
        // $vehiculos =  (new cochesRepositorio())->allVehiculos();
        // $coches =  (new cochesRepositorio())->allCoches();
        $tablaCli = (new cochesRepositorio())->tablaClientes();
        // var_dump($tablaCli);

        if (isset($_POST['okFechas'])) {
            $errores = array();

            if (!isset($_POST['fechaAlquiler'], $_POST['fechaDevolucion']) || empty($_POST['fechaAlquiler']) || empty($_POST['fechaDevolucion'])) {
                $errores['fecha'] = 'Ambas fechas son obligatorias';
            }

            $inicio = strtotime($_POST['fechaAlquiler']);
            $fin = strtotime($_POST['fechaDevolucion']);

            if ($inicio > $fin) {
                $errores['fecha'] = 'La fecha de devolución no puede ser anterior a la de alquiler';
            }

            // var_dump($errores);

            if (empty($errores)) {
                $filtro = (new cochesRepositorio())->cochesDisponibles($inicio, $fin);
                var_dump($filtro);
            }
        }

        if (isset($_POST['okCoche'])) {

            $_SESSION['coche'] = (new cochesRepositorio())->findCoche($_POST['okCoche']);
            // var_dump($_SESSION['coche']);

            header('Location: index.php?ctl=coche');
        }

        if (isset($_POST['okDevolver'])) {
            (new cochesRepositorio())->devolucion($_SESSION['coche']['matricula']);
        }

        require __DIR__ . '/../../app/plantillas/cliente.php';
    }


    public function alquilar() //Coches
    {
        // var_dump($_SESSION['coche']);

        if (isset($_POST['okAlquiler'])) {
            $errores = array();

            if (!isset($_POST['alquilerDiaInicio'], $_POST['alquilerDiaDevolucion']) || empty($_POST['alquilerDiaInicio']) || empty($_POST['alquilerDiaDevolucion'])) {
                $errores['alquilerMin'] = 'Ambas fechas son obligatorias';
            }

            $inicio = strtotime($_POST['alquilerDiaInicio']);
            $fin = strtotime($_POST['alquilerDiaDevolucion']);

            if ($inicio > $fin) {
                $errores['fechaDev'] = 'La fecha de devolución no puede ser anterior a la de alquiler';
            }

            $diferencia = abs($inicio - $fin); // valor absoluto
            $dias = floor($diferencia / (60 * 60 * 24)); // Paso de segundos a días

            if ($dias < 1) {
                $errores['alquilerMin'] = 'El alquiler mínimo es de 1 día';
            }

            if ($_SESSION['coche']['estado'] != 'disponible') {
                $errores['noDisponible'] = 'El coche no está disponible para alquilar';
            }

            if (empty($_POST['ubicaRecogida']) || empty($_POST['ubicaDevolucion'])) {
                $errores['ubicaciones'] = 'Las ubicaciones de recogida y devolución son obligatorias';
            }

            if (empty($errores)) {
                $fechaReserva = (new DateTime());
                $fecha_string = $fechaReserva->format('Y-m-d H:i:s');

                $alquilado = (new cochesRepositorio)->alquiler($_SESSION['coche']['matricula'],  $_SESSION['cliente']['eCorreo'], $_POST['alquilerDiaInicio'], $_POST['alquilerDiaDevolucion'], $fecha_string);

                // Guardar los valores en sesión
                $_SESSION['ubiRecogida'] = $_POST['ubicaRecogida'];
                $_SESSION['fechaRecogida'] = $_POST['alquilerDiaInicio'];
                // $_SESSION['horaRecogida'] = $_POST['horaDiaInicio'];

                $_SESSION['ubiDevolucion'] = $_POST['ubicaDevolucion'];
                $_SESSION['fechaDevolucion'] = $_POST['alquilerDiaDevolucion'];
                // $_SESSION['horaDevolucion'] = $_POST['horaDiaDevolucion'];

                $confirmacion = 'Has alquilado nuestro ' . $_SESSION['coche']['marca'] . ' ' . $_SESSION['coche']['modelo'] . " durante $dias días.";
                // var_dump($alquilado);
            } else {
                $confirmacion = 'No se pudo alquilar el coche, revise los errores e intentelo de nuevo';
                // unset($errores);
            }
        }

        if (isset($_POST['okDevolver'])) {
            if ((new cochesRepositorio())->devolucion($_SESSION['coche']['matricula'])) {
                $texto = "Has devuelto nuestro " . $_SESSION['coche']['marca'] . ' ' . $_SESSION['coche']['modelo'] . " al servicio técnico";
            }
        }

        require __DIR__ . '/../../app/plantillas/coche.php';
    }


    public function compras() //Historial de compras
    {

        $reservados = (new cochesRepositorio())->reservas($_SESSION['cliente']['eCorreo']);

        require __DIR__ . '/../../app/plantillas/historialCompras.php';
    }
}
