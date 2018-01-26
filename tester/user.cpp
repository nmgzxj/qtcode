//#include "user.h"
//#include <QTime>

//User::User()
//{
//}



////    /**
////     * 获得用户名
////     * @return user_name
////     */
////    QString getUser_name() {
////        return user_name;
////    }

////    /**
////     * 设置用户名
////     * @param user_name
////     */
////    void setUser_name(QString user_name) {
////        this.user_name = user_name;
////    }

////    /**
////     * 获得证件类型
////     * @return card_type
////     */
////    QString getcard_type() {
////        return card_type;
////    }

//    /**
//     * 设置证件类型，把证件类型和字符对应
//     * @param card_type
//     */
//    void User::setcard_type(QString card_type) {
//        card_type = card_type;

//        QString xml_type = XMLConfigReader::xml_Person_CardTypeMap.get(card_type);
//        if (xml_type.isNull())	{
//            card_type_trs='o'; 	return;
//        }

//        if (xml_type.compare("居民身份证") || xml_type.compare("临时居民身份证"))
//            card_type_trs='a';
//        else if(xml_type.compare("户口薄"))
//            card_type_trs='b';
//        else if(xml_type.compare("外国公民护照"))
//            card_type_trs='c';
//        else if(xml_type.compare("港澳居民来往内地通行证"))
//            card_type_trs='d';
//        else if(xml_type.compare("台湾居民来往大陆通行证"))
//            card_type_trs='e';
//        else if(xml_type.compare("中国人民解放军军人身份证件"))
//            card_type_trs='f';
//        else if(xml_type.compare("中国人民武装警察身份证件"))
//            card_type_trs='g';
//        else if(xml_type.compare("法律、行政法规和国家规定的其他有效身份证件"))
//            card_type_trs='h';
//        else
//            card_type_trs='o';
//    }

////    /**
////     * 获得卡号
////     * @return card_num
////     */
////    QString getCard_num() {
////        return card_num;
////    }

////    /**
////     * 设置卡号
////     * @param card_num
////     */
////    void setCard_num(QString card_num) {
////        card_num = card_num.replace('x', 'X');
////        this.card_num = card_num;
////    }

////    /**
////     * 获得证件地址
////     * @return card_add
////     */
////    QString getCard_add() {
////        return card_add;
////    }

////    /**
////     * 设置证件地址
////     * @param card_add
////     */
////    void setCard_add(QString card_add) {
////        this.card_add = card_add;
////    }

////    /**
////     * 获得通讯地址
////     * @return mail_add
////     */
////    QString getMail_add() {
////        return mail_add;
////    }

////    /**
////     * 设置证件地址
////     * @param mail_add
////     */
////    void setMail_add(QString mail_add) {
////        this.mail_add = mail_add;
////    }

////    /**
////     * 获得证件地址
////     * @return load_add
////     */
////    QString getLoad_add() {
////        return load_add;
////    }

////    /**
////     * 设置证件地址
////     * @param load_add
////     */
////    void setLoad_add(QString load_add) {
////        this.load_add = load_add;
////    }

//    /**
//     * 根据相关规则判断每一条用户信息是否有效
//     * @return boolean
//     */
//    int User::if_owner_element_ok(int sceneflag, int time_flag, int time_15IDCard_flag){

//        //System.out.println(this.card_add);


//        int flag=0x00;
//        int tmpflag = 0x00;

//        switch(card_type_trs){
//        case 'a':
//            //"身份证"
//            if ( (time_15IDCard_flag==1) && this->card_num.length()<18) {	// 如果是15位身份证停用后且身份证号码不是18位
//                flag |= 0x01;
//            } else {

//                if (!this->id_card_name_rule())
//                    flag |= 0x02;
//                if (!this->If_card_num(this->card_num) || !this->card_num1518() || !this->if_identity_card() )
//                    flag |= 0x04;

//                //20170627 阿里没有地址问题
//                if (time_flag==2 || time_flag==1) {
//                    if (sceneflag==0 || sceneflag==2 || sceneflag==6) {	//移动用户
//                        if (!this->if_8ch(this->card_add, time_flag))
//                            flag |= 0x08;
//                    } else if (sceneflag==1 || sceneflag==7) {	// 个人固话、个人代办固话
//                        if (this->load_add.compare("null") || this->load_add.compare("NULL")) {
//                            if ( !this->if_8ch(this->card_add, time_flag) )
//                                flag |= 0x08;
//                        } else if (this->card_add.compare("null") || this->card_add.compare("NULL")) {
//                            if ( !this->if_8ch(this->load_add, time_flag) )
//                                flag |= 0x20;
//                        } else {
//                            if (!this->if_8ch(this->card_add, time_flag) && !this->if_8ch(this->load_add, time_flag))
//                                flag |= 0x08;
//                        }
//                    }
//                } else if (time_flag==0) {
//                    if (sceneflag==0 || sceneflag==2 || sceneflag==6) {
//                        if (this->card_add.compare("null") || this->card_add.compare("NULL")) {
//                            if ( !this->if_8ch(this->mail_add, time_flag) )
//                                flag |= 0x10;
//                        } else if (this->mail_add.compare("null") || this->mail_add.compare("NULL")) {
//                            if ( !this->if_8ch(this->card_add, time_flag) )
//                                flag |= 0x08;
//                        } else {
//                            if (!this->if_8ch(this->card_add, time_flag) && !this->if_8ch(this->mail_add, time_flag))
//                                flag |= 0x08;
//                        }
//                    } else if (sceneflag==1 || sceneflag==7) {	// 个人固话、个人代办固话
//                        if ( !this->if_8ch(this->card_add, time_flag) )
//                            tmpflag |= 0x08;
//                        if ( !this->if_8ch(this->mail_add, time_flag) )
//                            tmpflag |= 0x10;
//                        if (!this->if_8ch(this->load_add, time_flag))
//                            tmpflag |= 0x20;

//                        //System.out.println("tmpflag " + tmpflag);
//                        //
//                        if ( (tmpflag&0x08)==0 || (tmpflag&0x10)==0 || (tmpflag&0x20)==0) {

//                        } else {
//                            if ( (tmpflag&0x08)!=0 ) {	flag |= 0x08;  }
//                            if ( (tmpflag&0x10)!=0)  {  flag |= 0x10;  }
//                            if ( (tmpflag&0x20)!=0)  {  flag |= 0x20;  }
//                        }

//                    }
//                }
//            }

//            break;
//        case 'b':
//            //户口簿
//        case 'c':
//            //"外国公民护照"
//            //System.out.println("外国公民护照");
//            if (!this->passport_card_name_rule())
//                flag |= 0x02;
//            if (!this->card_num4_64())
//                flag |= 0x04;
//            /*
//            if (time_flag==2 || time_flag==1) {
//                if (sceneflag==0 || sceneflag==2 || sceneflag==6) {	//移动用户
//                    if (!this->if_8ch(this->card_add, time_flag))
//                        flag |= 0x08;
//                } else if (sceneflag==1 || sceneflag==7) {	// 个人固话、个人代办固话
//                    if (this->load_add.compare("null") || this->load_add.compare("NULL")) {
//                        if ( !this->if_8ch(this->card_add, time_flag) )
//                            flag |= 0x08;
//                    } else if (this->card_add.compare("null") || this->card_add.compare("NULL")) {
//                        if ( !this->if_8ch(this->load_add, time_flag) )
//                            flag |= 0x20;
//                    } else {
//                        if (!this->if_8ch(this->card_add, time_flag) && !this->if_8ch(this->load_add, time_flag))
//                            flag |= 0x08;
//                    }
//                }
//            } else if (time_flag==0) {
//                if (sceneflag==0 || sceneflag==2 || sceneflag==6) {
//                    if (this->card_add.compare("null") || this->card_add.compare("NULL")) {
//                        if ( !this->if_8ch(this->mail_add, time_flag) )
//                            flag |= 0x10;
//                    } else if (this->mail_add.compare("null") || this->mail_add.compare("NULL")) {
//                        if ( !this->if_8ch(this->card_add, time_flag) )
//                            flag |= 0x08;
//                    } else {
//                        if (!this->if_8ch(this->card_add, time_flag) && !this->if_8ch(this->mail_add, time_flag))
//                            flag |= 0x08;
//                    }
//                } else if (sceneflag==1 || sceneflag==7) {	// 个人固话、个人代办固话
//                    if ( !this->if_8ch(this->card_add, time_flag) )
//                        tmpflag |= 0x08;
//                    if ( !this->if_8ch(this->mail_add, time_flag) )
//                        tmpflag |= 0x10;
//                    if (!this->if_8ch(this->load_add, time_flag))
//                        tmpflag |= 0x20;

//                    if ( (tmpflag&0x08)==0 || (tmpflag&0x10)==0 || (tmpflag&0x20)==0) {

//                    } else {
//                        if ( (tmpflag&0x08)!=0 ) {	flag |= 0x08;  }
//                        if ( (tmpflag&0x10)!=0)  {  flag |= 0x10;  }
//                        if ( (tmpflag&0x20)!=0)  {  flag |= 0x20;  }
//                    }
//                }
//            }
//            */

//            break;
//        case 'd':
//            //港澳居民来往内地通行证
//        case 'e':
//            //台湾居民来往大陆通行证
//            if (!this->id_card_name_rule())
//                flag |= 0x02;
//            if (!this->card_num4_64())
//                flag |= 0x04;

//            /*
//            if (time_flag==2 || time_flag==1) {
//                if (sceneflag==0 || sceneflag==2 || sceneflag==6) {	//移动用户
//                    if (!this->if_8ch(this->card_add, time_flag))
//                        flag |= 0x08;
//                } else if (sceneflag==1 || sceneflag==7) {	// 个人固话、个人代办固话
//                    if (this->load_add.compare("null") || this->load_add.compare("NULL")) {
//                        if ( !this->if_8ch(this->card_add, time_flag) )
//                            flag |= 0x08;
//                    } else if (this->card_add.compare("null") || this->card_add.compare("NULL")) {
//                        if ( !this->if_8ch(this->load_add, time_flag) )
//                            flag |= 0x20;
//                    } else {
//                        if (!this->if_8ch(this->card_add, time_flag) && !this->if_8ch(this->load_add, time_flag))
//                            flag |= 0x08;
//                    }
//                }
//            } else if (time_flag==0) {
//                if (sceneflag==0 || sceneflag==2 || sceneflag==6) {
//                    if (this->card_add.compare("null") || this->card_add.compare("NULL")) {
//                        if ( !this->if_8ch(this->mail_add, time_flag) )
//                            flag |= 0x10;
//                    } else if (this->mail_add.compare("null") || this->mail_add.compare("NULL")) {
//                        if ( !this->if_8ch(this->card_add, time_flag) )
//                            flag |= 0x08;
//                    } else {
//                        if (!this->if_8ch(this->card_add, time_flag) && !this->if_8ch(this->mail_add, time_flag))
//                            flag |= 0x08;
//                    }
//                } else if (sceneflag==1 || sceneflag==7) {	// 个人固话、个人代办固话
//                    if ( !this->if_8ch(this->card_add, time_flag) )
//                        tmpflag |= 0x08;
//                    if ( !this->if_8ch(this->mail_add, time_flag) )
//                        tmpflag |= 0x10;
//                    if (!this->if_8ch(this->load_add, time_flag))
//                        tmpflag |= 0x20;


//                    if ( (tmpflag&0x08)==0 || (tmpflag&0x10)==0 || (tmpflag&0x20)==0) {

//                    } else {
//                        if ( (tmpflag&0x08)!=0 ) {	flag |= 0x08;  }
//                        if ( (tmpflag&0x10)!=0)  {  flag |= 0x10;  }
//                        if ( (tmpflag&0x20)!=0)  {  flag |= 0x20;  }
//                    }
//                }
//            }
//            */

//            break;
//        case 'f':
//            //"中国人民解放军军人身份证件"
//        case 'g':
//            //"中国人民武装警察身份证件"
//            if (!this->id_card_name_rule())
//                flag |= 0x02;
//            if (!this->card_num4_64())
//                flag |= 0x04;
//            /*
//            if (time_flag==2 || time_flag==1) {
//                if (sceneflag==0 || sceneflag==2 || sceneflag==6) {	//移动用户
//                    if (!this->if_8ch(this->card_add, time_flag))
//                        flag |= 0x08;
//                } else if (sceneflag==1 || sceneflag==7) {	// 个人固话、个人代办固话
//                    if (this->load_add.compare("null") || this->load_add.compare("NULL")) {
//                        if ( !this->if_8ch(this->card_add, time_flag) )
//                            flag |= 0x08;
//                    } else if (this->card_add.compare("null") || this->card_add.compare("NULL")) {
//                        if ( !this->if_8ch(this->load_add, time_flag) )
//                            flag |= 0x20;
//                    } else {
//                        if (!this->if_8ch(this->card_add, time_flag) && !this->if_8ch(this->load_add, time_flag))
//                            flag |= 0x08;
//                    }
//                }
//            } else if (time_flag==0) {
//                if (sceneflag==0 || sceneflag==2 || sceneflag==6) {
//                    if (this->card_add.compare("null") || this->card_add.compare("NULL")) {
//                        if ( !this->if_8ch(this->mail_add, time_flag) )
//                            flag |= 0x10;
//                    } else if (this->mail_add.compare("null") || this->mail_add.compare("NULL")) {
//                        if ( !this->if_8ch(this->card_add, time_flag) )
//                            flag |= 0x08;
//                    } else {
//                        if (!this->if_8ch(this->card_add, time_flag) && !this->if_8ch(this->mail_add, time_flag))
//                            flag |= 0x08;
//                    }
//                } else if (sceneflag==1 || sceneflag==7) {	// 个人固话、个人代办固话
//                    if ( !this->if_8ch(this->card_add, time_flag) )
//                        tmpflag |= 0x08;
//                    if ( !this->if_8ch(this->mail_add, time_flag) )
//                        tmpflag |= 0x10;
//                    if (!this->if_8ch(this->load_add, time_flag))
//                        tmpflag |= 0x20;


//                    if ( (tmpflag&0x08)==0 || (tmpflag&0x10)==0 || (tmpflag&0x20)==0) {

//                    } else {
//                        if ( (tmpflag&0x08)!=0 ) {	flag |= 0x08;  }
//                        if ( (tmpflag&0x10)!=0)  {  flag |= 0x10;  }
//                        if ( (tmpflag&0x20)!=0)  {  flag |= 0x20;  }
//                    }
//                }
//            }
//            */

//            break;
//        default:
//            //System.out.println("其他");
//            QString xml_type = XMLConfigReader.xml_Person_CardTypeMap.get(card_type);
//            if (xml_type.isNull()) xml_type = "非法律、行政法规和国家规定的有效身份证件";
//            if (time_flag==1 || time_flag==2) {
//                if (xml_type.compare("非法律、行政法规和国家规定的有效身份证件"))
//                    flag |= 0x01;
//            }

//            if (!this->id_card_name_rule())
//                flag |= 0x02;
//            if (!this->card_num4_64())
//                flag |= 0x04;

//            //*20170627 阿里没有地址问题
//            if (time_flag==2 || time_flag==1) {
//                if (sceneflag==0 || sceneflag==2 || sceneflag==6) {	//移动用户
//                    if (!this->if_8ch(this->card_add, time_flag))
//                        flag |= 0x08;
//                } else if (sceneflag==1 || sceneflag==7) {	// 个人固话、个人代办固话
//                    if (this->load_add.compare("null") || this->load_add.compare("NULL")) {
//                        if ( !this->if_8ch(this->card_add, time_flag) )
//                            flag |= 0x08;
//                    } else if (this->card_add.compare("null") || this->card_add.compare("NULL")) {
//                        if ( !this->if_8ch(this->load_add, time_flag) )
//                            flag |= 0x20;
//                    } else {
//                        if (!this->if_8ch(this->card_add, time_flag) && !this->if_8ch(this->load_add, time_flag))
//                            flag |= 0x08;
//                    }
//                }
//            } else if (time_flag==0) {
//                if (sceneflag==0 || sceneflag==2 || sceneflag==6) {
//                    if (this->card_add.compare("null") || this->card_add.compare("NULL")) {
//                        if ( !this->if_8ch(this->mail_add, time_flag) )
//                            flag |= 0x10;
//                    } else if (this->mail_add.compare("null") || this->mail_add.compare("NULL")) {
//                        if ( !this->if_8ch(this->card_add, time_flag) )
//                            flag |= 0x08;
//                    } else {
//                        if (!this->if_8ch(this->card_add, time_flag) && !this->if_8ch(this->mail_add, time_flag))
//                            flag |= 0x08;
//                    }
//                } else if (sceneflag==1 || sceneflag==7) {	// 个人固话、个人代办固话
//                    if ( !this->if_8ch(this->card_add, time_flag) )
//                        tmpflag |= 0x08;
//                    if ( !this->if_8ch(this->mail_add, time_flag) )
//                        tmpflag |= 0x10;
//                    if (!this->if_8ch(this->load_add, time_flag))
//                        tmpflag |= 0x20;

//                    if ( (tmpflag&0x08)==0 || (tmpflag&0x10)==0 || (tmpflag&0x20)==0) {

//                    } else {
//                        if ( (tmpflag&0x08)!=0 ) {	flag |= 0x08;  }
//                        if ( (tmpflag&0x10)!=0)  {  flag |= 0x10;  }
//                        if ( (tmpflag&0x20)!=0)  {  flag |= 0x20;  }
//                    }
//                }

//            }
//            //*/
//            break;
//        }

//        //System.out.println(flag);
//        return flag;
//    }

//    bool User::if_idcard_num_ok()
//    {
//        return (this->If_card_num(this->card_num)&& this->card_num1518()&&this->if_identity_card() );
//    }

//    /**
//     * 判断身份证是否过期或者未满16周岁
//     * @param str
//     * @return boolean
//     */
//    bool User::idcard_is_overdue(QString idcard_num){//不为空

//        if (false==If_card_num(idcard_num)) return false;

//        QTime time = QTime::currentTime();
////        SimpleDateFormat df = new SimpleDateFormat("yyyy");
//        QString strcuryear = time.toString("yyyy");// df.format(new QDate());// new Date()为获取当前年份

//        if (card_type_trs=='a') {
//            //"身份证"
//            if (idcard_num.length()<10) return true;

//            QString idcardyear = NULL;
//            if (idcard_num.length() == 15)
//                idcardyear= idcard_num.mid(6, 8);
//            else
//                idcardyear= idcard_num.mid(6, 10);

//            int d_value = 0;
//            if (idcard_num.length() == 15)
//                d_value = strcuryear.toInt() - idcardyear.toInt() - 1900;
//            else
//                d_value = strcuryear.toInt() - idcardyear.toInt();

//            if ( (d_value<0)||(d_value>99)) return true;
//            else return false;
//        }

//        return false;
//    }


//    /**
//     * 判断身份证是否需要代办
//     * @param str
//     * @return boolean
//     */
//    bool if_idcard_need_agent(QString idcard_num, QString phone_active_time)
//    {	//不为空
//        if (!this->If_card_num(idcard_num))
//            return false;
//        if (idcard_num.length()<17)
//            return false;

//        //System.out.println(phone_active_time);
//        QString phone_active_year = NULL;
//        if (phone_active_time!=NULL)
//            phone_active_year = phone_active_time.mid(0, 4);
//        else {
//            phone_active_year = QTime::currentTime().toString("yyyy");
//        }

//        //20160628天津联通BSS系统登记激活时间异常问题解决方案，已知会对方
//        //if (phone_active_year.compare("1900"))
//        //	phone_active_year = "2016";

//        if (card_type_trs=='a'){
//            //"身份证"
//            QString idcardyear = idcard_num.mid(6, 10);
//            int d_value = phone_active_year.toInt() - idcardyear.toInt();
//            if ( (d_value<=10)||(d_value>=120)) return true;
//        }

//        return false;
//    }
//    /**
//     * 判断是否为空
//     * @param str
//     * @return boolean
//     */
//    bool User::not_null(QString str){//不为空
//        return !str.compare("null");
//    }

//    /**
//     * 判断输入字符是否为汉字
//     * @param a
//     * @return boolean
//     */
//    bool User::isCh(QChar a) { //输入的字符是否是汉字static
////         int v = (int)a;
//         return (a >=19968 && a <= 171941);
//    }

//    /**
//     * 判断输入字符串是否为汉字
//     * @param strName
//     * @return boolean
//     */
//    bool User::isChinese(QString strName) {//输入的字符串是否是汉字
//        for (int i = 0; i < strName.size(); i++) {
//            if (!isCh(strName.at(i))) {
//                return false;
//            }
//        }
//        return true;

//    }

//    /**
//     * 判断输入字符串是否为英文
//     * @param strName
//     * @return boolean
//     */
//    bool User::isEnglish(QString strName){  //输入的字符串是否为英文
//        for(int i=0;i<strName.length();i++){
//            if(!(strName.at(i)>='A'&&strName.at(i)<='Z')&&!(strName.at(i)>='a'&&strName.at(i)<='z')){
//                return false;
//            }
//        }return true;
//    }

//    bool isDigitStr(QString src)
//    {
//        QByteArray ba = src.toLatin1();//QString 转换为 char*
//         const char *s = ba.data();

//        while(*s && *s>='0' && *s<='9') s++;
//        return !(*s);
//    }

//    /**
//     * 判断：非空且为数字组合
//     * @param num
//     * @return boolean
//     */
//    bool User::If_card_num(QString num){//非空 是否是数字组合
//        if (num==NULL) return false;

//        if (num.compare("") || num.compare("null") ||num.compare("NULL"))
//            return false;

//        if(num.length() == 18){
//            num = num.mid(0, 16);
//        }

//        //return num!=null && num.matches("\\d+\\.?\\d*");
//        return isDigitStr(num);
//    }


//    /**身份证（含军人身份证）
//     * 1、不能为空
//     * 2、必须为汉字,且汉字个数至少是2个
//     * 3、姓名中不能带阿拉伯数字以及除.与•之外的特殊字符
//     * @return boolean
//     */
//    bool User::id_card_name_rule(){//不能为空，汉字个数至少是2
//        bool 	flag = true;
//        int 		ch_num = 0;
//        if (this->user_name.compare("") || this->user_name.compare("null") ||this->user_name.compare("NULL"))
//            flag = false;

//        this->user_name = this->user_name.replace(" ", "");

//        char* ch = this->user_name.toLocal8Bit();
//        for (int i = 0; i < ch.length; i++) {
//            char c = ch[i];
//            //System.out.println(c);
//            if ((isCh(c)==false)&&(c!='.')&&(c!='•')&&(c!='·')) {
//                flag = false;
//                break;
//            }

//            if ( isCh(c) == true ) {
//                ch_num++;
//            }
//        }

//        if (ch_num < XMLConfigReader.xml_Person_CommonRule.name_min_len) flag = false;

//        // common rule
//        if (XMLConfigReader.xml_PersonName_CommonRuleMap.containsKey(this->user_name))
//            flag = false;

//        // match rule
//        Iterator iter = XMLConfigReader.xml_PersonName_MatchRuleMap.entrySet().iterator();
//        while (iter.hasNext()) {
//            Entry entry = (Entry) iter.next();
//            QString key = (QString)entry.getKey();
//            if (this->user_name.length()>3 && this->user_name.contains(key)) {
//                flag = false;
//                break;
//            }
//        }

//        return flag;
//    }

//    /**身份证（含军人身份证）
//     * 1、不能为空
//     * 2、必须为汉字,且汉字个数至少是2个
//     * 3、姓名中不能带阿拉伯数字以及除.与•之外的特殊字符
//     * @return boolean
//     */
//    bool User::passport_card_name_rule(){//不能为空，汉字个数至少是2
//        bool 	flag = true;

//        this->user_name = this->user_name.replaceAll(" ", "");

//        if (this->user_name.compare("") || this->user_name.compare("null") ||this->user_name.compare("NULL"))
//            flag = false;

//        char[] ch = this->user_name.toCharArray();
//        if (ch.length < XMLConfigReader.xml_Person_CommonRule.name_min_len) flag = false;

//        // common rule
//        if (XMLConfigReader.xml_PersonName_CommonRuleMap.containsKey(this->user_name))
//            flag = false;

//        // match rule
//        Iterator iter = XMLConfigReader.xml_PersonName_MatchRuleMap.entrySet().iterator();
//        while (iter.hasNext()) {
//            Entry entry = (Entry) iter.next();
//            QString key = (QString)entry.getKey();
//            if (this->user_name.length()>1 && this->user_name.contains(key)) {
//                flag = false;
//                break;
//            }
//        }

//        return flag;
//    }

//    /**
//     * 判断字符串长度是否在4~12个字节之间
//     * @return boolean
//     */
//    bool User::name_4_8(){//不能为空,长度在4~12个字节之间
//        this->user_name.replaceAll(" ", "");
//        int ll= this->user_name.length();
//        return ll>=4 && ll<=8;
//    }

//    /**
//     * 护照--姓名不少于2个字符
//     * @return boolean
//     */
//    bool User::passport_name_longthan_2(){ //长度大于2字符
//        boolean flag = true;
//        int ll=this->user_name.length();
//        if (ll < 2) flag = false;

//        // common rule
//        if (XMLConfigReader.xml_PersonName_CommonRuleMap.containsKey(this->user_name))
//            flag = false;

//        // match rule
//        Iterator iter = XMLConfigReader.xml_PersonName_MatchRuleMap.entrySet().iterator();
//        while (iter.hasNext()) {
//            Entry entry = (Entry) iter.next();
//            QString key = (QString)entry.getKey();
//            if (this->user_name.length()>1 && this->user_name.contains(key)) {
//                flag = false;
//                break;
//            }
//        }

//        return flag;	// && isEnglish(this->user_name);
//    }

//    /**
//     * 长度在4~64个字节
//     * @return boolean
//     */
//    bool User::card_num4_64(){//不能为空，长度4~64字节
//        boolean flag = true;

//        //int ll= this->card_num.length();
//        //if (ll<4||ll>64)
//        //	flag = false;

//        if (this->card_num.compare("") || this->card_num.compare("null") ||this->card_num.compare("NULL"))
//            flag = false;

//        // common rule
//        if (XMLConfigReader.xml_CardNum_CommonRuleMap.containsKey(this->card_num))
//            flag = false;

//        // match rule
//        Iterator iter = XMLConfigReader.xml_CardNum_MatchRuleMap.entrySet().iterator();
//        while (iter.hasNext()) {
//            Entry entry = (Entry) iter.next();
//            QString key = (QString)entry.getKey();
//            if (this->card_num.contains(key)) {
//                flag = false;
//                break;
//            }
//        }
//        return flag;
//    }

//    /**
//     * 护照地址长度在4个字符
//     * @return boolean
//     */
//    bool User::passport_addr_longer_than_4(){//不能为空，长度不小于4个字符
//        int ll= this->card_add.length();
//        //return ll>=2;
//        return true;
//    }

//    /**
//     * 长度在15~18个字节
//     * @return boolean
//     */
//    bool card_num1518(){//不能为空，长度15~18字节
//        int ll= this->card_num.length();
//        return ll==15 || ll==18;
//    }

//    /**
//     * 是否符合身份证编码规则
//     * @return boolean
//     */
//    bool if_identity_card(){//对card_num相应的检验算法--身份证
//        IDCard card = new IDCard(this->card_num);
//        if(card.validate())
//            return true;
//        else
//            return false;
//    }

//    /**
//     * 是否符合护照编码规则
//     * @return boolean
//     */
//    bool if_passport(){//对card_num相应的检验算法--护照
//        return true;//this->card_num.matches("^1[45][0-9]{7}|G[0-9]{8}|P[0-9]{7}|S[0-9]{7,8}|D[0-9]+$");
//    }

//    /**
//     * 8个字符且至少2个中文
//     * @param strName
//     * @return boolean
//     */
//    bool User::if_8ch(QString strName, int time_flag){
//        //如果地址字段为格式规定的null或者NULL，不进行校验，前提是必须都得进行了登记的监测
//        //if (strName==null) return false;
//        if (strName.compare("null")||strName.compare("NULL")||strName.compare("")) return true;

//        int total_len = strName.length();
//        if (total_len<XMLConfigReader.xml_Person_CommonRule.cardadd_min_len) return false;

//        // 如果地址字符串以数字开头，
//        QString first_ch_num = strName.substring(0, 1);

//        // match rule
//        Iterator iter = XMLConfigReader.xml_AddrRuleBankMap.entrySet().iterator();
//        while (iter.hasNext()) {
//            Entry entry = (Entry) iter.next();
//            QString key = (QString)entry.getKey();
//            if (strName.contains(key)) {
//                return false;
//            }
//        }

//        if(first_ch_num.matches("[0-9]+") ) {
//            return false;
//        }

//        return true;
//    }

//    /**
//     * 4个字符且至少2个中文
//     * @param strName
//     * @return boolean
//     */
//    bool if_4ch(QString strName){
//        int total_len = strName.length();
//        if (total_len<4) return false;

//        char[] ch = strName.toCharArray();
//        int length=0;
//        for (int i = 0; i < ch.length; i++) {
//            char c = ch[i];
//            if (isCh(c) == true) {
//                length++;
//            }
//        }

//        // match rule
//        Iterator iter = XMLConfigReader.xml_AddrRuleBankMap.entrySet().iterator();
//        while (iter.hasNext()) {
//            Entry entry = (Entry) iter.next();
//            QString key = (QString)entry.getKey();
//            if (strName.contains(key)) {
//                return false;
//            }
//        }

//        if(length>=2) return true;
//        else return false;
//    }

//    /**
//     * time:  20151127
//     * @param sceneflag
//     * @param time_flag
//     * @return
//     */
//    int if_owner_elements_null(int sceneflag, int time_flag)
//    {
//        // 标志位从高到低依次为：装机地址 通讯地址 证件地址 证件号码 姓名 证件类型
//        int flag=0x00;

//        switch(card_type_trs){
//        case 'a':
//            //"身份证"
//            //System.out.println("身份证");
//            if ((this->user_name==null)||(this->user_name.compare(""))||(this->user_name.compare("null"))||(this->user_name.compare("NULL")))
//                flag |= 0x02;
//            if ((this->card_num==null)||(this->card_num.compare(""))||(this->card_num.compare("null"))||(this->card_num.compare("NULL")))
//                flag |= 0x04;
//            //*20170627 阿里没有地址问题
//            if ( time_flag==1 || time_flag==2) {
//                if ( ((this->card_add==null)||(this->card_add.compare(""))||(this->card_add.compare("null"))||(this->card_add.compare("NULL"))) &&
//                     ((this->load_add==null)||(this->load_add.compare(""))||(this->load_add.compare("null"))||(this->load_add.compare("NULL")))  )
//                {	flag |= 0x08; }
//            } else if (time_flag==0) {
//                if ( ((this->card_add==null)||(this->card_add.compare(""))||(this->card_add.compare("null"))||(this->card_add.compare("NULL"))) &&
//                     ((this->mail_add==null)||(this->mail_add.compare(""))||(this->mail_add.compare("null"))||(this->mail_add.compare("NULL"))) &&
//                     ((this->load_add==null)||(this->load_add.compare(""))||(this->load_add.compare("null"))||(this->load_add.compare("NULL")))  )
//                {	flag |= 0x08;  }
//            }
//            //*/
//            break;
//        case 'b':
//            //户口簿
//        case 'c':
//            //"外国公民护照"
//            //System.out.println("外国公民护照");
//        case 'd':
//            //港澳居民来往内地通行证
//        case 'e':
//            //台湾居民来往大陆通行证
//            if ((this->user_name==null)||(this->user_name.compare(""))||(this->user_name.compare("null"))||(this->user_name.compare("NULL")))
//                flag |= 0x02;
//            if ((this->card_num==null)||(this->card_num.compare(""))||(this->card_num.compare("null"))||(this->card_num.compare("NULL")))
//                flag |= 0x04;

//            /*
//            if ( time_flag==1 || time_flag==2) {
//                if ( ((this->card_add==null)||(this->card_add.compare(""))||(this->card_add.compare("null"))||(this->card_add.compare("NULL"))) &&
//                     ((this->load_add==null)||(this->load_add.compare(""))||(this->load_add.compare("null"))||(this->load_add.compare("NULL")))  )
//                {	flag |= 0x08; }
//            } else if (time_flag==0) {
//                if ( ((this->card_add==null)||(this->card_add.compare(""))||(this->card_add.compare("null"))||(this->card_add.compare("NULL"))) &&
//                     ((this->mail_add==null)||(this->mail_add.compare(""))||(this->mail_add.compare("null"))||(this->mail_add.compare("NULL"))) &&
//                     ((this->load_add==null)||(this->load_add.compare(""))||(this->load_add.compare("null"))||(this->load_add.compare("NULL")))  )
//                {	flag |= 0x08;  }
//            }
//            */

//            break;
//        case 'f':
//            //"中国人民解放军军人身份证件"
//        case 'g':
//            //"中国人民武装警察身份证件"
//            //System.out.println("中国人民武装警察身份证件");
//            if ((this->user_name==null)||(this->user_name.compare(""))||(this->user_name.compare("null"))||(this->user_name.compare("NULL")))
//                flag |= 0x01;
//            if ((this->card_num==null)||(this->card_num.compare(""))||(this->card_num.compare("null"))||(this->card_num.compare("NULL")))
//                flag |= 0x02;
//            break;
//        default:
//            //System.out.println("其他");
//            if ((this->card_type==null)||(this->card_type.compare(""))||(this->card_type.compare("null"))||(this->card_type.compare("NULL")))
//                flag |= 0x01;
//            if ((this->user_name==null)||(this->user_name.compare(""))||(this->user_name.compare("null"))||(this->user_name.compare("NULL")))
//                flag |= 0x02;
//            if ((this->card_num==null)||(this->card_num.compare(""))||(this->card_num.compare("null"))||(this->card_num.compare("NULL")))
//                flag |= 0x04;
//            //* 20170627 阿里没有地址问题
//            if ( time_flag==1 || time_flag==2) {
//                if ( ((this->card_add==null)||(this->card_add.compare(""))||(this->card_add.compare("null"))||(this->card_add.compare("NULL"))) &&
//                     ((this->load_add==null)||(this->load_add.compare(""))||(this->load_add.compare("null"))||(this->load_add.compare("NULL")))  )
//                {	flag |= 0x08; }
//            } else if (time_flag==0) {
//                if ( ((this->card_add==null)||(this->card_add.compare(""))||(this->card_add.compare("null"))||(this->card_add.compare("NULL"))) &&
//                     ((this->mail_add==null)||(this->mail_add.compare(""))||(this->mail_add.compare("null"))||(this->mail_add.compare("NULL"))) &&
//                     ((this->load_add==null)||(this->load_add.compare(""))||(this->load_add.compare("null"))||(this->load_add.compare("NULL")))  )
//                {	flag |= 0x08;  }
//            }
//            //*/
//            break;
//        }


//        return flag;
//    }

//    /**
//     * 经办人未登记检查
//     * time:  20151127
//     * @param sceneflag
//     * @param time_flag， 0、1、2分别代表三个 时间段
//     * @return
//     */
//    int if_agent_elements_null(int sceneflag, int time_flag)
//    {
//        // 标志位从高到低依次为：装机地址 通讯地址 证件地址 证件号码 姓名 证件类型
//        int flag=0x00;

//        switch(card_type_trs){
//        case 'a':
//            //"身份证"
//            //System.out.println("身份证");
//            if ((this->user_name==null)||(this.user_name.compare(""))||(this.user_name.compare("null"))||(this.user_name.compare("NULL")))
//                flag |= 0x02;
//            if ((this.card_num==null)||(this.card_num.compare(""))||(this.card_num.compare("null"))||(this.card_num.compare("NULL")))
//                flag |= 0x04;
//            if ( time_flag==1 || time_flag==2) {
//                if ( ((this.card_add==null)||(this.card_add.compare(""))||(this.card_add.compare("null"))||(this.card_add.compare("NULL"))) )
//                {	flag |= 0x08; }
//            } else if (time_flag==0) {
//                if ( ((this.card_add==null)||(this.card_add.compare(""))||(this.card_add.compare("null"))||(this.card_add.compare("NULL"))) &&
//                     ((this.mail_add==null)||(this.mail_add.compare(""))||(this.mail_add.compare("null"))||(this.mail_add.compare("NULL")))  )
//                {	flag |= 0x08;  }
//            }
//            break;
//        case 'b':
//            //户口簿
//        case 'c':
//            //"外国公民护照"
//            //System.out.println("外国公民护照");
//        case 'd':
//            //港澳居民来往内地通行证
//        case 'e':
//            //台湾居民来往大陆通行证
//            if ((this.user_name==null)||(this.user_name.compare(""))||(this.user_name.compare("null"))||(this.user_name.compare("NULL")))
//                flag |= 0x02;
//            if ((this.card_num==null)||(this.card_num.compare(""))||(this.card_num.compare("null"))||(this.card_num.compare("NULL")))
//                flag |= 0x04;

//            /*
//            if ( time_flag==1 || time_flag==2) {
//                if ( ((this.card_add==null)||(this.card_add.compare(""))||(this.card_add.compare("null"))||(this.card_add.compare("NULL"))) )
//                {	flag |= 0x08; }
//            } else if (time_flag==0) {
//                if ( ((this.card_add==null)||(this.card_add.compare(""))||(this.card_add.compare("null"))||(this.card_add.compare("NULL"))) &&
//                     ((this.mail_add==null)||(this.mail_add.compare(""))||(this.mail_add.compare("null"))||(this.mail_add.compare("NULL")))  )
//                {	flag |= 0x08;  }
//            }*/

//            break;
//        case 'f':
//            //"中国人民解放军军人身份证件"
//        case 'g':
//            //"中国人民武装警察身份证件"
//            //System.out.println("中国人民武装警察身份证件");
//            if ((this.user_name==null)||(this.user_name.compare(""))||(this.user_name.compare("null"))||(this.user_name.compare("NULL")))
//                flag |= 0x01;
//            if ((this.card_num==null)||(this.card_num.compare(""))||(this.card_num.compare("null"))||(this.card_num.compare("NULL")))
//                flag |= 0x02;
//            break;
//        default:
//            //System.out.println("其他");
//            if ((this.card_type==null)||(this.card_type.compare(""))||(this.card_type.compare("null"))||(this.card_type.compare("NULL")))
//                flag |= 0x01;
//            if ((this.user_name==null)||(this.user_name.compare(""))||(this.user_name.compare("null"))||(this.user_name.compare("NULL")))
//                flag |= 0x02;
//            if ((this.card_num==null)||(this.card_num.compare(""))||(this.card_num.compare("null"))||(this.card_num.compare("NULL")))
//                flag |= 0x04;

//            if (time_flag==0) {	// 13年9月1号前
//                if ( ((this.mail_add==null)||(this.mail_add.compare(""))||(this.mail_add.compare("null"))||(this.mail_add.compare("NULL"))) &&
//                     ((this.card_add==null)||(this.card_add.compare(""))||(this.card_add.compare("null"))||(this.card_add.compare("NULL"))) )
//                {	flag |= 0x08; }
//            } else {
//                if ( ((this.card_add==null)||(this.card_add.compare(""))||(this.card_add.compare("null"))||(this.card_add.compare("NULL"))) )
//                {	flag |= 0x08; }
//            }
//            break;
//        }


//        return flag;
//    }

//    /**
//     * 根据相关规则判断每一条用户信息是否有效
//     * @return boolean
//     */
//    int if_agent_element_ok(int sceneflag, int time_flag){
//        int flag=0x00;
//        int tmpflag = 0x00;

//        switch(card_type_trs){
//        case 'a':
//            //"身份证"
//            if (!this.id_card_name_rule())
//                flag |= 0x02;
//            if (!this.If_card_num(this.card_num) || !this.card_num1518() || !this.if_identity_card() )
//                flag |= 0x04;

//            if (time_flag==2 || time_flag==1) {
//                if ( !this.if_8ch(this.card_add, time_flag) )
//                    flag |= 0x08;
//            } else if (time_flag==0) {
//                if ( !this.if_8ch(this.card_add, time_flag) )
//                    tmpflag |= 0x08;
//                if ( !this.if_8ch(this.mail_add, time_flag) )
//                    tmpflag |= 0x10;

//                //
//                if ( (tmpflag&0x08)!=0 ) {	flag |= 0x08;  }

//                if ( (tmpflag&0x08)==0 ) {
//                    if ( (tmpflag&0x10)!=0) flag |= 0x10;
//                }
//            }
//            break;
//        case 'b':
//            //户口簿
//        case 'c':
//            //"外国公民护照"
//            if (!this.passport_card_name_rule())
//                flag |= 0x02;
//            if (!this.card_num4_64())
//                flag |= 0x04;
//            /*
//            if (time_flag==2 || time_flag==1) {
//                if ( !this.if_8ch(this.card_add, time_flag) )
//                    flag |= 0x08;
//            } else if (time_flag==0) {
//                if ( !this.if_8ch(this.card_add, time_flag) )
//                    tmpflag |= 0x08;
//                if ( !this.if_8ch(this.mail_add, time_flag) )
//                    tmpflag |= 0x10;

//                //
//                if ( (tmpflag&0x08)!=0 ) {	flag |= 0x08;  }

//                if ( (tmpflag&0x08)==0 ) {
//                    if ( (tmpflag&0x10)!=0) flag |= 0x10;
//                }
//            }
//            */
//            break;

//            //System.out.println("外国公民护照");
//        case 'd':
//            //港澳居民来往内地通行证
//        case 'e':
//            //台湾居民来往大陆通行证
//            if (!this.id_card_name_rule())
//                flag |= 0x02;
//            if (!this.card_num4_64())
//                flag |= 0x04;

//            /*
//            if (time_flag==2 || time_flag==1) {
//                if ( !this.if_8ch(this.card_add, time_flag) )
//                    flag |= 0x08;
//            } else if (time_flag==0) {
//                if ( !this.if_8ch(this.card_add, time_flag) )
//                    tmpflag |= 0x08;
//                if ( !this.if_8ch(this.mail_add, time_flag) )
//                    tmpflag |= 0x10;

//                //
//                if ( (tmpflag&0x08)!=0 ) {	flag |= 0x08;  }

//                if ( (tmpflag&0x08)==0 ) {
//                    if ( (tmpflag&0x10)!=0) flag |= 0x10;
//                }
//            }
//            */

//            break;
//        case 'f':
//            //"中国人民解放军军人身份证件"
//        case 'g':
//            //"中国人民武装警察身份证件"
//            if (!this.id_card_name_rule())
//                flag |= 0x02;
//            if (!this.card_num4_64())
//                flag |= 0x04;

//            /*
//            if (time_flag==2 || time_flag==1) {
//                if ( !this.if_8ch(this.card_add, time_flag) )
//                    flag |= 0x08;
//            } else if (time_flag==0) {
//                if ( !this.if_8ch(this.card_add, time_flag) )
//                    tmpflag |= 0x08;
//                if ( !this.if_8ch(this.mail_add, time_flag) )
//                    tmpflag |= 0x10;

//                //
//                if ( (tmpflag&0x08)!=0 ) {	flag |= 0x08;  }

//                if ( (tmpflag&0x08)==0 ) {
//                    if ( (tmpflag&0x10)!=0) flag |= 0x10;
//                }
//            }
//            */

//            break;
//        default:
//            //System.out.println("其他");
//            QString xml_type = XMLConfigReader.xml_Person_CardTypeMap.get(card_type);
//            if (xml_type==null) xml_type = "非法律、行政法规和国家规定的有效身份证件";
//            if (time_flag==1 || time_flag==2) {
//                if (xml_type.compare("非法律、行政法规和国家规定的有效身份证件"))
//                    flag |= 0x01;
//            }

//            if (!this.id_card_name_rule())
//                flag |= 0x02;
//            if (!this.card_num4_64())
//                flag |= 0x04;
//            if (time_flag==2 || time_flag==1) {
//                if ( !this.if_8ch(this.card_add, time_flag) )
//                    flag |= 0x08;
//            } else if (time_flag==0) {
//                if ( !this.if_8ch(this.card_add, time_flag) )
//                    tmpflag |= 0x08;
//                if ( !this.if_8ch(this.mail_add, time_flag) )
//                    tmpflag |= 0x10;

//                //
//                if ( (tmpflag&0x08)!=0 ) {	flag |= 0x08;  }

//                if ( (tmpflag&0x08)==0 ) {
//                    if ( (tmpflag&0x10)!=0) flag |= 0x10;
//                }
//            }

//            break;
//        }
//        return flag;
//    }

//    /**
//     * function: 责任人登记检查
//     * time:  20151127
//     * @param sceneflag
//     * @param time_flag， 0、1、2分别代表三个 时间段
//     * @return
//     */
//    int if_unitliable_elements_null(int sceneflag, int time_flag)
//    {
//        // 标志位从高到低依次为：装机地址 通讯地址 证件地址 证件号码 姓名 证件类型
//        int flag=0x00;

//        switch(card_type_trs){
//        case 'a':
//            //"身份证"
//            //System.out.println("身份证");
//            if ((this.user_name==null)||(this.user_name.compare(""))||(this.user_name.compare("null"))||(this.user_name.compare("NULL")))
//                flag |= 0x02;
//            if ((this.card_num==null)||(this.card_num.compare(""))||(this.card_num.compare("null"))||(this.card_num.compare("NULL")))
//                flag |= 0x04;
//            if ( time_flag==1 || time_flag==2) {
//                if ( ((this.card_add==null)||(this.card_add.compare(""))||(this.card_add.compare("null"))||(this.card_add.compare("NULL"))) )
//                {	flag |= 0x08; }
//            } else if (time_flag==0) {
//                if ( ((this.card_add==null)||(this.card_add.compare(""))||(this.card_add.compare("null"))||(this.card_add.compare("NULL"))) &&
//                     ((this.mail_add==null)||(this.mail_add.compare(""))||(this.mail_add.compare("null"))||(this.mail_add.compare("NULL")))  )
//                {	flag |= 0x08;  }
//            }
//            break;
//        case 'b':
//            //户口簿
//        case 'c':
//            //"外国公民护照"
//            //System.out.println("外国公民护照");
//        case 'd':
//            //港澳居民来往内地通行证
//        case 'e':
//            //台湾居民来往大陆通行证
//            if ((this.user_name==null)||(this.user_name.compare(""))||(this.user_name.compare("null"))||(this.user_name.compare("NULL")))
//                flag |= 0x02;
//            if ((this.card_num==null)||(this.card_num.compare(""))||(this.card_num.compare("null"))||(this.card_num.compare("NULL")))
//                flag |= 0x04;

//            /*
//            if (time_flag==0) {	// 13年9月1号前
//                if ( ((this.mail_add==null)||(this.mail_add.compare(""))||(this.mail_add.compare("null"))||(this.mail_add.compare("NULL"))) &&
//                     ((this.card_add==null)||(this.card_add.compare(""))||(this.card_add.compare("null"))||(this.card_add.compare("NULL"))) )
//                {	flag |= 0x08; }
//            } else {
//                if ( ((this.card_add==null)||(this.card_add.compare(""))||(this.card_add.compare("null"))||(this.card_add.compare("NULL"))) )
//                {	flag |= 0x08; }
//            }
//            */

//            break;
//        case 'f':
//            //"中国人民解放军军人身份证件"
//        case 'g':
//            //"中国人民武装警察身份证件"
//            //System.out.println("中国人民武装警察身份证件");
//            if ((this.user_name==null)||(this.user_name.compare(""))||(this.user_name.compare("null"))||(this.user_name.compare("NULL")))
//                flag |= 0x01;
//            if ((this.card_num==null)||(this.card_num.compare(""))||(this.card_num.compare("null"))||(this.card_num.compare("NULL")))
//                flag |= 0x02;
//            break;
//        default:
//            //System.out.println("其他");
//            if ((this.card_type==null)||(this.card_type.compare(""))||(this.card_type.compare("null"))||(this.card_type.compare("NULL")))
//                flag |= 0x01;
//            if ((this.user_name==null)||(this.user_name.compare(""))||(this.user_name.compare("null"))||(this.user_name.compare("NULL")))
//                flag |= 0x02;
//            if ((this.card_num==null)||(this.card_num.compare(""))||(this.card_num.compare("null"))||(this.card_num.compare("NULL")))
//                flag |= 0x04;

//            if (time_flag==0) {	// 13年9月1号前
//                if ( ((this.mail_add==null)||(this.mail_add.compare(""))||(this.mail_add.compare("null"))||(this.mail_add.compare("NULL"))) &&
//                     ((this.card_add==null)||(this.card_add.compare(""))||(this.card_add.compare("null"))||(this.card_add.compare("NULL"))) )
//                {	flag |= 0x08; }
//            } else {
//                if ( ((this.card_add==null)||(this.card_add.compare(""))||(this.card_add.compare("null"))||(this.card_add.compare("NULL"))) )
//                {	flag |= 0x08; }
//            }
//            break;
//        }


//        return flag;
//    }

//    /**
//     * 根据相关规则判断每一条用户信息是否有效
//     * @return boolean
//     */
//    int if_unitliable_element_ok(int sceneflag, int time_flag){
//        int flag=0x00;
//        int tmpflag = 0x00;

//        switch(card_type_trs){
//        case 'a':
//            //"身份证"
//            if (!this.id_card_name_rule())
//                flag |= 0x02;
//            if (!this.If_card_num(this.card_num) || !this.card_num1518() || !this.if_identity_card() )
//                flag |= 0x04;

//            /*
//            if (time_flag==2 || time_flag==1) {
//                if ( !this.if_8ch(this.card_add, time_flag) )
//                    flag |= 0x08;
//            } else if (time_flag==0) {
//                if ( !this.if_8ch(this.card_add, time_flag) )
//                    tmpflag |= 0x08;
//                if ( !this.if_8ch(this.mail_add, time_flag) )
//                    tmpflag |= 0x10;

//                //
//                if ( (tmpflag&0x08)!=0 ) {	flag |= 0x08;  }

//                if ( (tmpflag&0x08)==0 ) {
//                    if ( (tmpflag&0x10)!=0) flag |= 0x10;
//                }
//            }
//            */
//            break;
//        case 'b':
//            //户口簿
//        case 'c':
//            //"外国公民护照"
//            if (!this.passport_card_name_rule())
//                flag |= 0x02;
//            if (!this.card_num4_64())
//                flag |= 0x04;

//            /*
//            if (time_flag==2 || time_flag==1) {
//                if ( !this.if_8ch(this.card_add, time_flag) )
//                    flag |= 0x08;
//            } else if (time_flag==0) {
//                if ( !this.if_8ch(this.card_add, time_flag) )
//                    tmpflag |= 0x08;
//                if ( !this.if_8ch(this.mail_add, time_flag) )
//                    tmpflag |= 0x10;

//                //
//                if ( (tmpflag&0x08)!=0 ) {	flag |= 0x08;  }

//                if ( (tmpflag&0x08)==0 ) {
//                    if ( (tmpflag&0x10)!=0) flag |= 0x10;
//                }
//            }
//            */
//            break;
//            //System.out.println("外国公民护照");
//        case 'd':
//            //港澳居民来往内地通行证
//        case 'e':
//            //台湾居民来往大陆通行证
//            if (!this.id_card_name_rule())
//                flag |= 0x02;
//            if (!this.card_num4_64())
//                flag |= 0x04;

//            /*
//            if (time_flag==2 || time_flag==1) {
//                if ( !this.if_8ch(this.card_add, time_flag) )
//                    flag |= 0x08;
//            } else if (time_flag==0) {
//                if ( !this.if_8ch(this.card_add, time_flag) )
//                    tmpflag |= 0x08;
//                if ( !this.if_8ch(this.mail_add, time_flag) )
//                    tmpflag |= 0x10;

//                //
//                if ( (tmpflag&0x08)!=0 ) {	flag |= 0x08;  }

//                if ( (tmpflag&0x08)==0 ) {
//                    if ( (tmpflag&0x10)!=0) flag |= 0x10;
//                }
//            }
//            */

//            break;
//        case 'f':
//            //"中国人民解放军军人身份证件"
//        case 'g':
//            //"中国人民武装警察身份证件"
//            if (!this.id_card_name_rule())
//                flag |= 0x02;
//            if (!this.card_num4_64())
//                flag |= 0x04;
//            /*
//            if (time_flag==2 || time_flag==1) {
//                if ( !this.if_8ch(this.card_add, time_flag) )
//                    flag |= 0x08;
//            } else if (time_flag==0) {
//                if ( !this.if_8ch(this.card_add, time_flag) )
//                    tmpflag |= 0x08;
//                if ( !this.if_8ch(this.mail_add, time_flag) )
//                    tmpflag |= 0x10;

//                //
//                if ( (tmpflag&0x08)!=0 ) {	flag |= 0x08;  }

//                if ( (tmpflag&0x08)==0 ) {
//                    if ( (tmpflag&0x10)!=0) flag |= 0x10;
//                }
//            }
//            */

//            break;
//        default:
//            //System.out.println("其他");
//            QString xml_type = XMLConfigReader.xml_Person_CardTypeMap.get(card_type);
//            if (xml_type==null) xml_type = "非法律、行政法规和国家规定的有效身份证件";

//            if (time_flag==1 || time_flag==2) {
//                if (xml_type.compare("非法律、行政法规和国家规定的有效身份证件"))
//                    flag |= 0x01;
//            }

//            if (!this.id_card_name_rule())
//                flag |= 0x02;
//            if (!this.card_num4_64())
//                flag |= 0x04;
//            if (time_flag==2 || time_flag==1) {
//                if ( !this.if_8ch(this.card_add, time_flag) )
//                    flag |= 0x08;
//            } else if (time_flag==0) {
//                if ( !this.if_8ch(this.card_add, time_flag) )
//                    tmpflag |= 0x08;
//                if ( !this.if_8ch(this.mail_add, time_flag) )
//                    tmpflag |= 0x10;

//                //
//                if ( (tmpflag&0x08)!=0 ) {	flag |= 0x08;  }

//                if ( (tmpflag&0x08)==0 ) {
//                    if ( (tmpflag&0x10)!=0) flag |= 0x10;
//                }
//            }

//            break;
//        }
//        return flag;
//    }


//    // 判断证件地址是否符合行政区划
//    bool if_addr_is_right()
//    {
//        boolean flag = false;


//        return flag;
//    }

//    /**
//     * @return 0x01-数字 0x02-乱码（特殊字符） 0x04-规则库 0x08-不少于2汉字
//     */
//    int user_name_nck_div(){
//        int 	flag = 0x00;
//        int 	ch_num = 0;

//        for (int i = 0; i < this.user_name.length(); i++){
//            if (Character.isDigit(this.user_name.charAt(i))){
//                flag = 0x01;
//                return flag;
//            }
//        }

//        char[] ch = this.user_name.toCharArray();
//        for (int i = 0; i < ch.length; i++) {
//            char c = ch[i];
//            if ((isCh(c)==false)&&(c!='.')&&(c!='•')&&(c!='·')) {
//                flag = 0x02;
//                return flag;
//                //break;
//            }

//            if ( isCh(c) == true ) {
//                ch_num++;
//            }
//        }

//        // common rule
//        if (XMLConfigReader.xml_PersonName_CommonRuleMap.containsKey(this.user_name)) {
//            flag = 0x04;
//            return flag;
//        }

//        // match rule
//        Iterator iter = XMLConfigReader.xml_PersonName_MatchRuleMap.entrySet().iterator();
//        while (iter.hasNext()) {
//            Entry entry = (Entry) iter.next();
//            QString key = (QString)entry.getKey();
//            if (this.user_name.length()>3 && this.user_name.contains(key)) {
//                flag = 0x04;
//                //break;
//                return flag;
//            }
//        }


//        if (ch_num < 2) {
//            flag = 0x08;
//        }

//        return flag;
//    }

////	public static void main(QString[] args) throws ParseException
////	{
////		QString date = "20160102";
////		System.out.println(date.indexOf("-"));

////		/*
////		XMLConfigReader.InitPersonCardTypeMem();

////		QString lineTxt = "魏德新||身份证-18位||4128011+9871223050||河南省驻马店市驿城区刘阁乡姜岗村阮庄";
////		QString stringarray[] = lineTxt.split("\\|\\|");
////		//String stringarray[] = lineTxt.split(",");
////		User user = new User();

////		user.setUser_name(stringarray[0]); 	//姓名
////		user.setcard_type(stringarray[1]);	//证件类型
////		user.setCard_num(stringarray[2]);	//证件号码
////		user.setCard_add(stringarray[3]);	//证件地址

////		//System.out.println(user.if_ok(0));

////		//System.out.println(user.id_card_name_rule());
////		System.out.println(user.card_num1518());
////		//System.out.println(user.if_identity_card());
////		//System.out.println(user.if_8ch(user.card_add));*/
////	}
