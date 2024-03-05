
#ifndef DATABASECOMPONENT_HPP
#define DATABASECOMPONENT_HPP

#include "db/userDb.hpp"
#include "dto/ConfigDto.hpp"

class DatabaseComponent {
public:

  /**
   * Create database client
   */
  OATPP_CREATE_COMPONENT(std::shared_ptr<UserDb>, userDb)([] {

    auto connectionProvider = std::make_shared<oatpp::postgresql::ConnectionProvider>("postgresql://admin:123@db:5432/rinha");    

    //postgresql://[ENTER USERNAME HERE]:[ENTER PASSWORD HERE]@db:5432/rinha
    /* Create database-specific ConnectionPool */
    auto connectionPool = oatpp::postgresql::ConnectionPool::createShared(connectionProvider, 
                                                                      10 /* max-connections */, 
                                                                      std::chrono::seconds(5) /* connection TTL */);
    
    /* Create database-specific Executor */
    auto executor = std::make_shared<oatpp::postgresql::Executor>(connectionPool);

    return std::make_shared<UserDb>(executor);

  }());


};

#endif //SQLITE_DATABASECOMPONENT_HPP
