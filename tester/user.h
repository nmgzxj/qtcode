#ifndef USER_H
#define USER_H
#include <QString>
#include <QChar>
#include <QRegExp>
#include <QRegExpValidator>
#include "xmlconfigreader.h"
char card_type_trs;

class User
{
public:
    bool car_num1518;

    User();
    QString user_name;	//持有人姓名
    QString card_type;	//证件类型
    QString card_num;		//证件号码
    QString card_add;		//证件地址

    QString mail_add;		// 通信地址
    QString load_add;		// 装机地址

    void setcard_type(QString card_type);
    /**
     * 根据相关规则判断每一条用户信息是否有效
     * @return boolean
     */
    int if_owner_element_ok(int sceneflag, int time_flag, int time_15IDCard_flag);
    /**
     * 判断：非空且为数字组合
     * @param num
     * @return boolean
     */
    bool If_card_num(QString num);
    /**
     * 8个字符且至少2个中文
     * @param strName
     * @return boolean
     */
    bool if_8ch(QString strName, int time_flag);

//    /**
//     * 获得卡号
//     * @return card_num
//     */
//    QString getCard_num() {
//        return card_num;
//    }

//    /**
//     * 设置卡号
//     * @param card_num
//     */
//    void setCard_num(QString card_num) {
//        card_num = card_num.replace('x', 'X');
//        this.card_num = card_num;
//    }

//    /**
//     * 获得证件地址
//     * @return card_add
//     */
//    QString getCard_add() {
//        return card_add;
//    }

//    /**
//     * 设置证件地址
//     * @param card_add
//     */
//    void setCard_add(QString card_add) {
//        this.card_add = card_add;
//    }

//    /**
//     * 获得通讯地址
//     * @return mail_add
//     */
//    QString getMail_add() {
//        return mail_add;
//    }

//    /**
//     * 设置证件地址
//     * @param mail_add
//     */
//    void setMail_add(QString mail_add) {
//        this.mail_add = mail_add;
//    }

//    /**
//     * 获得证件地址
//     * @return load_add
//     */
//    QString getLoad_add() {
//        return load_add;
//    }

//    /**
//     * 设置证件地址
//     * @param load_add
//     */
//    void setLoad_add(QString load_add) {
//        this.load_add = load_add;
//    }


    bool if_idcard_num_ok();
    /**
     * 判断身份证是否过期或者未满16周岁
     * @param str
     * @return boolean
     */
    bool idcard_is_overdue(QString idcard_num);

    /**
     * 判断身份证是否需要代办
     * @param str
     * @return boolean
     */
    bool if_idcard_need_agent();
    /**
     * 判断是否为空
     * @param str
     * @return boolean
     */
    bool not_null(QString str);
    /**
     * 判断输入字符是否为汉字
     * @param a
     * @return boolean
     */
    static bool isCh(QChar a);
    /**
     * 判断输入字符串是否为汉字
     * @param strName
     * @return boolean
     */
    bool isChinese(QString strName);

    /**
     * 判断输入字符串是否为英文
     * @param strName
     * @return boolean
     */
    bool isEnglish(QString strName);




    /**身份证（含军人身份证）
     * 1、不能为空
     * 2、必须为汉字,且汉字个数至少是2个
     * 3、姓名中不能带阿拉伯数字以及除.与•之外的特殊字符
     * @return boolean
     */
    bool id_card_name_rule();

    /**身份证（含军人身份证）
     * 1、不能为空
     * 2、必须为汉字,且汉字个数至少是2个
     * 3、姓名中不能带阿拉伯数字以及除.与•之外的特殊字符
     * @return boolean
     */
    bool passport_card_name_rule();

    /**
     * 判断字符串长度是否在4~12个字节之间
     * @return boolean
     */
    bool name_4_8();

    /**
     * 护照--姓名不少于2个字符
     * @return boolean
     */
    bool passport_name_longthan_2();

    /**
     * 长度在4~64个字节
     * @return boolean
     */
    bool card_num4_64();

    /**
     * 护照地址长度在4个字符
     * @return boolean
     */
    bool passport_addr_longer_than_4();

    /**
     * 长度在15~18个字节
     * @return boolean
     */
    bool card_num1518();

    /**
     * 是否符合身份证编码规则
     * @return boolean
     */
    bool if_identity_card();

    /**
     * 是否符合护照编码规则
     * @return boolean
     */
    bool if_passport();


    /**
     * 4个字符且至少2个中文
     * @param strName
     * @return boolean
     */
    bool if_4ch(QString strName);

    /**
     * time:  20151127
     * @param sceneflag
     * @param time_flag
     * @return
     */
    int if_owner_elements_null(int sceneflag, int time_flag);

    /**
     * 经办人未登记检查
     * time:  20151127
     * @param sceneflag
     * @param time_flag， 0、1、2分别代表三个 时间段
     * @return
     */
    int if_agent_elements_null(int sceneflag, int time_flag);

    /**
     * 根据相关规则判断每一条用户信息是否有效
     * @return boolean
     */
    int if_agent_element_ok(int sceneflag, int time_flag);

    /**
     * function: 责任人登记检查
     * time:  20151127
     * @param sceneflag
     * @param time_flag， 0、1、2分别代表三个 时间段
     * @return
     */
    int if_unitliable_elements_null(int sceneflag, int time_flag);

    /**
     * 根据相关规则判断每一条用户信息是否有效
     * @return boolean
     */
    int if_unitliable_element_ok(int sceneflag, int time_flag);


    // 判断证件地址是否符合行政区划
    bool if_addr_is_right();

    /**
     * @return 0x01-数字 0x02-乱码（特殊字符） 0x04-规则库 0x08-不少于2汉字
     */
    int user_name_nck_div();

};

#endif // USER_H
