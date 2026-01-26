add_executable(perisci_hello
  hello.cpp
)

target_compile_features(perisci_hello PUBLIC cxx_std_17)

target_link_libraries(perisci_hello
  PRIVATE
    perisci_api
)

set_target_properties(perisci_hello PROPERTIES OUTPUT_NAME "perisci-hello")
