
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

    auto connectionProvider = std::make_shared<oatpp::sqlite::ConnectionProvider>("data.sqlite");    
  
    /* Create database-specific ConnectionPool */
    auto connectionPool = oatpp::sqlite::ConnectionPool::createShared(connectionProvider, 
                                                                      10 /* max-connections */, 
                                                                      std::chrono::seconds(5) /* connection TTL */);
    
    /* Create database-specific Executor */
    auto executor = std::make_shared<oatpp::sqlite::Executor>(connectionPool);

    return std::make_shared<UserDb>(executor);

  }());


};

#endif //SQLITE_DATABASECOMPONENT_HPP
