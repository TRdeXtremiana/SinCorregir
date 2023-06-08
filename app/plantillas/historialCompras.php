<?php ob_start() ?>
<?php $_SESSION['usuario'] = 'cliente'; ?>
<h1>Historial de compras de <?= $_SESSION['cliente']['nombre'] ?></h1>

<!-- < ?= var_dump($reservados) ?> -->

<table>
    <thead>
        <tr>
            <th>ID reserva</th>
            <th>Foto</th>
            <th>Marca</th>
            <th>Modelo</th>
            <th>Matrícula</th>
            <th>Categoría</th>
            <th>Recogida</th>
            <th>Devolución</th>
            <th>Tiempo total</th>
            <th>Importe total</th>
        </tr>
    </thead>

    <?php foreach ($reservados as $key => $value) : ?>
        <tr>
            <td><?= $value['idReserva'] ?></td>
            <td><img src="web/imagenes/<?= $value['categoria'] ?>/<?= $value['Foto'] ?>.jpg" alt="imagen de un <?= $value['marca'] . ' ' . $value['modelo'] ?>" width="100px"></td>
            <td><?= $value['marca'] ?></td>
            <td><?= $value['modelo'] ?></td>
            <td><?= $value['matricula'] ?></td>
            <td><?= $value['categoria'] ?></td>
            <td>
                <?php
                $recogida = new DateTime($value['Recogida']);
                $recogidaStr = $recogida->format('d/m/Y') . ' a las ' . $_SESSION['horaRecogida'];
                echo $recogidaStr;
                ?>
            </td>
            <td>
                <?php
                $devolucion = new DateTime($value['Devolución']);
                $devolucionStr = $devolucion->format('d/m/Y') . ' a las ' . $_SESSION['horaDevolucion'];
                echo $devolucionStr;
                ?>
            </td>

            <?php
            $inicio = $recogida->getTimestamp();
            $fin = $devolucion->getTimestamp();

            $diferencia = abs($inicio - $fin); // El valor absoluto

            $horas = floor($diferencia / (60 * 60)); // Paso de segundos a horas
            $minutos = floor(($diferencia / 60) % 60); // Coger los minutos
            ?>

            <?php if ($horas >= 24 && $horas % 24 === 0) : ?>
                <?php $dias = $horas / 24 ?>
                <td><?= $dias ?> días</td>
                <td><?= ($value['precio'] * $dias) ?> €</td>
            <?php else : ?>
                <?php if ($minutos != 0) : ?>
                    <td><?= $horas ?>:<?= $minutos ?> horas</td>
                <?php else : ?>
                    <td><?= $horas ?> horas</td>
                <?php endif ?>
                <td><?= number_format(($value['precio'] / 24) * $horas, 2) ?> €</td>
            <?php endif ?>

        </tr>
    <?php endforeach ?>

</table>
<?php $contenido = ob_get_clean() ?>
<?php include 'base.php' ?>