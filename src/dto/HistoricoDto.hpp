#ifndef HistoricoDto_hpp
#define HistoricoDto_hpp

#include "oatpp/core/macro/codegen.hpp"
#include "oatpp/core/Types.hpp"

#include OATPP_CODEGEN_BEGIN(DTO)

class HistoricoSaldoDto: public oatpp::DTO{
     DTO_INIT(HistoricoSaldoDto, DTO)

     DTO_FIELD(Int32, total);
     DTO_FIELD(String, data_extrato);
     DTO_FIELD(Int32, limite);
};

class HistoricoTransacaoDto: public oatpp::DTO{
     DTO_INIT(HistoricoTransacaoDto, DTO)

     DTO_FIELD(Int32, valor);
     DTO_FIELD(String, tipo);
     DTO_FIELD(String, descricao);
     DTO_FIELD(String, realizada_em);
};


class HistoricoDto: public oatpp::DTO {
    DTO_INIT(HistoricoDto, DTO)

    DTO_FIELD(Object<HistoricoSaldoDto>, saldo);
    DTO_FIELD(Vector<Object<HistoricoTransacaoDto>>, ultimas_transacoes);
};

#include OATPP_CODEGEN_END(DTO)

#endif /* UserDto_hpp */