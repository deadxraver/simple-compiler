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

enable_testing()
add_executable(expression_test test/expression_test.cpp)
target_include_directories(expression_test PRIVATE src)
target_link_libraries(expression_test compiler_lib)
add_test(EXPRESSION_TEST expression_test)
