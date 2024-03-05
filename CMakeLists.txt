cmake_minimum_required(VERSION 3.1)

set(project_name my-project) ## rename your project here

project(${project_name})

set(CMAKE_CXX_STANDARD 11)

include_directories(src)

add_library(${project_name}-lib
        src/AppComponent.hpp
        src/controller/transacaoController.cpp
        src/controller/transacaoController.hpp
        src/services/UserService.hpp
        src/services/UserService.cpp
        src/dto/DTOs.hpp
)

## link libs

# find_package(SQLite3 REQUIRED)
find_package(oatpp          1.3.0 REQUIRED)
find_package(oatpp-postgresql   1.3.0 REQUIRED)
# find_package(oatpp-sqlite   1.3.0 REQUIRED)

target_link_libraries(${project_name}-lib
        # PUBLIC SQLite::SQLite3
        PUBLIC oatpp::oatpp
        # PUBLIC oatpp::oatpp-test
        PUBLIC oatpp::oatpp-sqlite
)

## add executables

add_definitions(

        -DDATABASE_FILE="${CMAKE_CURRENT_SOURCE_DIR}/db.sqlite"

        ## Path to database migration scripts
        -DDATABASE_MIGRATIONS="${CMAKE_CURRENT_SOURCE_DIR}/sql"

)

add_executable(${project_name}-exe
        src/App.cpp
)
target_link_libraries(${project_name}-exe ${project_name}-lib)
add_dependencies(${project_name}-exe ${project_name}-lib)

# add_executable(${project_name}-test
#         test/tests.cpp
#         test/app/TestComponent.hpp
#         test/app/MyApiTestClient.hpp
# )
# target_link_libraries(${project_name}-test ${project_name}-lib)
# add_dependencies(${project_name}-test ${project_name}-lib)

# set_target_properties(${project_name}-lib ${project_name}-exe ${project_name}-test PROPERTIES
#         CXX_STANDARD 11
#         CXX_EXTENSIONS OFF
#         CXX_STANDARD_REQUIRED ON
#         LINKER_LANGUAGE CXX
# )

# enable_testing()
# add_test(project-tests ${project_name}-test)
