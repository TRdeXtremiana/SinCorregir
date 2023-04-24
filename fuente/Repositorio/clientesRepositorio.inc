<?php

namespace app\AlquilerCoches\repositorio;

use app\conf\conexiones\core\ConexionBd;

class ClientesRepositorio
{
    public function loginSQL(string $correo, string $contraseña): bool
    {
        $sql = 'SELECT eCorreo, pass
                FROM sesion
                WHERE eCorreo = :correo AND pass = :contraseña';

        require_once __DIR__ . '/../../core/conexionBd.inc';

        try {
            $con = (new ConexionBd())->getConexion();
            $snt = $con->prepare($sql);

            $snt->bindValue(':correo', $correo);
            $snt->bindValue(':contraseña', $contraseña);

            $snt->execute();

            $sesion = $snt->fetch(\PDO::FETCH_ASSOC); //devuelve 1 fila (fetch)

            if (empty($sesion)) {
                return false;
            } else {
                return true;
            }
        } catch (\PDOException $ex) {
            throw $ex;
        } finally {
            unset($snt);
            unset($con);
        }
    }

    public function registrarUsuario(string $nombre, string $apellido, string $tipoDocumento, string $documento, string $domicilio, string $tlfno, string $eCorreo, string $nacionalidad, string $pass): bool
    {
        $sql = 'INSERT INTO sesion (eCorreo,pass)
                VALUES(:eCorreo, :pass)';

        $sqlCliente = 'INSERT INTO cliente(nombre,apellido, tipo, documento, domicilio, tlfno, eCorreo, nacionalidad)
                        VALUES(:nombre, :apellido, :tipo, :documento, :domicilio, :tlfno, :eCorreo, :nacionalidad)';

        require_once __DIR__ . '/../../core/conexionBd.inc';

        try {
            $con = (new ConexionBd())->getConexion();
            $snt = $con->prepare($sql);

            $snt->bindValue(':eCorreo', $eCorreo);
            $snt->bindValue(':pass', $pass);

            if ($snt->execute()) {
                $idUsers = $con->lastInsertId();

                $snt = $con->prepare($sqlCliente);

                $snt->bindValue(':nombre', $nombre);
                $snt->bindValue(':apellido', $apellido);
                $snt->bindValue(':tipo', $tipoDocumento);
                $snt->bindValue(':documento', $documento);
                $snt->bindValue(':domicilio', $domicilio);
                $snt->bindValue(':tlfno', $tlfno);
                $snt->bindValue(':eCorreo', $eCorreo);
                $snt->bindValue(':nacionalidad', $nacionalidad);

                if ($snt->execute()) {
                    return $con->commit();
                }
            }
        } catch (\PDOException $ex) {
            throw $ex;
        } finally {
            unset($snt);
            unset($con);
        }
    }

    public function registrarEmpleado(string $nombre, string $apellido, string $documento, string $SS, string $domicilio, string $tlfno, string $eCorreo, string $cargo, string $pass): bool
    {
        $sql = 'INSERT INTO sesion (eCorreo,pass)
                VALUES(:eCorreo, :pass)';

        $sqlEmpleado = 'INSERT INTO empleado(nombre,apellido, dni, SS, domicilio, tlfno, eCorreo, cargo)
                        VALUES(:nombre, :apellido, :documento, :SS, :domicilio, :tlfno, :eCorreo, :cargo)';

        require_once __DIR__ . '/../../core/conexionBd.inc';

        try {
            $con = (new ConexionBd())->getConexion();
            $snt = $con->prepare($sql);

            $snt->bindValue(':eCorreo', $eCorreo);
            $snt->bindValue(':pass', $pass);

            if ($snt->execute()) {
                $snt = $con->prepare($sqlEmpleado);

                $snt->bindValue(':nombre', $nombre);
                $snt->bindValue(':apellido', $apellido);
                $snt->bindValue(':documento', $documento);
                $snt->bindValue(':SS', $SS);
                $snt->bindValue(':domicilio', $domicilio);
                $snt->bindValue(':tlfno', $tlfno);
                $snt->bindValue(':eCorreo', $eCorreo);
                $snt->bindValue(':cargo', $cargo);

                if ($snt->execute()) {
                    return $con->commit();
                }
            }
        } catch (\PDOException $ex) {
            throw $ex;
        } finally {
            unset($snt);
            unset($con);
        }
    }
}
