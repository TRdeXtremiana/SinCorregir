<?php

namespace app\AlquilerCoches\modelo;

use app\AlquilerCoches\modelo\AppException;

class Persona
{
    private string $nombre;
    private string $apellido;
    private string $domicilio;
    private string $tlfno;
    private string $eCorreo;
    private string $pwd;
    private string $rol;

    public function __construct(string $nombre, string $apellido, string $domicilio, string $tlfno, string $eCorreo, string $pwd, string $rol)
    {

        if (!$this->setNombre($nombre)) {
            $error["nombre"] = "El nombre no es valido";
        }

        if (!$this->setApellido($apellido)) {
            $error["apellido"] = "El apellido no es valido";
        }

        if (!$this->setDomicilio($domicilio)) {
            $error["domicilio"] = "El domicilio no es valido";
        }

        if (!$this->setTlfno($tlfno)) {
            $error["tlfno"] = "El número de teléfono no es valido";
        }

        if (!$this->setECorreo($eCorreo)) {
            $error["eCorreo"] = "El eCorreo no es valido";
        }

        if (!$this->setPwd($pwd)) {
            $error["contraseña"] = "La contraseña no es valida";
        }

        if (!$this->setRol($rol)) {
            $error["rol"] = "Ese rol no es valido";
        }

        if (isset($error)) {
            throw new AppException($error, 'Hay errores en los datos de la persona');
        }
    }

    public function getApellido()
    {
        return $this->apellido;
    }

    public function setApellido($apellido)
    {
        $expReg = '/^[A-ZÁÉÍÓÚÑ][a-záéíóúñ]+(-[A-ZÁÉÍÓÚÑ][a-záéíóúñ]+)?( [A-ZÁÉÍÓÚÑ][a-záéíóúñ]+(-[A-ZÁÉÍÓÚÑ][a-záéíóúñ]+)?){0,3}$/';
        if (!preg_match($expReg, $apellido)) {
            return false;
        }
        $this->apellido = $apellido;
        return true;
    }

    public function getNombre()
    {
        return $this->nombre;
    }

    public function setNombre($nombre)
    {
        $expReg = '/^[A-ZÁÉÍÓÚÑ][a-záéíóúñ]+( [A-ZÁÉÍÓÚÑ][a-záéíóúñ]+){0,3}$/';
        if (!preg_match($expReg, $nombre)) {
            return false;
        }
        $this->nombre = $nombre;
        return true;
    }

    public function getDomicilio()
    {
        return $this->domicilio;
    }

    public function setDomicilio($domicilio)
    {
        $expReg = '/^(calle|carretera|diagonal|paseo|avenida)\\s\\d{2}\\s#\\d{2}-\\d{2}\\s[a-zA-Z\\s]+$/';

        if (!preg_match($expReg, $domicilio)) {
            return false;
        }

        $this->domicilio = $domicilio;
        return $this;
    }

    public function getTlfno()
    {
        return $this->tlfno;
    }

    public function setTlfno($tlfno)
    {
        $expReg = '/^[9|6|7][0-9]{8}$/';
        if (!preg_match($expReg, $tlfno)) {
            return false;
        }

        $this->tlfno = $tlfno;
        return $this;
    }

    public function getECorreo()
    {
        return $this->eCorreo;
    }

    public function setECorreo($eCorreo)
    {
        if (!filter_var($eCorreo, FILTER_VALIDATE_EMAIL)) {
            return false;
        }

        $this->eCorreo = $eCorreo;
    }

    public function getPwd()
    {
        return $this->pwd;
    }

    public function setPwd($pwd)
    {
        $expReg = '/^(?=\w*\d)(?=\w*[A-Z])(?=\w*[a-z])\S{8,16}$/';
        //Entre 8 y 16 caracteres, al menos un dígito, al menos una minúscula y al menos una mayúscula.
        //w3Unpocodet0d0

        if (!preg_match($expReg, $pwd)) {
            return false;
        }

        $this->pwd = password_hash($pwd, PASSWORD_DEFAULT);
        return $this;
    }

    public function getRol()
    {
        return $this->rol;
    }

    public function setRol($rol)
    {
        $roles = ['usuario', 'cliente', 'admin', 'vendedor', 'operario'];
        if (!in_array($roles, $rol)) {
            return false;
        }

        $this->rol = $rol;
        return $this;
    }
}
