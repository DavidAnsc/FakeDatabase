cmake_minimum_required(VERSION 3.15)

project(FakeDatabase
    VERSION 0.0.1
    DESCRIPTION "Fake database"
    LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(SOURCE_FILES 
  src/main.cpp 
  src/DataModels/OperationArray.cpp 
  src/DataModels/DatabaseRelated/Query.cpp 
  src/DataModels/DatabaseRelated/Row.cpp 
  src/DataModels/DatabaseRelated/Table.cpp 
  src/Kits/CommandParser.cpp
  src/DataModels/DatabaseRelated/Commands.cpp
  src/DataModels/DatabaseRelated/DBOperations.cpp
)

add_executable(fake_database
  ${SOURCE_FILES}
)

target_include_directories(fake_database PRIVATE include)