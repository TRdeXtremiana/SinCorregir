<?php

namespace app\AlquilerCoches\modelo;

use app\AlquilerCoches\modelo\nacionalidades;
use app\AlquilerCoches\modelo\tipoDocumento;

class Cliente extends Persona

{
    private int $idCliente;
    private string $documento;
    private tipoDocumento $tipo;
    private string $nacionalidad;

    public function __construct(string $nombre, string $apellido, string $domicilio, string $tlfno, string $eCorreo, string $pwd, string $rol = 'cliente', string $documento, string $tipo, string $nacionalidad)
    {
        try {
            parent::__construct($nombre, $apellido, $domicilio, $tlfno, $eCorreo, $pwd, $rol);
        } catch (AppException $th) {
            $error = $th->getError();
        }

        // if (!$this->setIdCliente($idCliente)) {
        //     $error = "La id del cliente no es válida";
        // }

        if (!$this->setDocumento($documento)) {
            $error["documento"] = "El documento no es válido";
        }

        if (!$this->setTipo($tipo)) {
            $error["tipoDocumento"] = "El tipo de documento no es válido";
        }

        if (!$this->setNacionalidad($nacionalidad)) {
            $error["nacionalidad"] = "La nacionalidad no es válida";
        }

        if (isset($error)) {
            throw new AppException($error, 'Hay errores en los datos del cliente');
        }
    }

    public function getIdCliente()
    {
        return $this->idCliente;
    }

    public function setIdCliente($idCliente)
    {
        $this->idCliente = $idCliente;
        return $this;
    }

    public function getDocumento()
    {
        return $this->documento;
    }

    public function setDocumento($documento)
    {
        $dniRegex = '/^[0-9]{8}[A-Z]$/';
        $nieRegex = '/^[XYZ][0-9]{7}[TRWAGMYFPDXBNJZSQVHLCKE]$/i';

        if (!preg_match($dniRegex, $documento) || !preg_match($nieRegex, $documento)) {
            // throw new Exception("El documento no es válido");
            return false;
        }

        $this->$documento = $documento;
        return true;
    }

    public function getTipo(): tipoDocumento
    {
        return $this->tipo;
    }

    public function setTipo($tipo): bool
    {
        switch ($tipo) {
            case 'DNI':
                $this->tipo = tipoDocumento::DNI;
                break;

            case 'NIE':
                $this->tipo = tipoDocumento::NIE;
                break;

            case 'Pasaporte':
                $this->tipo = tipoDocumento::Pasaporte;
                break;
        }

        return true;
    }

    public function getNacionalidad()
    {
        return $this->nacionalidad;
    }

    public function setNacionalidad($nacionalidad)
    {
        if (!in_array($nacionalidad, Nacionalidades::cases())) {
            // throw new Exception("La nacionalidad no es válida");
            return false;
        }

        $this->nacionalidad = $nacionalidad;
        return $this;
    }
}
