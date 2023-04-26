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
}
