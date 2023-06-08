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
        // $tablaCli = (new cochesRepositorio())->tablaClientes();
        // var_dump($tablaCli);

        if (isset($_POST['okFechas'])) {
            $errores = array();

            if (!isset($_POST['fechaAlquiler'], $_POST['fechaDevolucion']) || empty($_POST['fechaAlquiler']) || empty($_POST['fechaDevolucion'])) {
                $errores['fecha'] = 'Ambas fechas son obligatorias';
            }

            if ($_POST['fechaAlquiler'] > $_POST['fechaDevolucion']) {
                $errores['fecha'] = 'La fecha de devolución no puede ser anterior a la de alquiler';
            }

            // var_dump($errores);

            if (empty($errores)) {
                // var_dump($_POST['fechaAlquiler']);
                // var_dump($_POST['fechaDevolucion']);

                $_SESSION['fInicio'] = $_POST['fechaAlquiler'];
                $_SESSION['fFin'] = $_POST['fechaDevolucion'];
                $filtro = (new cochesRepositorio())->cochesDisponibles($_POST['fechaAlquiler'], $_POST['fechaDevolucion']);
            }
        }

        if (isset($_POST['ok'])) { //Separar de este controlador
            var_dump($_POST);

            $_SESSION['coche'] = (new cochesRepositorio())->findCoche($_POST['ok']);
            var_dump($_SESSION['coche']);

            header('Location: index.php?ctl=coche');
        }

        if (isset($_POST['okDevolver'])) {
            (new cochesRepositorio())->devolucion($_SESSION['coche']['matricula']);
        }


        require __DIR__ . '/../../app/plantillas/cliente.php';
    }


    public function reservar() //Coches
    {
        // var_dump($_SESSION['coche']);

        if (isset($_POST['okAlquiler'])) {
            $errores = array();

            $inicio = strtotime($_SESSION['fInicio']);
            $fin = strtotime($_SESSION['fFin']);

            $diferencia = abs($inicio - $fin); // valor absoluto
            $dias = floor($diferencia / (60 * 60)); // Paso de segundos a horas

            if ($dias < 1) {
                $errores['alquilerMin'] = 'El alquiler mínimo es de 1 hora';
            }

            if ($_SESSION['coche']['estado'] != 'disponible') {
                $errores['noDisponible'] = 'El coche no está disponible para alquilar';
            }

            if (empty($_POST['ubicaRecogida']) || empty($_POST['ubicaDevolucion'])) {
                $errores['ubicaciones'] = 'Las ubicaciones de recogida y devolución son obligatorias';
            }

            if (empty($errores)) {
                $fechaReserva = (new DateTime());
                $fecha_string = $fechaReserva->format('Y-m-d');

                // Guardar los valores en sesión
                $_SESSION['ubiRecogida'] = $_POST['ubicaRecogida'];
                $_SESSION['horaRecogida'] = $_POST['horaDiaInicio'];

                $_SESSION['ubiDevolucion'] = $_POST['ubicaDevolucion'];
                $_SESSION['horaDevolucion'] = $_POST['horaDiaDevolucion'];

                $_SESSION['fInicio'] = $_SESSION['fInicio'] . ' ' . $_POST['horaDiaInicio'];
                $_SESSION['fFin'] = $_SESSION['fFin'] . ' ' . $_POST['horaDiaDevolucion'];
                var_dump($_SESSION['coche']);
                $alquilado = (new cochesRepositorio)->reserva($_SESSION['coche']['matricula'], $_SESSION['cliente']['eCorreo'], $_SESSION['fInicio'], $_SESSION['fFin'], $fecha_string);

                $confirmacion = 'Has alquilado nuestro ' . $_SESSION['coche']['marca'] . ' ' . $_SESSION['coche']['modelo'] . " durante $dias días.";
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
