<?php
ob_start() ?>
<?php $_SESSION['usuario'] = 'cliente'; ?>

<h1>Bienvenido, <?= $_SESSION['nombre'] ?></h1>

<form action="" method="post">
    <?php foreach ($categorias as $key => $valor) : ?>
        <div class="categoria">
            <h2><?= $valor['nombre'] ?></h2>
            <p><?= $valor['descr'] ?></p>

            <table>
                <thead>
                    <tr>
                        <th>Foto</th>
                        <th>Marca</th>
                        <th>Modelo</th>
                        <th>Año</th>
                        <th>Motor</th>
                        <th>Matricula</th>
                        <th>Estado</th>
                        <th></th>
                    </tr>
                </thead>

                <tbody>
                    <?php foreach ($tablaCli as $key => $value) : ?>
                        <?php if ($value['categoria'] === $valor['nombre']) : ?>
                            <tr>
                                <td><?= $value['foto'] ?></td>
                                <td><?= $value['marca'] ?></td>
                                <td><?= $value['modelo'] ?></td>
                                <td><?= $value['año'] ?></td>
                                <td><?= $value['motor'] ?></td>
                                <td><?= $value['matricula'] ?></td>

                                <?php if ($value['estado'] === 'disponible') : ?>
                                    <td class="disponible"><?= $value['estado'] ?></td>
                                <?php else : ?>
                                    <td class="noDisponible"><?= $value['estado'] ?></td>
                                <?php endif ?>

                                <td><input type="submit" value="Más info" name="okCoche" id="<?= $value['matricula'] ?>"></td>
                            </tr>
                        <?php endif ?>
                    <?php endforeach ?>
                </tbody>
            </table>
        </div>
    <?php endforeach ?>
</form>

<?php $contenido = ob_get_clean() ?>
<?php include 'base.php' ?>