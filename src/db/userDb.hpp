#ifndef SQLITE_USERDB_HPP
#define SQLITE_USERDB_HPP

#include "dto/UserDto.hpp"
#include "dto/TransacaoDto.hpp"
#include "oatpp-postgresql/orm.hpp"
#include <stdio.h>

#include OATPP_CODEGEN_BEGIN(DbClient)

class UserDb : public oatpp::orm::DbClient {
    public:
    UserDb(const std::shared_ptr<oatpp::orm::Executor>& executor)
    : oatpp::orm::DbClient(executor)
  {

    // oatpp::orm::SchemaMigration migration(executor);
    // printf("path: %s\n\n\n\n", DATABASE_MIGRATIONS);
    // migration.addFile(1, DATABASE_MIGRATIONS "/001_init.sql");
    // migration.migrate();

    // auto version = executor->getSchemaVersion();
    // OATPP_LOGD("ClienteDb", "Migration - OK. Version=%d.", version);

  }

  QUERY(getUserById,
        "SELECT limite, saldo FROM cliente WHERE id=:id;",
        PARAM(oatpp::Int32, id))

  QUERY(updateSaldoCliente,
        "UPDATE cliente SET saldo=:saldo WHERE id=:id;",
        PARAM(oatpp::Int32, id),
        PARAM(oatpp::Int32, saldo))
  
  QUERY(adicionarNovaEntradaHistorico,
    "INSERT INTO transacoes (valor, tipo, descricao, realizada_em, clienteId) VALUES(:transacao.valor,:transacao.tipo, :transacao.descricao, :data, :id)",
    PARAM(oatpp::Int32, id),
    PARAM(oatpp::Object<TransacaoDto>, transacao),
    PARAM(oatpp::String, data)
  )

  QUERY(getHistorico,
    "SELECT valor, tipo, descricao, realizada_em FROM transacoes where clienteId=:id order by realizada_em DESC limit 10;",
    PARAM(oatpp::Int32, id)
  )
  };
  

#include OATPP_CODEGEN_END(DbClient) //<- End Codegen

#endif 
