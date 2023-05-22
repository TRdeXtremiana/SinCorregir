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
            <td><img src="web\imagenes\<?= $value['categoria'] ?>\<?= $value['Foto'] ?>.jpg" alt="imagen de un <?= $value['marca'] . ' ' . $value['modelo'] ?>" width="100px"></td>
            <td><?= $value['marca'] ?></td>
            <td><?= $value['modelo'] ?></td>
            <td><?= $value['matricula'] ?></td>
            <td><?= $value['categoria'] ?></td>
            <td><?= $recog = (new DateTime($value['Recogida']))->format('d/m/Y') ?> a las <?= $_SESSION['horaRecogida'] ?></td>
            <td><?= $devol = (new DateTime($value['Devolución']))->format('d/m/Y') ?>a las <?= $_SESSION['horaDevolucion'] ?></td>

            <?php
            $inicio = strtotime((new DateTime($value['Recogida'] . ' ' . $_SESSION['horaRecogida']))->format('Y-m-d H:i'));
            $fin = strtotime((new DateTime($value['Devolución'] . ' ' . $_SESSION['horaDevolucion']))->format('Y-m-d H:i'));

            $diferencia = abs($inicio - $fin); // valor absoluto

            $horas = array();
            $horas[$value['matricula']] = floor($diferencia / (60 * 60)); // Paso de segundos a horas

            $minutos = array();
            $minutos[$value['matricula']] = floor(($diferencia / 60) % 60); // Obtener los minutos restantes
            ?>

            <?php if ($horas[$value['matricula']] >= 24 && $horas[$value['matricula']] % 24 === 0) : ?>
                <?php $dias = $horas[$value['matricula']] / 24 ?>
                <td><?= $dias ?> días</td>
                <td><?= ($value['precio'] * $dias) ?> €</td>
            <?php else : ?>
                <?php if ($minutos[$value['matricula']] != 0) : ?>
                    <td><?= $horas[$value['matricula']] ?>:<?= $minutos[$value['matricula']] ?> horas</td>
                <?php else : ?>
                    <td><?= $horas[$value['matricula']] ?> horas</td>
                <?php endif ?>
                <td><?= number_format(($value['precio'] / 24) * $horas[$value['matricula']], 2) ?> €</td>
            <?php endif ?>


        </tr>
    <?php endforeach ?>
</table>
<?php $contenido = ob_get_clean() ?>
<?php include 'base.php' ?>