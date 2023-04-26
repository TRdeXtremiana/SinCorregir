<?php

namespace app\AlquilerCoches\modelo;

enum Nacionalidades
{
    case Argentina;
    case Braseleña;
    case Colombiana;
    case Española;
    case Francesa;
    case Italiana;
    case Mexicana;
    case Portuguesa;
    case Inglesa;
    case Estadounidense;
    case China;
    case Japonesa;
    case Andorrana;


    public static function isNacionalidad(string $nacionalidad): self|bool
    {
        foreach (self::cases() as $status) {
            if ($nacionalidad === $status->name) {
                return $status;
            }
        }
        return false;
    }
}
