#include "UserService.hpp"
#include "dto/TransacaoDto.hpp"
#include <boost/date_time/posix_time/posix_time.hpp>
#include <ctime>

oatpp::Object<UserDto> UserService::getUserById(const oatpp::Int32& id, const oatpp::provider::ResourceHandle<oatpp::orm::Connection>& connection) {

  auto dbResult = m_database->getUserById(id, connection);
  OATPP_ASSERT_HTTP(dbResult->isSuccess(), Status::CODE_500, dbResult->getErrorMessage());

  auto result = dbResult->fetch<oatpp::Vector<oatpp::Object<UserDto>>>();

  return result[0];

}

// to-do
oatpp::Object<HistoricoDto> UserService::getClienteHistorico(const oatpp::Int32& id, const oatpp::provider::ResourceHandle<oatpp::orm::Connection>& connection) {

  auto dbResult = m_database->getHistorico(id);
  // OATPP_ASSERT_HTTP(dbResult->isSuccess(), Status::CODE_500, dbResult->getErrorMessage());

  auto historico = dbResult->fetch<oatpp::Vector<oatpp::Object<HistoricoTransacaoDto>>>();

  dbResult = m_database->getUserById(id);
  // OATPP_ASSERT_HTTP(dbResult->isSuccess(), Status::CODE_500, dbResult->getErrorMessage());
  
  auto userData = dbResult->fetch<oatpp::Vector<oatpp::Object<UserDto>>>()[0];

  auto retorno = HistoricoDto::createShared();
  auto saldo = HistoricoSaldoDto::createShared();


  saldo->total = userData->saldo;
  saldo->limite = userData->limite;
  
  
  { 
    using namespace boost::posix_time;
    ptime t = microsec_clock::universal_time();
    saldo->data_extrato = to_iso_extended_string(t)+"Z";
  }

  // {
  //   // std::time_t time = std::time({});

  //   char timeString[100];
  //   // strftime('%Y-%m-%dT%H:%M:%fZ', 'now')
  //   std::strftime(timeString, std::size(timeString),
  //                 "%Y-%m-%dT%H:%M:%fZ", std::gmtime(&time));
  // }
  

  retorno->saldo = saldo;
  retorno->ultimas_transacoes = historico; 

  return retorno;

}

oatpp::Object<UserDto> UserService::updateSaldo(const oatpp::Int32& id ,const oatpp::Object<TransacaoDto>& transacaoDto, const oatpp::Int32& saldo) {

  auto dbResult = m_database->updateSaldoCliente(id, saldo);  
  
  m_database->adicionarNovaEntradaHistorico(id, transacaoDto);

  // valor, tipo, descricao, id

  // auto dbResult = m_database->updateSaldoCliente(id, saldo);
  OATPP_ASSERT_HTTP(dbResult->isSuccess(), Status::CODE_500, dbResult->getErrorMessage());
  
  return getUserById(id);

}


// oatpp::Object<UserDto> UserService::updateSaldo(const oatpp::Int32& id, const oatpp::Int32& saldo, const oatpp::Object<UserDto>& dto, const oatpp::provider::ResourceHandle<oatpp::orm::Connection>& connection = nullptr) {

//   auto dbResult = m_database->updateSaldoCliente(id, connection);
//   OATPP_ASSERT_HTTP(dbResult->isSuccess(), Status::CODE_500, dbResult->getErrorMessage());
//   OATPP_ASSERT_HTTP(dbResult->hasMoreToFetch(), Status::CODE_404, "User not found");

//   auto result = dbResult->fetch<oatpp::Vector<oatpp::Object<UserDto>>>();
//   OATPP_ASSERT_HTTP(result->size() == 1, Status::CODE_500, "Unknown error");

//   return result[0];

// }
