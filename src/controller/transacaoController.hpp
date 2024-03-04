#ifndef TransacaoController_hpp
#define TransacaoController_hpp

#include "dto/DTOs.hpp"
#include "services/UserService.hpp"
#include "dto/TransacaoDto.hpp"

#include "oatpp/web/server/api/ApiController.hpp"
#include "oatpp/core/macro/codegen.hpp"
#include "oatpp/core/macro/component.hpp"

#include OATPP_CODEGEN_BEGIN(ApiController) //<-- Begin codegen

/**
 * Sample Api Controller.
 */
class TransacaoController : public oatpp::web::server::api::ApiController {
public:
  /**
   * Constructor with object mapper.
   * @param objectMapper - default object mapper used to serialize/deserialize DTOs.
   */
  TransacaoController(OATPP_COMPONENT(std::shared_ptr<ObjectMapper>, objectMapper))
    : oatpp::web::server::api::ApiController(objectMapper)
  {}
private:

  typedef TransacaoController __ControllerType;

  ENDPOINT_ASYNC("GET", "/clientes/{id}/extrato", getExtrato) {
    //no body
    ENDPOINT_ASYNC_INIT(getExtrato)
    UserService m_userService;

    Action act() override {
      auto userId = request->getPathVariable("id");

      return _return(controller->createDtoResponse(Status::CODE_200, m_userService.getClienteHistorico(std::stoi(userId))));
    }
  };

  ENDPOINT_ASYNC("POST", "/users/{userId}", trasacao) {

    ENDPOINT_ASYNC_INIT(trasacao)
    UserService m_userService;

    

    Action validate(const oatpp::Object<TransacaoDto>& body) {
      auto userId = request->getPathVariable("userId");
      auto valor = *(body)->valor;
      auto tipo = body->tipo->data();
      auto desc = body->descricao->data();
      
      auto usuario = m_userService.getUserById(std::stoi(userId));
      auto limite = *(usuario)->limite;
      auto saldo = *(usuario)->saldo;

      if(body->tipo == "c"){
        int novoSaldo = saldo + valor;
        return _return(controller->createDtoResponse(Status::CODE_200, m_userService.updateSaldo(std::stoi(userId), body ,novoSaldo)));
      }else{
        int novoSaldo = saldo - valor;
        if(novoSaldo <= (limite * -1)){
          return _return(controller->createResponse(Status::CODE_422));  
        }
        return _return(controller->createDtoResponse(Status::CODE_200, m_userService.updateSaldo(std::stoi(userId), body ,novoSaldo)));
      }

      return _return(controller->createDtoResponse(Status::CODE_200, m_userService.getUserById(std::stoi(userId))));
    }

    Action act() override {
      return request->readBodyToDtoAsync<oatpp::Object<TransacaoDto>>(
          controller->getDefaultObjectMapper()
      ).callbackTo(&trasacao::validate);
    }
  };
  
};

#include OATPP_CODEGEN_BEGIN(ApiController)

#endif
