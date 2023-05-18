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
            <td><?= $recog = (new DateTime($value['Recogida']))->format('d/m/Y') ?></td>
            <td><?= $devol = (new DateTime($value['Devolución']))->format('d/m/Y') ?></td>

            <?php
            $inicio = strtotime((new DateTime($value['Recogida']))->format('Y-m-d'));
            $fin = strtotime((new DateTime($value['Devolución']))->format('Y-m-d'));

            $diferencia = abs($inicio - $fin); // valor absoluto
            $dias = floor($diferencia / (60 * 60 * 24)); // Paso de segundos a días

            //Calcular horas
            ?>

            <td><?= $dias ?> dias</td>
            <td><?= $value['precio'] * $dias ?> €</td>
        </tr>
    <?php endforeach ?>
</table>
<?php $contenido = ob_get_clean() ?>
<?php include 'base.php' ?>