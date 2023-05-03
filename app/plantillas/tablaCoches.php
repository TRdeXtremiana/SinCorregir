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
            <tr>
                <td><?= $value['foto'] ?></td>
                <td><?= $value['marca'] ?></td>
                <td><?= $value['modelo'] ?></td>
                <td><?= $value['año'] ?></td>
                <td><?= $value['motor'] ?></td>
                <td><?= $value['matricula'] ?></td>

                <?php if ($value['estado'] == 'disponible') : ?>
                    <td class="disponible"><?= $value['estado'] ?></td>
                <?php else : ?>
                    <td class="noDisponible"><?= $value['estado'] ?></td>
                <?php endif ?>

                <td><input type="submit" value="Más info"></td>
            </tr>
        <?php endforeach ?>
    </tbody>
</table>