#ifndef TransacaoDto_hpp
#define TransacaoDto_hpp

#include "oatpp/core/macro/codegen.hpp"
#include "oatpp/core/Types.hpp"

#include OATPP_CODEGEN_BEGIN(DTO)

class TransacaoDto: public oatpp::DTO {
    DTO_INIT(TransacaoDto, DTO)

    DTO_FIELD(Int32, valor);
    DTO_FIELD(String, tipo);
    DTO_FIELD(String, descricao);
};


#include OATPP_CODEGEN_END(DTO)

#endif /* TransacaoDto_hpp */