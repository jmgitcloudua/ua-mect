CREATE SCHEMA RentACar;
GO

CREATE TABLE RentACar.BALCAO(			
	Nome		VARCHAR(50)		NOT NULL,
	Endereco	VARCHAR(50)		NOT NULL,
	Numero		INT	,
	PRIMARY KEY(Numero)
);

CREATE TABLE RentACar.CLIENTE(
	Nome		VARCHAR(50)		NOT NULL,
	Endereco	VARCHAR(50)		NOT NULL,
	Num_Carta	INT				NOT NULL,
	NIF			INT				NOT NULL,
	PRIMARY KEY(NIF)
);

CREATE TABLE RentACar.TIPO_VEICULO(
	Codigo			VARCHAR(30)		NOT NULL,
	Designacao		VARCHAR(15)		NOT NULL,
	Arcondicionado	INT			,
	PRIMARY KEY(Codigo)
);


CREATE TABLE RentACar.VEICULO(
	Matricula			CHAR(8)			NOT NULL,
	Marca				CHAR(15)		NOT NULL,
	Ano					INT				NOT NULL,
	Codigo_Tipo_Veiculo	VARCHAR(30)		NOT NULL,
	PRIMARY KEY (Matricula),
	FOREIGN KEY (Codigo_Tipo_Veiculo) REFERENCES RentACar.TIPO_VEICULO(Codigo)
);

CREATE TABLE RentACar.ALUGUER(
	Numero				INT				NOT NULL,
	Duracao				INT				NOT NULL,
	Datta				TIMESTAMP		NOT NULL,
	NIF_Cliente			INT				NOT NULL,
	Numero_Balcao		INT				,
	Matricula_Veiculo	CHAR(8)			NOT NULL,
	PRIMARY KEY(Numero),
	FOREIGN KEY (NIF_Cliente) REFERENCES RentACar.CLIENTE(NIF),
	FOREIGN KEY (Matricula_Veiculo) REFERENCES RentACar.VEICULO(Matricula),
	FOREIGN KEY (Numero_Balcao) REFERENCES RentACar.BALCAO(Numero)
);

CREATE TABLE RentACar.LIGEIRO(
	Codigo_Tipo			VARCHAR(30)		NOT NULL,
	Numlugares			INT				NOT NULL,
	Portas				INT				NOT NULL,
	Combustivel			CHAR(15)		NOT NULL CHECK (Combustivel IN ('Gasolina', 'Gás', 'Híbrido', 'Eletrico')),
	PRIMARY KEY(Codigo_Tipo),
	FOREIGN KEY (Codigo_Tipo) REFERENCES RentACar.TIPO_VEICULO(Codigo)
);

CREATE TABLE RentACar.PESADO(
	Codigo_Tipo			VARCHAR(30)		NOT NULL,
	Peso				INT				NOT NULL,
	Passageiros			INT				NOT NULL,
	PRIMARY KEY(Codigo_Tipo),
	FOREIGN KEY (Codigo_Tipo) REFERENCES RentACar.TIPO_VEICULO(Codigo)
);

CREATE TABLE RentACar.SIMILARIDADE(
	Codigo_Tipo1		VARCHAR(30)		NOT NULL,
	Codigo_Tipo2		VARCHAR(30)		NOT NULL,
	PRIMARY KEY(Codigo_Tipo1),
	FOREIGN KEY (Codigo_Tipo2) REFERENCES RentACar.TIPO_VEICULO(Codigo)
);
