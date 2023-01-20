#include <QtTest>
#include <serverlangparser.h>

// add necessary includes here

#define PARSE_TEST_FILE(x)\
    NaiSys::ServerLang::parser prs(x, \
                           "C:/Git-Repos/NaiSys-HttpServer/NaiSys-DesktopUtils/LibServerLang/Tests/"); \
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

};

QTEST_APPLESS_MAIN(GeneralTests)

#include "tst_generaltests.moc"