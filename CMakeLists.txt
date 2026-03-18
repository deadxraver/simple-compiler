add_library(
            compiler_lib
            src/expression.cpp
            src/parser.cpp
            src/statement.cpp
            src/token.cpp
            src/lexer.cpp
            src/util.cpp
)

add_executable(compile src/main.cpp)
target_link_libraries(compile compiler_lib)
