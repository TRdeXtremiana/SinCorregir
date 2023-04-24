<?php

namespace app\AlquilerCoches\modelo;

use Exception;

/**
 * Gestiona los errores generales de la aplicación
 */
class AppException extends Exception
{
    private array $error;

    public function __construct(array $error, string $mensajeError = null)
    {
        if (!is_null($mensajeError)) {
            parent::__construct($mensajeError);
        }

        $this->error = $error;
    }

    public function getError(): array
    {
        return $this->error;
    }
}
