CREATE SCHEMA stocks;
GO

CREATE TABLE stocks.Empresa(
    Empresa_ID         int          NOT NULL,
    PRIMARY KEY (Empresa_ID)
);

CREATE TABLE stocks.Comercializa(
    Codigo_Produto    VARCHAR(30)           NOT NULL,
    Empresa_ID         int                  NOT NULL,
    PRIMARY KEY (Codigo_Produto),
    FOREIGN KEY (Empresa_ID) REFERENCES stocks.Empresa(Empresa_ID)
);

CREATE TABLE stocks.Produto(
    Codigo_Produto      VARCHAR(30)          NOT NULL,
    Nome                VARCHAR(30)          NOT NULL,
    Iva                 float                NOT NULL,
    Preco               float                NOT NULL,
    PRIMARY KEY (Codigo_Produto),
    FOREIGN KEY (Codigo_Produto) REFERENCES stocks.Comercializa(Codigo_Produto)
);

CREATE TABLE stocks.Tipo_Fornecedor(
    Codigo_fornecedor       int                  NOT NULL,
    Designacao              VARCHAR(30)          NOT NULL,
    PRIMARY KEY (Codigo_fornecedor)
);


CREATE TABLE stocks.Fornecedor(
    NIF_Fornecedor                   int           NOT NULL,
    Numero_Fax            int           NOT NULL,
    Nome                  VARCHAR(30)   NOT NULL,
    Endereco              VARCHAR(30)   NOT NULL,
    Codigo_fornecedor     int           NOT NULL,
    PRIMARY KEY (NIF_Fornecedor),
    FOREIGN KEY (Codigo_fornecedor) REFERENCES stocks.Tipo_Fornecedor(Codigo_fornecedor)
);

CREATE TABLE stocks.Encomenda(
    Numero_Encomenda        int                  NOT NULL,
    Data_Encomenda          DATE                 NOT NULL,
    NIF_Fornecedor          int                  NOT NULL,
    PRIMARY KEY (Numero_Encomenda),
    FOREIGN KEY (NIF_Fornecedor) REFERENCES stocks.Fornecedor(NIF_Fornecedor)
);

CREATE TABLE stocks.Encomenda_Produto_Contem(
    Codigo_Produto      VARCHAR(30)          NOT NULL,
    Codigo_Encomenda    int          NOT NULL,
    Quantidade          int                  NOT NULL CHECK (Quantidade >= 0),
    PRIMARY KEY (Codigo_Produto, Codigo_Encomenda),
    FOREIGN KEY (Codigo_Produto) REFERENCES stocks.Produto(Codigo_Produto),
    FOREIGN KEY (Codigo_Encomenda) REFERENCES stocks.Encomenda(Numero_Encomenda)
);

CREATE TABLE stocks.Armazem(
    Armazem_ID           int                  NOT NULL,
    Nome                 VARCHAR(30)          NOT NULL,
    Localizacao          VARCHAR(30)          NOT NULL,
    PRIMARY KEY (Armazem_ID)
);

CREATE TABLE stocks.Armazem_Produto_Contem(
    Codigo_Produto      VARCHAR(30)          NOT NULL,
    Armazem_ID          int                  NOT NULL,
    Quantidade          int                  NOT NULL CHECK (Quantidade >= 0),
    PRIMARY KEY (Codigo_Produto, Armazem_ID),
    FOREIGN KEY (Codigo_Produto) REFERENCES stocks.Produto(Codigo_Produto),
    FOREIGN KEY (Armazem_ID) REFERENCES stocks.Armazem(Armazem_ID)
);

CREATE TABLE stocks.Condicoes_Pagamento(
    Codigo_Condicao_Pagamento VARCHAR(7) CHECK (Codigo_Condicao_Pagamento in ('pronto', '30 dias', '60 dias')) NOT NULL,
    NIF_Fornecedor            int                  NOT NULL,
    PRIMARY KEY (Codigo_Condicao_Pagamento),
    FOREIGN KEY (NIF_Fornecedor) REFERENCES stocks.Fornecedor(NIF_Fornecedor)
);