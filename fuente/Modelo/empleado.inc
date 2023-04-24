<?php

namespace app\AlquilerCoches\modelo;

class Empleado extends Persona
{
    private string $documento;
    private string $ss;
    private string $cargo;

    public function __construct(string $nombre, string $apellido, string $domicilio, string $tlfno, string $eCorreo, string $pwd, string $rol, string $documento, string $ss, string $cargo)
    {
        try {
            parent::__construct($nombre, $apellido, $domicilio, $tlfno, $eCorreo, $pwd, $rol);
        } catch (AppException $th) {
            $error = $th->getError();
        }

        if (!$this->setDni($documento)) {
            $error["documento"] = "El documento no es válido";
        }

        if (!$this->setSs($ss)) {
            $error["segSoc"] = "El numero de la SS no es válido";
        }

        if (!$this->setCargo($cargo)) {
            $error["cargo"] = "El cargo no es válido";
        }

        if (isset($error)) {
            throw new AppException($error, 'Hay errores en los datos del empleado');
        }
    }

    public function getDni()
    {
        return $this->documento;
    }

    public function setDni($documento)
    {
        $expReg = '/^[0-9]{8}[A-Z]$/';
        $nieRegex = '/^[XYZ][0-9]{7}[TRWAGMYFPDXBNJZSQVHLCKE]$/i';

        if (!preg_match($expReg, $documento) || !preg_match($nieRegex, $documento)) {
            // throw new Exception("El DNI no es válido");
            return false;
        }

        $this->$documento = $documento;
        return true;
    }

    public function getSs()
    {
        return $this->ss;
    }

    public function setSs($ss)
    {
        $expReg = '/^(\d{2})(\d{2})(\d{2})\d{5}$/'; //11 numeros

        if (!preg_match($ss, $expReg)) {
            // throw new Exception("El numero de la SS no es válido");
            return false;
        }

        $this->ss = $ss;
        return $this;
    }

    public function getCargo()
    {
        return $this->cargo;
    }

    public function setCargo($cargo)
    {

        $cargos = array('director', 'responsable', 'gestor', 'gerente');

        if (!in_array($cargo, $cargos)) {
            // throw new Exception("El cargo no es válido");
            return false;
        }

        $this->cargo = $cargo;
        return $this;
    }
}
