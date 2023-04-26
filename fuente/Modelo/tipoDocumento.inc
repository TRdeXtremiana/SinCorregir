<?php

namespace app\AlquilerCoches\modelo;

enum tipoDocumento
{
    case DNI;
    case NIE;
    case Pasaporte;

    public static function isTipo(string $tipo): self|bool
    {
        foreach (self::cases() as $status) {
            if ($tipo === $status->name) {
                return $status;
            }
        }
        return false;
    }
}
