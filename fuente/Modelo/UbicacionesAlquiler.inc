<?php
namespace app\AlquilerCoches\modelo;

enum UbicacionesAlquiler {
   case Logroño;
   case Calahorra;
   case Arnedo;
   case Haro;
   case Nájera;


public static function laRioja(string $ubicacion): self|bool
{
    foreach (self::cases() as $status) {
        if ($ubicacion === $status->name) {
            return $status;
        }
    }
    return false;
}}