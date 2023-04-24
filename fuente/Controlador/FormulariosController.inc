<?php
// Ejemplo de controlador para página home de la aplicación
namespace app\AlquilerCoches\controlador;

use app\AlquilerCoches\modelo\Cliente;
use app\AlquilerCoches\repositorio\ClientesRepositorio;

class formulariosController
{
    public function login()
    {
        if (isset($_POST['loginOK'])) {
            // $email = $_POST['eCorreo'];
            // $pass = $_POST['password'];
            $sesion = (new ClientesRepositorio())->loginSQL($_POST['eCorreo'], $_POST['password']);
            if ($sesion !== false) {
                if (password_verify($_POST['password'], $sesion['pass'])) {

                    $_SESSION['usuario'] =
                        'cliente';
                    require_once __DIR__ . '/../../app/plantillas/cliente.php';
                }
            }
        }
        require __DIR__ . '/../../app/plantillas/login.php';
    }

    public function registroCli()
    {
        require __DIR__ . '/../../app/plantillas/registroCli.php';

        if (isset($_POST['registroOK'])) {

            $nombre = $_POST['nombre'];
            $apellido = $_POST['apellidos'];
            $domicilio = $_POST['ciudad'] . $_POST['tipo_via'] . ' ' . $_POST['domicilio'];
            $tlfno = $_POST['telefono'];
            $eCorreo = $_POST['email'];
            $tipoDocumento = $_POST['tipo'];
            $documento = $_POST['documento'];
            $nacionalidad = $_POST['nacionalidad'];
            $pass = $_POST['password'];

            $cliente = new Cliente($nombre, $apellido, $domicilio, $tlfno, $eCorreo, $pass, $rol, $documento, $tipoDocumento, $nacionalidad);
            (new ClientesRepositorio())->registrarUsuario($nombre, $apellido, $tipoDocumento, $documento, $domicilio, $tlfno, $eCorreo, $nacionalidad, $pass);
        }
    }
}
