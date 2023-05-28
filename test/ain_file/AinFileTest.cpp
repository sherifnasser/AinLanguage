
#include <iostream>
#include <catch2/catch.hpp>
#include "AinFile.hpp"
#include "BadFileFormatException.hpp"

SCENARIO("Test AinFile.cpp","[AinFileTest.cpp]"){
    GIVEN("A file"){
        WHEN("format is *.ain"){
            std::string path="../test/ain_file/testPass.ain";
            AinFile file(path);
            std::vector<std::wstring> LINES={L"##",L"This for testing AinFile.cpp",L"##"};
            THEN("read lines in file"){
                auto lines=file.getLines();
                REQUIRE(lines.size()==LINES.size());
                for(int i=0;i<lines.size();i++){
                    REQUIRE(lines[i]==LINES[i]);
                }
            }
        };

        WHEN("file in path and format is not *.ain"){
            THEN("Throw BadFileFormatException with file name"){
                std::string path="app/testFail.notain";

                auto matcher=Catch::Matchers::Predicate<BadFileFormatException>(
                    [&](const BadFileFormatException e){
                        std::string what=e.what();
                        return
                            what.find("testFail.notain")!=std::string::npos
                                &&
                            what.find("app/")==std::string::npos
                        ;
                    }
                );

                REQUIRE_THROWS_MATCHES(
                    AinFile(path),
                    BadFileFormatException,
                    matcher
                );

            };
        };
    };

}