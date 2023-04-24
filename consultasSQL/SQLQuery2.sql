use alquilerVehiculos;
go 

-- DROP TABLE categoria;
-- DROP TABLE vehiculo;
-- DROP TABLE coche;
-- DROP TABLE sesion;
-- DROP TABLE cliente;
-- DROP TABLE empleado;
-- DROP TABLE reserva;
-- DROP TABLE alquiler;
-- DROP TABLE caja;
-- go

create table categoria
(	idCategoria INT IDENTITY not null,
	nombre VARCHAR(20) not null,
	descr VARCHAR(1000) not null,

	CONSTRAINT PkCategoria
		PRIMARY KEY (idCategoria),
);

insert into categoria(nombre, descr)
values ('Urbano', '4 asientos. Entre 2,7 y 3,7 metros de longitud. Ideales para moverse por la ciudad y encontrar aparcamiento facilmente. Motores de combustión y eléctricos'),
('Utilitario','5 asientos. Entre 3,7 y 4,2 metros de longitud. Adecuados para la ciudad y para realizar viajes no muy largos. Motores de gasolina, diésel, híbridos y eléctricos'),
('Compacto','5 asientos. Emtre 4,2 y 4,6 metros de longitud. Listos para viajar a ciudades distantes y moverse en la ciudad. Modelos familiares, coupé y descapotables. Motores de gasolina, diésel y eléctricos'),
('Berlina','Entre 4,6 y mas de 5 metros. Para viajes largos, disfrutando de comodidad absoluta y altas prestaciones. Modelos familiares, coupé y descapotables. Motores de gasolina, diésel e híbridos');


CREATE TABLE vehiculo
(	idVehiculo INT IDENTITY NOT NULL,
	marca VARCHAR(50) NOT NULL,
	modelo VARCHAR(50) NOT NULL,
	año SMALLINT NOT NULL,
	motor VARCHAR(200) NOT NULL, --mod
	cambio VARCHAR(100) NOT NULL, --mod
	idCategoria INT NOT NULL,

	CONSTRAINT PkVehiculo
		PRIMARY KEY (idVehiculo),

	CONSTRAINT FkCategoriaNVehiculo
		FOREIGN KEY (idCategoria)
		REFERENCES categoria (idCategoria),
);

CREATE TABLE coche
(	matricula CHAR(7) NOT NULL,
	Kilometros NUMERIC(7,1) NOT NULL,
	precio MONEY NOT NULL,
	estado VARCHAR(15) NOT NULL,
	idVehiculo INT NOT NULL,
	todoRiesgo MONEY NOT NULL,
	terceros MONEY NOT NULL,

	CONSTRAINT PkCoche
		PRIMARY KEY (matricula),

	CONSTRAINT FkVehiculoNCoche
		FOREIGN KEY (idVehiculo)
		REFERENCES vehiculo (idVehiculo),
);

CREATE TABLE sesion
(	idSesion INT IDENTITY NOT NULL,
	eCorreo VARCHAR(100) NOT NULL,
	pass VARCHAR(255) NOT NULL,
	rol VARCHAR(20) NOT NULL DEFAULT 'cli', --mod

	CONSTRAINT PkSesion
		PRIMARY KEY (idSesion),

	CONSTRAINT UeCorreoNSesion
		UNIQUE (eCorreo),
);

CREATE TABLE cliente
(	idCliente INT IDENTITY NOT NULL,
	apellido VARCHAR(100) NOT NULL,
	nombre VARCHAR(50) NOT NULL,
	documento VARCHAR(10) NOT NULL,
	tipo VARCHAR(10) NOT NULL,
	domicilio VARCHAR(200) NOT NULL,
	tlfno VARCHAR(15) NOT NULL,
	eCorreo VARCHAR(100) NOT NULL,
	nacionalidad VARCHAR(30) NOT NULL,

	CONSTRAINT PkCliente
		PRIMARY KEY (idCliente),

	CONSTRAINT FkUsuarioNCliente
		FOREIGN KEY (eCorreo)
		REFERENCES sesion (eCorreo),
);

CREATE TABLE empleado
(	idEmpleado INT IDENTITY NOT NULL,
	apellido VARCHAR(100) NOT NULL,
	nombre VARCHAR(50) NOT NULL,
	dni VARCHAR(10) NOT NULL,
	SS CHAR(12) NOT NULL,
	domicilio VARCHAR(200) NOT NULL,
	tlfno VARCHAR(15) NOT NULL,
	eCorreo VARCHAR(100) NOT NULL,
	cargo VARCHAR(30) NOT NULL,

	CONSTRAINT PkEmpleado
		PRIMARY KEY (idEmpleado),

	CONSTRAINT FkUsuarioNEmpleado
		FOREIGN KEY (eCorreo)
		REFERENCES sesion (eCorreo),
);

CREATE TABLE reserva
(	idReserva INT IDENTITY NOT NULL,
	idCliente INT NOT NULL,
	matricula CHAR(7) NOT NULL,
	fInicio DATE NOT NULL,
	fFin DATE NOT NULL,

	CONSTRAINT PkReserva
		PRIMARY KEY (idReserva),

	CONSTRAINT FkClienteNReserva
		FOREIGN KEY (idCliente)
		REFERENCES cliente (idCliente),

	CONSTRAINT FkCocheNReserva
		FOREIGN KEY (matricula)
		REFERENCES coche (matricula),

	CONSTRAINT UCliMatFIniNReserva
		UNIQUE (idCliente, matricula, fInicio)
);

CREATE TABLE alquiler
(	idAlquiler INT IDENTITY NOT NULL,
	idCliente INT NOT NULL,
	matricula CHAR(7) NOT NULL,
	idReserva INT NOT NULL,
	fInicio DATE NOT NULL,
	fFin DATE NOT NULL,
	importe MONEY NOT NULL,
	atendidoPor INT NOT NULL,
	--seguro VARCHAR() NOT NULL,

	CONSTRAINT PkAlquiler
		PRIMARY KEY (idAlquiler),

	CONSTRAINT FkEmpleadoNAlquiler
		FOREIGN KEY (atendidoPor)
		REFERENCES empleado (idEmpleado),

	CONSTRAINT FkClienteNAlquiler
		FOREIGN KEY (idCliente)
		REFERENCES cliente (idCliente),

	CONSTRAINT FkCocheNAlquiler
		FOREIGN KEY (matricula)
		REFERENCES coche (matricula),

	CONSTRAINT FkReservaNAlquiler
		FOREIGN KEY (idReserva)
		REFERENCES reserva (idReserva),

	CONSTRAINT UCliMatFIniNAlquiler
		UNIQUE (idCliente, matricula, fInicio)
);

CREATE TABLE caja
(	idMovimiento INT NOT NULL,
	tipo CHAR NOT NULL,
	fMovimiento DATE NOT NULL DEFAULT GETDATE(),
	importe MONEY NOT NULL,
	descr VARCHAR(200) NOT NULL,

	CONSTRAINT PkCaja
		PRIMARY KEY (idMovimiento),
);