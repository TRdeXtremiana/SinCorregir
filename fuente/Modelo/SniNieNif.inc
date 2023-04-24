<?php

namespace app\AlquilerCoches\modelo;

require_once 'AppException.inc';
class SniNieNif
{
    private string $identificador;
    private string $tipo;
    private int $numero;
    private string $charControl;
    private ?string $letraNie = null;

    private function __construct(string $id)
    {
        $id = strtoupper($id);
        $num = -1;
        $control = '';
        $expRegDNI = '/^[0-9]{8}[A-Z]$/';
        $expRegNIE = '/^[XYZ][0-9]{7}[TRWAGMYFPDXBNJZSQVHLCKE]$/i';
    }
}
