PATHS=(abstr irt lexer main.cpp table_of_symbols type_checker)

for item in ${PATHS[*]}
do
    echo "=============== Checking ${item} ==============="
    cppcheck ${item} --enable=warning,performance,portability,style --language=c++ --suppressions-list=suppressions.txt

done