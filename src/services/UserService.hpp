#ifndef USERSERVICE_HPP
#define USERSERVICE_HPP

#include "db/userDb.hpp"
#include "dto/TransacaoDto.hpp"
#include "dto/HistoricoDto.hpp"
#include "oatpp/web/protocol/http/Http.hpp"
#include "oatpp/core/macro/component.hpp"

class UserService {
private:
  typedef oatpp::web::protocol::http::Status Status;
private:
  OATPP_COMPONENT(std::shared_ptr<UserDb>, m_database); // Inject database component
public:

//   oatpp::Object<UserDto> createUser(const oatpp::Object<UserDto>& dto);
    oatpp::Object<UserDto> updateSaldo(const oatpp::Int32& id ,const oatpp::Object<TransacaoDto>& transacaoDto, const oatpp::Int32& saldo);
    oatpp::Object<UserDto> getUserById(const oatpp::Int32& id, const oatpp::provider::ResourceHandle<oatpp::orm::Connection>& connection = nullptr);

    oatpp::Object<HistoricoDto> getClienteHistorico(const oatpp::Int32& id, const oatpp::provider::ResourceHandle<oatpp::orm::Connection>& connection = nullptr);
//   oatpp::Object<PageDto<oatpp::Object<UserDto>>> getAllUsers(const oatpp::UInt32& offset, const oatpp::UInt32& limit);
//   oatpp::Object<StatusDto> deleteUserById(const oatpp::Int32& id);

};

#endif //USERSERVICE_HPP