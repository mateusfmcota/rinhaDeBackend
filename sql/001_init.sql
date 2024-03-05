CREATE TABLE cliente (
    id          INTEGER NOT NULL PRIMARY KEY,
    nome        VARCHAR UNIQUE,
    limite      INTEGER,
    saldo       INTEGER DEFAULT 0
);

INSERT INTO cliente (nome, limite) VALUES ('o barato sai caro', 100000);
INSERT INTO cliente (nome, limite) VALUES ('zan corp ltda', 80000);
INSERT INTO cliente (nome, limite) VALUES ('les cruders', 1000000);
INSERT INTO cliente (nome, limite) VALUES ('padaria joia de cocaia', 10000000);
INSERT INTO cliente (nome, limite) VALUES ('kid mais', 500000);

CREATE TABLE transacoes (
    id  INTEGER NOT NULL PRIMARY KEY,
    valor INTEGER NOT NULL,
    tipo VARCHAR(1) NOT NULL,
    descricao VARCHAR NOT NULL,
    realizada_em VARCHAR(30),
    clienteId INTEGER NOT NULL
);

INSERT INTO transacoes (valor, tipo, descricao, realizada_em, clienteId) VALUES(10,'c', 'descricao', strftime('%Y-%m-%dT%H:%M:%fZ', 'now'), 1);