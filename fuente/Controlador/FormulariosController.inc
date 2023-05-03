<?php
// Ejemplo de controlador para página home de la aplicación
namespace app\AlquilerCoches\controlador;

use app\AlquilerCoches\modelo\AppException;
use app\AlquilerCoches\modelo\Cliente;
use app\AlquilerCoches\modelo\Nacionalidades;
use app\AlquilerCoches\modelo\tipoDocumento;
use app\AlquilerCoches\repositorio\ClientesRepositorio;

class formulariosController
{
    public function login()
    {
        if (isset($_POST['loginOK'])) {
            // $email = $_POST['eCorreo'];
            // $pass = $_POST['password'];
            $sesion = (new ClientesRepositorio())->loginSQL($_POST['eCorreo']);

            if ($sesion !== false) {
                if (password_verify($_POST['password'], $sesion['pass'])) {

                    $datos =  (new ClientesRepositorio())->datosCliente($_POST['eCorreo']);
                    $_SESSION['nombre'] = $datos['nombre'];
                    $_SESSION['apellido'] = $datos['apellido'];
                    $_SESSION['tlfno'] = $datos['tlfno'];

                    //var_dump($datos);
                    // var_dump($_SESSION['nombre']);
                    header('Location: index.php?ctl=cliente');
                    return;
                }
            }
        }
        require __DIR__ . '/../../app/plantillas/login.php';
    }

    public function registroCli()
    {

        $nacionalidades = nacionalidades::cases();
        $tipos = tipoDocumento::cases();

        if (isset($_POST['registroOK'])) {

            $nombre = $_POST['nombre'];
            $apellido = $_POST['apellidos'];
            $domicilio = $_POST['tipo_via'] . ' ' . $_POST['domicilio'] . ' ' . $_POST['ciudad'];
            $tlfno = $_POST['telefono'];
            $eCorreo = $_POST['email'];
            $tipoDocumento = $_POST['tipo'];
            $documento = $_POST['documento'];
            $nacionalidad = $_POST['nacionalidad'];
            $pass = $_POST['password'];

            try {
                $cliente = new Cliente($nombre, $apellido, $domicilio, $tlfno, $eCorreo, $pass, $documento, tipoDocumento::isTipo($tipoDocumento), Nacionalidades::isNacionalidad($nacionalidad));
                (new ClientesRepositorio())->registrarUsuario($nombre, $apellido, $tipoDocumento, $documento, $domicilio, $tlfno, $eCorreo, $nacionalidad, password_hash($pass, PASSWORD_DEFAULT));

                header('Location: index.php?ctl=inicio');
            } catch (AppException $ex) {
                $erroresUsuario = $ex->getError();
                var_dump($erroresUsuario);
                var_dump($_POST);
            }
        }
        require __DIR__ . '/../../app/plantillas/registroCli.php';
    }

    public function logout()
    {
        $_SESSION['usuario'] = 'anonimo';

        unset($_SESSION['nombre']);
        unset($_SESSION['apellido']);
        unset($_SESSION['tlfno']);
        unset($_SESSION['eCorreo']);

        session_destroy();
        header('Location: index.php?ctl=inicio');
    }
}
