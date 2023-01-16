#ifndef SERVERCALLS_H
#define SERVERCALLS_H

#include <QMap>
#include <QHash>

namespace NaiSys{
    enum{
        OrderDocket = 1,
        BillPrint,
        BillReceipt
    };
}

static QHash <QString, QString> callsArr = {
    {"sy_0x001A", "SELECT validate_user('_?1','_?2') AS retval;"},
    //=============================================================
    {"fn_0x001A", "SELECT get_current_date() AS retval;"},
    {"fn_0x001B", "SELECT get_current_time() AS retval;"},
    {"fn_0x001C", "SELECT get_next_billID() AS retval;"},
    {"fn_0x001D", "SELECT get_current_shiftID() AS retval;"},
    {"fn_0x001E", "SELECT get_current_orderID() AS retval;"},
    //=============================================================
    {"fn_0x002A", "SELECT get_item_price( '_?1' ) AS retval;"},
    {"fn_0x002B", "SELECT get_order_amount( '_?1' ) AS retval;"},
    {"fn_0x002C", "SELECT get_bill_amount( '_?1' ) AS retval;"},
    {"fn_0x002D", "SELECT * FROM get_order_data() ;"}, //Gets orders from open bills.
    {"fn_0x002E", "SELECT * FROM get_bill_data() ORDER BY id;"}, // TODO: implememnt
    {"fn_0x002F", "SELECT * FROM get_bill_info( '_?1' ) ORDER BY id;"},
    {"fn_0x002G", "SELECT * FROM get_bill_info_open() ORDER BY id;"},
    {"fn_0x002H", "SELECT * FROM get_bill_info_bydate('_?1', '_?2') ORDER BY id;"},
    {"fn_0x002I", "SELECT * FROM get_bill_info_byshift('_?1') ORDER BY id;"},
    {"fn_0x002J", "SELECT * FROM get_customer_list( '_?1' ) ORDER BY id;"},
    {"fn_0x002K", "SELECT * FROM get_active_shift_data() ORDER BY id;"},
    {"fn_0x002L", "SELECT * FROM get_shift_data( '_?1' ) ORDER BY id;"},
    {"fn_0x002J", "SELECT * FROM get_bill_order_list( '_?1' );"},
    //=============================================================
    {"fn_0x003A", "SELECT post_bill('_?1', '_?2', '_?3', '_?4');"},
    {"fn_0x003B", "SELECT post_order('_?1', '_?2', '_?3', '_?4');"},
    {"fn_0x003C", "SELECT open_shift('_?1', '_?2')"},
    {"fn_0x003D", "SELECT post_customer_payment('_?1', '_?2', '_?3', '_?4');"},
    {"fn_0x003E", "SELECT * FROM post_order_returning('_?1', '_?2', '_?3', '_?4');"},
    //=============================================================
    {"ns_0x001A","select * from _?1 ;"},
    {"ns_0x001B","select _?1 from _?2 ;"},
    {"ns_0x001C","SELECT _?1 FROM _?2 WHERE _?3 = '_?4';"},
    {"ns_0x002A","INSERT INTO _?1 (_?2) VALUES(_?3) RETURNING _?4 ;"},
    {"ns_0x004A","CREATE TABLE _?1 COLUMNS( _?2 ) ;"}
};

static QHash <QString, bool> printableCalls = {
    //{"fn_0x003B", true},
    //{"fn_0x003D", true},
    {"fn_0x003E", NaiSys::OrderDocket}
};

#endif // SERVERCALLS_H
