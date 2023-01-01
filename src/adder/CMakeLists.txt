add_library(adder STATIC adder.cpp) #when needto include hpp? look up documentation

install(TARGETS adder DESTINATION lib)
install(FILES include/adder.hpp DESTINATION include)