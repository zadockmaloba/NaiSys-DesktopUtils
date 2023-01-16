#include "naisysxlsx.h"

namespace NaiSys {

NaiSysXLSX::NaiSysXLSX(QObject *parent)
    : QObject{parent}
{

}

bool NaiSysXLSX::jsonArrayToSpreadSheet(const QJsonArray &jsonArr, const QString &name)
{
//    auto _url = QUrl(name);
//    auto _book = SimpleXlsx::CWorkbook(std::to_string(rand()));
//    auto &_sheet = _book.AddSheet( "Untitled" );
//    qDebug() << "Created Table";
//    SimpleXlsx::Style style;
//    style.horizAlign = SimpleXlsx::ALIGN_H_CENTER;
//    const size_t CenterStyleIndex = _book.AddStyle( style );


//    _sheet.BeginRow(40);
//    for(auto &col : jsonArr.at(0).toObject().keys()){
//        SimpleXlsx::Style style2;
//        style2.font.size = 11;
//        //style2.font.attributes = SimpleXlsx::EFontAttributes::FONT_BOLD;
//        auto const HeaderStyle = _book.AddStyle( style2 );
//        _sheet.AddCell(col.toUpper().toStdString(), HeaderStyle);
//    }
//    _sheet.EndRow();

//    for(auto const &v : jsonArr)
//    {
//        auto obj = v.toObject();

//        _sheet.BeginRow();
//        for(auto &col : obj.keys()){
//            if(col.contains("date" , Qt::CaseInsensitive) ||
//               col.contains("time", Qt::CaseInsensitive))
//            {
//                style.numFormat.formatString = "yyyy.mm.dd hh:mm:ss.000";
//                //const size_t CustomDateTimeStyleIndex = _book.AddStyle( style );
//                auto _date = QDateTime::fromString(obj[col].toString(), "yyyyMMddhhmmss");
//                _sheet.AddCell( _date.toString("dd-MMMM-yyyy hh:mm:ss").toStdString());
//            }

//            else if(col.contains("amount", Qt::CaseInsensitive) ||
//                    col.contains("balance", Qt::CaseInsensitive))
//            {
//                _sheet.AddCell(obj[col].toString().toDouble(), CenterStyleIndex);
//            }

//            else _sheet.AddCell(obj[col].toString().toStdString());
//        }
//        _sheet.EndRow();
//    }

//    qDebug() << _url.path();
//    auto pathString = _url.path();

//    #ifdef _WIN32
//    pathString.remove(0,1);
//    #endif

//    qDebug() << pathString;
//    return _book.Save(pathString.toStdString());
}

} // namespace NaiSys
