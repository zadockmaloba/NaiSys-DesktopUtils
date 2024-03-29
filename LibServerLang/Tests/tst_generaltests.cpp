#include <QtTest>
#include <serverlangparser.h>

// add necessary includes here

#define PARSE_TEST_FILE(x)\
    NaiSys::ServerLang::Parser prs(x, \
                           "./"); \
    prs.READ();

class GeneralTests : public QObject
{
    Q_OBJECT

public:
    GeneralTests(){};
    ~GeneralTests(){};

private slots:
    void variable_decl()
    {
        PARSE_TEST_FILE("test1.nsl")
    }
    void class_decl()
    {
        PARSE_TEST_FILE("test2.nsl")
    }
    void struct_decl()
    {
        PARSE_TEST_FILE("test3.nsl")
    }
    void function_decl()
    {
        PARSE_TEST_FILE("test4.nsl")
    }
    void hook_decl()
    {
        PARSE_TEST_FILE("test5.nsl")
    }
    void array_decl()
    {
        PARSE_TEST_FILE("test6.nsl")
    }
    void function_call()
    {
        PARSE_TEST_FILE("test7.nsl")
    }
    void python_scope()
    {
        PARSE_TEST_FILE("test8.nsl")
    }
    void variable_ref()
    {
        PARSE_TEST_FILE("test9.nsl")
    }
    void struct_access()
    {
        PARSE_TEST_FILE("test10.nsl")
    }
    void database_methods()
    {
        PARSE_TEST_FILE("test11.nsl")
    }
    void import_statements()
    {
        PARSE_TEST_FILE("test12.nsl")
    }

};

QTEST_APPLESS_MAIN(GeneralTests)

#include "tst_generaltests.moc"
