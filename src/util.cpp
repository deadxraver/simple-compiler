#include "util.hpp"

bool is_whitespace(char c) {
  return c == ' ' || c == '\t' || c == '\n';
}

bool is_digit(char c) {
  return c >= '0' && c <= '9';
}

bool is_letter(char c) {
  return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z');
}

bool is_operator(char c) {
  return c == '!' || c == '=' || c == '<' || c == '>' || c == '|' || c == '&' || c == '+' || c == '-';
}

bool is_eof(char c) {
  return c == 0;
}
