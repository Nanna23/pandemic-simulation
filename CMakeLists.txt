cmake_minimum_required(VERSION 3.16)
project(chain VERSION 0.1.0)

# abilita il supporto per i test, tra cui l'opzione BUILD_TESTING usata sotto
include(CTest)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# richiedi l'uso di C++17, senza estensioni non-standard offerte dal compilatore usato 
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS ON)

# abilita warning
string(APPEND CMAKE_CXX_FLAGS " -Wall -Wextra")

# abilita l'address sanitizer e l'undefined-behaviour sanitizer in debug mode
string(APPEND CMAKE_CXX_FLAGS_DEBUG " -fsanitize=address,undefined")
string(APPEND CMAKE_EXE_LINKER_FLAGS_DEBUG " -fsanitize=address,undefined")

# richiedi il componente graphics della libreria SFML, versione 2.5
#   le dipendenze vengono identificate automaticamente
find_package(SFML 2.5 COMPONENTS graphics REQUIRED)

#   notare l'assenza degli header file, che pero' possono essere indicati
add_executable(app main.cpp model/pandemic.cpp model/population.cpp view/consoleInterface.cpp controller/simulation.cpp)
# l'eseguibile dipende dalla libreria sfml-graphics e sue dipendenze
target_link_libraries(app PRIVATE sfml-graphics)

# se il testing e' abilitato...
#   per disabilitare il testing, passare -DBUILD_TESTING=OFF a cmake durante la fase di configurazione
if (BUILD_TESTING)

  # aggiungi l'eseguibile pandemic.t
  add_executable(pandemic.t model/pandemic.cpp model/population.cpp test/pandemic.test.cpp)
  # aggiungi l'eseguibile pandemic.t alla lista dei test
  add_test(NAME pandemic.t COMMAND pandemic.t)

  # aggiungi l'eseguibile population.t
  add_executable(population.t model/population.cpp test/population.test.cpp)
  # aggiungi l'eseguibile population.t alla lista dei test
  add_test(NAME population.t COMMAND population.t)

  # aggiungi l'eseguibile simulation.t
  add_executable(simulation.t controller/simulation.cpp model/pandemic.cpp model/population.cpp test/simulation.test.cpp)
  # aggiungi l'eseguibile simulation.t alla lista dei test
  add_test(NAME simulation.t COMMAND simulation.t)

endif()
