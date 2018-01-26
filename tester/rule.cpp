#include "rule.h"

Rule::Rule()
{
    QList<QString> addr_rule;//rule-addr-person-unit.xml
    addr_rule.append("哈哈");
    QList<QString> match_rule;//rule-addr-person-unit.xml
    match_rule.append("");
    match_rule.append("省");
    match_rule.append("直辖市");
    match_rule.append("市");
    match_rule.append("自治区");
    match_rule.append("区");
    match_rule.append("地区");
    match_rule.append("州");
    match_rule.append("盟");
    match_rule.append("县");
    match_rule.append("旗");
    match_rule.append("乡");
    match_rule.append("镇");
    match_rule.append("苏木");
    match_rule.append("街道");
    match_rule.append("街");
    match_rule.append("道");
    match_rule.append("路");
    match_rule.append("巷");
    match_rule.append("胡同");
    match_rule.append("里弄");
    match_rule.append("里");
    match_rule.append("弄");
    match_rule.append("幢");
    match_rule.append("栋");
    match_rule.append("楼");
    match_rule.append("座");
    match_rule.append("单元");
    match_rule.append("室");
    match_rule.append("号");
    match_rule.append("村");
    match_rule.append("社区");
    match_rule.append("组");
    match_rule.append("嘎查");
    match_rule.append("门");
    match_rule.append("社");

    QList<QString> person_cardtypes;//config-cardtype.xml
    person_cardtypes.append("");

//        <!-- 以下为《工信部25号令》规定的个人办理电话用户真实身份信息登记时需出示有效证件 -->
//        <person-cardtypes category="个人证件">

//                <cardtype category="居民身份证">
                    person_cardtypes.append("01");
                    person_cardtypes.append("0");
                    person_cardtypes.append("身份证");
                    person_cardtypes.append("身份证迁移");
                    person_cardtypes.append("国内身份证");
                    person_cardtypes.append("IDCARD");
                    person_cardtypes.append("身份证-18位");
                    person_cardtypes.append("身份证(18位)");
                    person_cardtypes.append("身份证18位");
                    person_cardtypes.append("身份证15位");
                    person_cardtypes.append("公众证件-居民身份证");
                    person_cardtypes.append("公众证件―居民身份证");
                    person_cardtypes.append("居民身份证");
                    person_cardtypes.append("居民身份证(18位)");
                    person_cardtypes.append("居民身份证(15位)");
                    person_cardtypes.append("身份证");
                    person_cardtypes.append("0-本地身份证");
                    person_cardtypes.append("1-外地身份证");
                    person_cardtypes.append("IdCard");
                    person_cardtypes.append("IdTypeJSX");
                    person_cardtypes.append("101");
                    person_cardtypes.append("1");
                    person_cardtypes.append("2");
//                </cardtype>

//                <cardtype category="临时居民身份证">
                    person_cardtypes.append("临时身份证");
                    person_cardtypes.append("临时居民身份证");
                    person_cardtypes.append("41");
                    person_cardtypes.append("TempId");
//                </cardtype>

//                <cardtype category="户口薄">
                    person_cardtypes.append("户口簿");
                    person_cardtypes.append("户口薄");
                    person_cardtypes.append("公众证件―户口簿");
                    person_cardtypes.append("04");
                    person_cardtypes.append("G-户口簿");
                    person_cardtypes.append("公众证件-户口簿");
                    person_cardtypes.append("户口本");
                    person_cardtypes.append("IdTypeHKB");
                    person_cardtypes.append("HUKOUBU");
                    person_cardtypes.append("户口本（禁止新增）");
                    person_cardtypes.append("户口卡");
                    person_cardtypes.append("户口本迁移");
                    person_cardtypes.append("户口本/居住证");
//                </cardtype>

//                <cardtype category="中国人民解放军军人身份证件">
                    person_cardtypes.append("军官证");
                    person_cardtypes.append("02");
                    person_cardtypes.append("士官证");
                    person_cardtypes.append("士官证迁移");
                    person_cardtypes.append("军官证（禁止新增）");
                    person_cardtypes.append("军官证迁移");
                    person_cardtypes.append("C-军官证");
                    person_cardtypes.append("军官（士兵）证");
                    person_cardtypes.append("军人身份证件");
                    person_cardtypes.append("军人身份证");
                    person_cardtypes.append("公众证件-军人身份证");
                    person_cardtypes.append("103");
                    person_cardtypes.append("军人证");
                    person_cardtypes.append("海军证");
                    person_cardtypes.append("海军证迁移");
                    person_cardtypes.append("空军证");
                    person_cardtypes.append("空军证迁移");
                    person_cardtypes.append("士官证");
                    person_cardtypes.append("士兵证");
                    person_cardtypes.append("SoldierID");
                    person_cardtypes.append("PLA");
//                </cardtype>

//                <cardtype category="中国人民武装警察身份证件">
                    person_cardtypes.append("警官证");
                    person_cardtypes.append("警官证迁移");
                    person_cardtypes.append("09");
                    person_cardtypes.append("104");
                    person_cardtypes.append("警官证（禁止新增）");
                    person_cardtypes.append("H-警官证");
                    person_cardtypes.append("武装警察身份证件");
                    person_cardtypes.append("武装警察身份证");
                    person_cardtypes.append("公众证件―武装警察身份证");
                    person_cardtypes.append("武警身份证");
                    person_cardtypes.append("人民警察证");
                    person_cardtypes.append("PolicePaper");
//                </cardtype>

//                <cardtype category="港澳居民来往内地通行证">
                    person_cardtypes.append("港澳证");
                    person_cardtypes.append("港澳身份证");
                    person_cardtypes.append("澳门身份证");
                    person_cardtypes.append("香港身份证");
                    person_cardtypes.append("港澳居民内地通行证");
                    person_cardtypes.append("17");
                    person_cardtypes.append("港澳居民来往内地通行证");
                    person_cardtypes.append("港澳来往内地通行证");
                    person_cardtypes.append("港澳居民往来内地通行");
                    person_cardtypes.append("港澳台通行证");
                    person_cardtypes.append("公众证件―港澳居民往来内地通行");
                    person_cardtypes.append("107");
                    person_cardtypes.append("内地通行证（港澳）");
                    person_cardtypes.append("港澳居民往来内地通行证");
//                </cardtype>

//                <cardtype category="台湾居民来往大陆通行证">
                    person_cardtypes.append("台胞证");
                    person_cardtypes.append("台胞身份证");
                    person_cardtypes.append("台湾身份证");
                    person_cardtypes.append("台湾居民内地通行证");
                    person_cardtypes.append("台湾居民来往内地通行证");
                    person_cardtypes.append("台湾居民来往大陆通行证");
                    person_cardtypes.append("公众证件―台湾居民往来大陆通行证");
                    person_cardtypes.append("台湾来往大陆通行证");
                    person_cardtypes.append("台湾居民往来大陆通行证");
                    person_cardtypes.append("42");
                    person_cardtypes.append("108");
                    person_cardtypes.append("大陆通行证（台湾）");
//                </cardtype>

//                <cardtype category="外国公民护照">
                    person_cardtypes.append("105");
                    person_cardtypes.append("护照");
                    person_cardtypes.append("公众证件―护照");
                    person_cardtypes.append("护照迁移");
                    person_cardtypes.append("03");
                    person_cardtypes.append("公众证件-护照");
                    person_cardtypes.append("外国公民护照");
                    person_cardtypes.append("A-护照");
                    person_cardtypes.append("PASSPORT");
//                </cardtype>

//                <cardtype category="法律、行政法规和国家规定的其他有效身份证件">
                    person_cardtypes.append("-");
                    person_cardtypes.append("外交使馆照会");
                    person_cardtypes.append("部队番号证件");
                    person_cardtypes.append("照会");
//                </cardtype>

//                <cardtype category="非法律、行政法规和国家规定的有效身份证件">
                    person_cardtypes.append("驾驶证");
                    person_cardtypes.append("驾驶证迁移");
                    person_cardtypes.append("驾驶执照");
                    person_cardtypes.append("07");
                    person_cardtypes.append("驾驶证（禁止新增）");
                    person_cardtypes.append("教师证");
                    person_cardtypes.append("学生证");
                    person_cardtypes.append("学生证迁移");
                    person_cardtypes.append("05");
                    person_cardtypes.append("学生证（集客专用）");
                    person_cardtypes.append("B-学生证");
                    person_cardtypes.append("社保卡");
                    person_cardtypes.append("客户卡");
                    person_cardtypes.append("客户标识码");
                    person_cardtypes.append("老年证");
                    person_cardtypes.append("老人证");
                    person_cardtypes.append("其他");
                    person_cardtypes.append("其他证件迁移");
                    person_cardtypes.append("其它");
                    person_cardtypes.append("Z-其它");
                    person_cardtypes.append("其它证件");
                    person_cardtypes.append("部队干部离休证");
                    person_cardtypes.append("户口本/居住证");
                    person_cardtypes.append("士兵证迁移");
                    person_cardtypes.append("工作证");
                    person_cardtypes.append("工作证迁移");
                    person_cardtypes.append("E");
                    person_cardtypes.append("18");
                    person_cardtypes.append("暂住证");
                    person_cardtypes.append("11");
                    person_cardtypes.append("回乡证");
                    person_cardtypes.append("10");
                    person_cardtypes.append("残疾证");
                    person_cardtypes.append("08");
                    person_cardtypes.append("市政府人才居住证");
                    person_cardtypes.append("13");
                    person_cardtypes.append("房产证");
                    person_cardtypes.append("房产证迁移");
                    person_cardtypes.append("15");
                    person_cardtypes.append("记者证");
                    person_cardtypes.append("19");
                    person_cardtypes.append("医疗证");
                    person_cardtypes.append("居留证");
                    person_cardtypes.append("22");
                    person_cardtypes.append("虚拟证件");
                    person_cardtypes.append("文职官员证");
                    person_cardtypes.append("文职证");
                    person_cardtypes.append("23");
                    person_cardtypes.append("军警单位相关证明");
                    person_cardtypes.append("当地办事处登记证");
                    person_cardtypes.append("预开户编号");
                    person_cardtypes.append("测试号码证件");
                    person_cardtypes.append("测试证");
                    person_cardtypes.append("99");
                    person_cardtypes.append("数固客户编码");
                    person_cardtypes.append("华侨证明（区县级）");
                    person_cardtypes.append("实名制待核实");
                    person_cardtypes.append("F-代扣号");
                    person_cardtypes.append("测试号码证件类型");
                    person_cardtypes.append("干部证");
                    person_cardtypes.append("干部证迁移");
                    person_cardtypes.append("社会保险号（禁止新增）");
                    person_cardtypes.append("其他（禁止新增）");
                    person_cardtypes.append("199");
                    person_cardtypes.append("20");
                    person_cardtypes.append("PPC用户卡号");
                    person_cardtypes.append("PPC用户卡号迁移");
                    person_cardtypes.append("代理商号");
                    person_cardtypes.append("银行帐户");
                    person_cardtypes.append("证件迁移");
                    person_cardtypes.append("银行帐户（禁止新增）");
//                </cardtype>

//        </person-cardtypes>

    QList<QString> unit_cardtypes;
    unit_cardtypes.append("");

//        <!-- 以下为《工信部25号令》规定的单位办理电话用户真实身份信息登记时需出示有效证件 -->
//        <unit-cardtypes category="单位证件">

//                <cardtype category="组织机构代码证">
                    unit_cardtypes.append("企业组织机构代码证");
                    unit_cardtypes.append("集团证件―组织机构代码证原件或加盖公章的组织机构代码证复印件");
                    unit_cardtypes.append("企业组织机构代码");
                    unit_cardtypes.append("中华人民共和国组织机构代码证");
                    unit_cardtypes.append("14");
                    unit_cardtypes.append("组织机构代码证");
                    unit_cardtypes.append("组织机构代码证（集客专用）");
                    unit_cardtypes.append("组织机构代码");
                    unit_cardtypes.append("组织机构");
                    unit_cardtypes.append("205");
                    unit_cardtypes.append("K-组织机构代码证");
                    unit_cardtypes.append("企业机构代码证");
                    unit_cardtypes.append("民办非企业单位登记证书（集客）");
                    unit_cardtypes.append("民办非企业单位登记证书");
                    unit_cardtypes.append("民办非企业单位证书");
                    unit_cardtypes.append("统一社会信用代码证");
                    unit_cardtypes.append("统一社会信息代码证书");
                    unit_cardtypes.append("统一社会信用代码证（集客专用）");
                    unit_cardtypes.append("统一社会信用代码证书");
                    unit_cardtypes.append("统一社会信用代码");
                    unit_cardtypes.append("集团证件-组织机构代码证原件或加盖公章的组织机构代码证复印件");
                    unit_cardtypes.append("单位组织机构代码证");
                    unit_cardtypes.append("IdTypeOrgId");
                    unit_cardtypes.append("OrgaCodeLicence");
//                </cardtype>

//                <cardtype category="营业执照">
                    unit_cardtypes.append("营业执照");
                    unit_cardtypes.append("集团证件―营业执照原件");
                    unit_cardtypes.append("营业执照迁移");
                    unit_cardtypes.append("201");
                    unit_cardtypes.append("营业执照（集客专用）");
                    unit_cardtypes.append("营业执照原件");
                    unit_cardtypes.append("营业执照(组织机构代码)");
                    unit_cardtypes.append("营业执照号码");
                    unit_cardtypes.append("工商营业执照");
                    unit_cardtypes.append("工商执照");
                    unit_cardtypes.append("06");
                    unit_cardtypes.append("E-营业执照");
                    unit_cardtypes.append("集团证件-营业执照原件");
                    unit_cardtypes.append("工商注册号");
                    unit_cardtypes.append("工商登记证");
                    unit_cardtypes.append("工商登记证迁移");
                    unit_cardtypes.append("工商标识码");
                    unit_cardtypes.append("税务证");
                    unit_cardtypes.append("税务登记号");
                    unit_cardtypes.append("税务登记证");
                    unit_cardtypes.append("I");
                    unit_cardtypes.append("ICP经营许可证");
                    unit_cardtypes.append("BussLicence");
                    unit_cardtypes.append("BusinessLicence");
                    unit_cardtypes.append("IdTypeYYZZ");
                    unit_cardtypes.append("BUSINESSLICENCE");
//                </cardtype>

//                <cardtype category="事业单位法人证书或者社会团体法人登记证书">
                    unit_cardtypes.append("事业单位法人证书");
                    unit_cardtypes.append("事业单位法人证书或者社会团体法人登记证书");
                    unit_cardtypes.append("社会团体法人登记证书");
                    unit_cardtypes.append("25");
                    unit_cardtypes.append("社会团体法人登记证书（集客专用）");
                    unit_cardtypes.append("社会团体法人证书");
                    unit_cardtypes.append("社团法人登记证");
                    unit_cardtypes.append("社团登记证");
                    unit_cardtypes.append("社会团体标识");
                    unit_cardtypes.append("社会团体标识迁移");
                    unit_cardtypes.append("31");
                    unit_cardtypes.append("206");
                    unit_cardtypes.append("事业单位法人证书");
                    unit_cardtypes.append("集团证件―事业单位法人证书");
                    unit_cardtypes.append("事业单位法人证书（集客专用）");
                    unit_cardtypes.append("202");
                    unit_cardtypes.append("单位法人证书");
                    unit_cardtypes.append("法人证");
                    unit_cardtypes.append("事业单位编码");
                    unit_cardtypes.append("12");
                    unit_cardtypes.append("单位介绍信");
                    unit_cardtypes.append("加盖公章的介绍信（集客专用）");
                    unit_cardtypes.append("单位介绍信/公函+公章（仅用于党政军客户）");
                    unit_cardtypes.append("单位介绍信(加盖公章)");
                    unit_cardtypes.append("单位证明(含公章)");
                    unit_cardtypes.append("单位证明（含公章）");
                    unit_cardtypes.append("单位证明");
                    unit_cardtypes.append("事业行政单位证明");
                    unit_cardtypes.append("事业行政单位证明迁移");
                    unit_cardtypes.append("204");
                    unit_cardtypes.append("军警单位相关证明");
                    unit_cardtypes.append("介绍信");
                    unit_cardtypes.append("单位介绍信");
                    unit_cardtypes.append("党政军客户介绍信或公函(盖公章)");
                    unit_cardtypes.append("32");
                    unit_cardtypes.append("单位介绍信/公函+公章");
                    unit_cardtypes.append("单位介绍信或单位公函");
                    unit_cardtypes.append("公章");
                    unit_cardtypes.append("90");
                    unit_cardtypes.append("单位公章");
                    unit_cardtypes.append("单位公章证明（单位）");
                    unit_cardtypes.append("21");
                    unit_cardtypes.append("CorpLicence");
                    unit_cardtypes.append("OrgaCodeLicence");
                    unit_cardtypes.append("IdTypeFRZS");
                    unit_cardtypes.append("IdTypeJSX");
                    unit_cardtypes.append("OrgaLicence");
                    unit_cardtypes.append("外交使馆照会");
                    unit_cardtypes.append("照会（集客专用）");
                    unit_cardtypes.append("照会");
//                </cardtype>

//                <cardtype category="法律、行政法规和国家规定的其他有效证件或者证明文件">
//                    unit_cardtypes.append("-");
//                </cardtype>

//                <cardtype category="非法律、行政法规和国家规定的有效身份证件">
                    unit_cardtypes.append("电信识别号");
                    unit_cardtypes.append("客户卡");
                    unit_cardtypes.append("客户标识码");
                    unit_cardtypes.append("集团客户标识码(JTCRMID)");
                    unit_cardtypes.append("其他");
                    unit_cardtypes.append("虚拟证件");
                    unit_cardtypes.append("物联产品");
                    unit_cardtypes.append("代理商易通卡");
                    unit_cardtypes.append("当地办事处登记证");
                    unit_cardtypes.append("集团编号");
                    unit_cardtypes.append("Q-集团编码");
                    unit_cardtypes.append("D-集团客户证件");
                    unit_cardtypes.append("其它证件");
                    unit_cardtypes.append("其他集团证件");
                    unit_cardtypes.append("集团其他证件");
                    unit_cardtypes.append("其它");
                    unit_cardtypes.append("Z-其它");
                    unit_cardtypes.append("GongZhang");
                    unit_cardtypes.append("测试号码证件类型");
                    unit_cardtypes.append("集团编号（集客专用）");
                    unit_cardtypes.append("数固客户编码（集客专用）");
                    unit_cardtypes.append("预开户编号");
                    unit_cardtypes.append("小微企业客户证件");
                         unit_cardtypes.append("小微企业客户");
                    unit_cardtypes.append("小微企业虚拟证件");
                    unit_cardtypes.append("测试号码证件");
                    unit_cardtypes.append("代理商号");
                    unit_cardtypes.append("证件迁移");
                    unit_cardtypes.append("部队番号证件");
//                </cardtype>

//        </unit-cardtypes>

//    </cardtype-config>

//    <?xml version="1.0" encoding="GB2312"?>//rule-common.xml
//    <common-rule>

//        <!--Note 1:以下为“黑卡”规定的个人办理移动电话数的阈值 -->
//        <maxlimit category="重号率阈值">5</maxlimit>

//        <!--Note 2： 对于字段长度，如无规则要求，一律添“-” -->
//        <person category="个人用户规则">
//            <name>
//                <len-min>2</len-min>
//                <len-max>-</len-max>

//                <!--Note 3：允许字符用单引号括起、双竖线分隔 -->
//                <permit-char>'.'||'?'||'・'</permit-char>
//            </name>

//            <!--Note 4：证件类型规则临界点 -->
//            <cardtype>
//                <time-interval>20130901</time-interval>
//            </cardtype>

//            <card-num>
//                <len-min>-</len-min>
//                <len-max>-</len-max>
//            </card-num>

//            <card-add>
//                <len-min>6</len-min>
//                <len-max>-</len-max>
//            </card-add>
//        </person>

//        <unit category="单位/行业用户规则">
//            <name>
//                <len-min>4</len-min>
//                <len-max>-</len-max>
//            </name>

//            <!--Note 5：证件类型规则临界点 -->
//            <cardtype>
//                <time-interval>20130901</time-interval>
//            </cardtype>

//            <card-num>
//                <len-min>-</len-min>
//                <len-max>-</len-max>
//            </card-num>

//            <card-add>
//                <len-min>6</len-min>
//                <len-max>-</len-max>
//            </card-add>

//        </unit>

//    </common-rule>

//    <?xml version="1.0" encoding="GB2312"?>//rule-name-person.xml
//    <person-name-rule> <!-- 姓名规则 -->
//        <rules category="bank">
//            <rule category="common-rule">	<!-- 全字匹配规则 -->
//                <sub>.");
//                <sub>-");

//                <sub>批量受理");
//                <sub>批开卡");

//            </rule>

//            <rule category="match-rule">	<!-- 模糊匹配规则 -->
//                <sub>本人");
//                <sub>工厂");

//            </rule>
//        </rules>
//    </person-name-rule>
//    <?xml version="1.0" encoding="GB2312"?>//rule-name-unit.xml
//    <unit-name-bank>	<!-- 企业名称规则 -->
//        <rules category="bank">
//            <rule category="common-rule"> <!-- 全字匹配规则 -->
//                <sub>.");
//                <sub>-");

//                <sub>过户");
//                <sub>其他");
//                <sub>测试卡");

//            </rule>

//            <rule category="match-rule"> <!-- 模糊匹配规则 -->
//                <sub>本人");
//            </rule>

//        </rules>
//    </unit-name-bank>
}
QString Rule::getRuleName()
{
    return ruleName;
}
//QList<QString> getRules()
//{
//    return rules;
//}
//void setRuleName(QString ruleName)
//{
//    this.ruleName=ruleName;
//}
//void setRules(QList<QString> rules)
//{
//    this.rules=rules;
//}
//void addRule(Rule rule)
//{
//    rules.add(rule);
//}
