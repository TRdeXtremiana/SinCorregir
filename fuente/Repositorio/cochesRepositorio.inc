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

    public function cochesDisponibles(string $fInicio, string $fFin): array
    {   //die(var_dump($fInicio, $fFin));
        $sql = "SELECT cat.nombre AS categoria, v.marca, v.modelo, v.año, v.motor, v.foto, c.precio, c.matricula, c.estado
                FROM vehiculo v
                INNER JOIN coche c ON c.idVehiculo = v.idVehiculo
                INNER JOIN categoria cat ON cat.idCategoria = v.idCategoria
                WHERE c.estado = 'disponible'
                AND c.matricula NOT IN (
                    SELECT matricula 
                    FROM reserva r1
                    WHERE r1.fInicio <= :fFinal
                        AND r1.fFin >= :fIni
                )
                AND c.matricula NOT IN (
                    SELECT matricula
                    FROM alquiler a
                    WHERE a.fInicio <= :fFin
                        AND a.fFin >= :fInicio
                        AND a.idReserva IS NOT NULL
                )";

        require_once __DIR__ . '/../../core/conexionBd.inc';

        try {
            $con = (new ConexionBd())->getConexion();
            $snt = $con->prepare($sql);

            $snt->bindValue(':fIni', $fInicio);
            $snt->bindValue(':fFinal', $fFin);

            $snt->bindValue(':fInicio', $fInicio);
            $snt->bindValue(':fFin', $fFin);

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
        $sql = "SELECT cat.nombre as categoria, v.marca, v.modelo, v.año, v.motor, v.foto, c.precio, c.matricula, c.kilometros, c.estado
        FROM vehiculo v
        INNER JOIN coche c ON c.idVehiculo = v.idVehiculo
        INNER JOIN categoria cat ON cat.idCategoria = v.idCategoria
        WHERE c.estado = 'disponible'";

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
        $sql = 'SELECT cat.nombre as categoria, cat.descr , v.marca, v.modelo, v.año, v.motor, v.foto, c.precio, c.matricula, c.kilometros, c.estado
                FROM vehiculo v
                INNER JOIN coche c ON c.idVehiculo = v.idVehiculo
                INNER JOIN categoria cat ON cat.idCategoria = v.idCategoria
                WHERE c.matricula = :matricula';

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

    public function reserva(string $matricula, string $eCorreo, string $fInicio, string $fFin, string $fReserva): bool
    {
        $sql = "UPDATE coche
                    SET estado = 'reservado'
                    WHERE matricula = :matricula";

        $sql2 = "SELECT idcliente
                    FROM cliente
                    WHERE eCorreo = :eCorreo";

        $sql3 = "INSERT INTO reserva (idCliente, matricula, fInicio, fFin, fReserva)
                    VALUES(:idCli, :matricula, :fInicio, :fFin, :fReserva)";

        $sql4 = "SELECT precio
                    FROM coche
                    WHERE matricula = :matricula";

        $sql5 = "SELECT idReserva
                    FROM reserva
                    WHERE idCliente = :idCli AND matricula = :matricula AND fInicio=:fInicio";

        $sql6 = "INSERT INTO alquiler(idCliente, matricula, idReserva, fInicio, fFin, importe,atendidoPor)
                    VALUES(:idCli, :matricula, :idReserva, :fInicio, :fFin, :importe, :atendidoPor)";

        require_once __DIR__ . '/../../core/conexionBd.inc';

        try {
            $con = (new ConexionBd())->getConexion();
            $snt = $con->prepare($sql);

            $snt->bindValue(':matricula', $matricula);
            if ($snt->execute()) {
                $snt = $con->prepare($sql2);

                $snt->bindValue(':eCorreo', $eCorreo);
                if ($snt->execute()) {
                    $idCli = $snt->fetchColumn();

                    $snt = $con->prepare($sql3);

                    $snt->bindValue(':idCli', $idCli);
                    $snt->bindValue(':matricula', $matricula);
                    $snt->bindValue(':fInicio', $fInicio);
                    $snt->bindValue(':fFin', $fFin);
                    $snt->bindValue(':fReserva', $fReserva);

                    if ($snt->execute()) {
                        $snt = $con->prepare($sql4);

                        $snt->bindValue(':matricula', $matricula);

                        if ($snt->execute()) {
                            $importe = $snt->fetchColumn();

                            $snt = $con->prepare($sql5);

                            $snt->bindValue(':idCli', $idCli);
                            $snt->bindValue(':matricula', $matricula);
                            $snt->bindValue(':fInicio', $fInicio);

                            if ($snt->execute()) {
                                $idReserva = $snt->fetchColumn();

                                $snt = $con->prepare($sql6);

                                $snt->bindValue(':idCli', $idCli);
                                $snt->bindValue(':matricula', $matricula);
                                $snt->bindValue(':idReserva', $idReserva);
                                $snt->bindValue(':fInicio', $fInicio);
                                $snt->bindValue(':fFin', $fFin);
                                $snt->bindValue(':importe', $importe);
                                $snt->bindValue(':atendidoPor', 3); //Hay que hacer vendedores

                                if ($snt->execute()) {
                                    return true;
                                }
                            }
                        }
                    }
                }
            }
            return false;
        } catch (\PDOException $ex) {
            throw $ex;
        } finally {
            unset($snt);
            unset($con);
        }
    }


    public function devolucion(string $matricula): bool
    {
        $sql = "UPDATE coche
                SET estado = 'disponible'
                WHERE matricula = :matricula";

        require_once __DIR__ . '/../../core/conexionBd.inc';

        try {
            $con = (new ConexionBd())->getConexion();
            $snt = $con->prepare($sql);

            $snt->bindValue(':matricula', $matricula);
            $snt->execute();

            return true;
        } catch (\PDOException $ex) {
            throw $ex;
        } finally {
            unset($snt);
            unset($con);
        }
    }

    public function reservas(string $eCorreo): array | false
    {
        $sql = 'SELECT idcliente
                FROM cliente
                WHERE eCorreo = :eCorreo';

        $sql2 = 'SELECT alq.idReserva, v.Foto, cat.nombre AS categoria, v.marca, v.modelo, c.matricula, c.precio, r.fInicio AS Recogida, r.fFin AS Devolución
                 FROM reserva r
                 INNER JOIN coche c ON r.matricula=c.matricula
                 INNER JOIN cliente cli ON r.idCliente = cli.idCliente
                 INNER JOIN vehiculo v ON c.idVehiculo = v.idVehiculo
                 INNER JOIN categoria cat ON v.idCategoria = cat.idCategoria
                 INNER JOIN alquiler alq ON c.matricula = alq.matricula
                 WHERE r.idCliente = :idCli';

        require_once __DIR__ . '/../../core/conexionBd.inc';

        try {
            $con = (new ConexionBd())->getConexion();
            $snt = $con->prepare($sql);

            $snt->bindValue(':eCorreo', $eCorreo);
            if ($snt->execute()) {
                $idCli = $snt->fetch(\PDO::FETCH_COLUMN);

                $snt = $con->prepare($sql2);
                $snt->bindValue(':idCli', $idCli);
                $snt->execute();

                return $snt->fetchAll(\PDO::FETCH_ASSOC);
            }
            return false;
        } catch (\PDOException $ex) {
            throw $ex;
        } finally {
            unset($snt);
            unset($con);
        }
    }
}
