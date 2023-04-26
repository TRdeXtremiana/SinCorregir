<?php
ob_start() ?>
<?php $_SESSION['usuario'] = 'cliente'; ?>

<h1>Bienvenido, <?= $_SESSION['nombre'] ?></h1>

<table>
    <thead>
        <tr>
            <th>Categoría</th>
            <th>Descripcion</th>
        </tr>
    </thead>

    <tbody>
        <?php foreach ($datos as $key => $value) : ?>
            <tr>
                <td><?= $value['nombre'] ?></td> <!-- enlaces a los coches dentro de cada categoria-->
                <td><?= $value['descr'] ?></td>
            </tr>
        <?php endforeach ?>
    </tbody>
</table>

<?php $contenido = ob_get_clean() ?>
<?php include 'base.php' ?>