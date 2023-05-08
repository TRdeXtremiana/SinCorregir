<?php ob_start() ?>
<?php $_SESSION['usuario'] = 'cliente'; ?>
<h1>Historial de compras de <?= $_SESSION['cliente']['nombre'] ?></h1>

<?= var_dump($reservados) ?>

<table>
    <thead>
        <tr>
            <th></th>
            <th></th>
            <th></th>
            <th></th>
            <th></th>
            <th></th>
            <th></th>
            <th></th>
            <th></th>
        </tr>
    </thead>
    <?php foreach ($reservados as $key => $value) : ?>
        <tr>
            <td><?= $value['']?></td>
            <td><?= $value['']?></td>
            <td><?= $value['']?></td>
            <td><?= $value['']?></td>
            <td><?= $value['']?></td>
            <td><?= $value['']?></td>
            <td><?= $value['']?></td>
            <td><?= $value['']?></td>
            <td><?= $value['']?></td>
        </tr>
    <?php endforeach ?>
</table>
<?php $contenido = ob_get_clean() ?>
<?php include 'base.php' ?>