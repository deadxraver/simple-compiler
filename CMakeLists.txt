add_library(
            compiler_lib
            src/expression.cpp
            src/parser.cpp
            src/statement.cpp
            src/token.cpp
            src/lexer.cpp
            src/util.cpp
            src/data_type.cpp
            src/type_setter.cpp
)

add_executable(compile src/main.cpp)
target_link_libraries(compile compiler_lib)

enable_testing()
add_executable(expression_test test/expression_test.cpp)
add_executable(lexer_test test/lexer_test.cpp)
add_executable(types_test test/types_test.cpp)
target_include_directories(expression_test PRIVATE src)
target_include_directories(lexer_test PRIVATE src)
target_include_directories(types_test PRIVATE src)
target_link_libraries(expression_test compiler_lib)
target_link_libraries(lexer_test compiler_lib)
target_link_libraries(types_test compiler_lib)
add_test(EXPRESSION_TEST expression_test)
add_test(LEXER_TEST lexer_test)
add_test(TYPES_TEST types_test)
