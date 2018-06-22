note :

- run `git pull --recurse-submodules` `git submodule update --init`
- For Mariadbpp testing, change `deps/mariadbpp/test/CMakeFile.txt` user and password entry
- In deps/mariadbpp/test/CMakeFile.txt, change line to this : `target_link_libraries(mariadbpp_tests mariadbclientpp gtest_main mariadbclient)`

todo : 
- Use configuration based design for test
- Use configuration based design for main
- Use standalone CMakeFile for test