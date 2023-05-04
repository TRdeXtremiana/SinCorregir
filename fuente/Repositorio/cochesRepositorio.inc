<?php

namespace app\AlquilerCoches\repositorio;

use app\conf\conexiones\core\ConexionBd;

class cochesRepositorio
{

    public function allCategorias(): array
    {
        $sql = 'SELECT nombre, descr
                FROM categoria';

        require_once __DIR__ . '/../../core/conexionBd.inc';

        try {
            $con = (new ConexionBd())->getConexion();
            $snt = $con->prepare($sql);

            $snt->execute();

            $categorias = $snt->fetchAll(\PDO::FETCH_ASSOC);
            return $categorias;
        } catch (\PDOException $ex) {
            throw $ex;
        } finally {
            unset($snt);
            unset($con);
        }
    }

    public function allVehiculos(): array
    {
        $sql = 'SELECT *
                FROM vehiculo';

        require_once __DIR__ . '/../../core/conexionBd.inc';

        try {
            $con = (new ConexionBd())->getConexion();
            $snt = $con->prepare($sql);

            $snt->execute();

            $vehiculos = $snt->fetchAll(\PDO::FETCH_ASSOC);
            return $vehiculos;
        } catch (\PDOException $ex) {
            throw $ex;
        } finally {
            unset($snt);
            unset($con);
        }
    }

    public function allCoches(): array
    {
        $sql = 'SELECT *
                FROM coche';

        require_once __DIR__ . '/../../core/conexionBd.inc';

        try {
            $con = (new ConexionBd())->getConexion();
            $snt = $con->prepare($sql);

            $snt->execute();

            $coches = $snt->fetchAll(\PDO::FETCH_ASSOC);
            return $coches;
        } catch (\PDOException $ex) {
            throw $ex;
        } finally {
            unset($snt);
            unset($con);
        }
    }

    public function tablaClientes(): array
    {
        $sql = 'SELECT cat.nombre as categoria, v.marca, v.modelo, v.año, v.motor, v.foto, c.precio, c.matricula, c.kilometros, c.estado
                FROM vehiculo v
                INNER JOIN coche c ON c.idVehiculo = v.idVehiculo
                INNER JOIN categoria cat ON cat.idCategoria = v.idCategoria';

        require_once __DIR__ . '/../../core/conexionBd.inc';

        try {
            $con = (new ConexionBd())->getConexion();
            $snt = $con->prepare($sql);

            $snt->execute();

            $coches = $snt->fetchAll(\PDO::FETCH_ASSOC);
            return $coches;
        } catch (\PDOException $ex) {
            throw $ex;
        } finally {
            unset($snt);
            unset($con);
        }
    }

    public function findCoche(string $matricula): array
    {
        $sql = 'SELECT cat.nombre, cat.descr , v.marca, v.modelo, v.año, v.motor, v.foto, c.precio, c.matricula, c.kilometros, c.estado
                FROM vehiculo v
                INNER JOIN coche c ON c.idVehiculo = v.idVehiculo
                INNER JOIN categoria cat ON cat.idCategoria = v.idCategoria
                WHERE c.matricula = :matricula ';

        require_once __DIR__ . '/../../core/conexionBd.inc';

        try {
            $con = (new ConexionBd())->getConexion();
            $snt = $con->prepare($sql);

            $snt->bindValue(':matricula', $matricula);
            $snt->execute();

            $coches = $snt->fetch(\PDO::FETCH_ASSOC);
            return $coches;
        } catch (\PDOException $ex) {
            throw $ex;
        } finally {
            unset($snt);
            unset($con);
        }
    }
}
