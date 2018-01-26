#include "setup.h"
#include <QTextEdit>
#include <QFile>
#include <QTextStream>
#include <QTextCodec>
#include <QDir>

Setup::Setup(QWidget *parent) : QMainWindow(parent)
{
    setWindowTitle("参数设置");
    QTextEdit *edit=new QTextEdit;
    edit->setText(loadXml("../../../config/config-autoid.xml"));
    setCentralWidget(edit);
    resize(500,150);


}

QString Setup::loadXml(QString filename){
    QTextCodec *code = QTextCodec::codecForName("GBK");//设置文件编码
    QString returnStr;
//    QString filename = "../../../config/config-autoid.xml";
    QTextStream cin(stdin, QIODevice::ReadOnly);
    QTextStream cout(stdout, QIODevice::WriteOnly);
    QTextStream cerr(stderr, QIODevice::WriteOnly);
    cout <<QDir::currentPath()<<endl;
    QFile file(filename);

     if (file.open(QFile::ReadOnly | QFile::Text))
     {
         printf("file is ok.\n");
         QTextStream stream(&file);
         stream.setCodec(code);
         QString line;

//model->removeRows(0, model->rowCount(QModelIndex()), QModelIndex());
         do
         {
             line = stream.readLine();

             returnStr += line;
             returnStr += '\n';
         } while (!line.isEmpty());

       file.close();
     }
     else
     {
         printf("file open failed.\n");
     }
     return returnStr;
}

//<?xml version="1.0" encoding="GB2312"?>//config-autoid.xml
//<autoid-config>
//	<items>
//		<item category="机主">
//			<sub category="姓名">0</sub>
//			<sub category="证件类型">1</sub>
//			<sub category="证件号码">2</sub>
//			<sub category="证件地址">3</sub>
//			<sub category="通讯地址">4</sub>
//			<sub category="装机地址">5</sub>
//		</item>
//		<item category="代（经）办人">
//			<sub category="姓名">6</sub>
//			<sub category="证件类型">7</sub>
//			<sub category="证件号码">8</sub>
//			<sub category="证件地址">9</sub>
//			<sub category="通讯地址">10</sub>
//		</item>
//		<item category="责任人">
//			<sub category="姓名">11</sub>
//			<sub category="证件类型">12</sub>
//			<sub category="证件号码">13</sub>
//			<sub category="证件地址">14</sub>
//			<sub category="通讯地址">15</sub>
//		</item>
//		<item category="单位或行业">
//			<sub category="单位名称">16</sub>
//			<sub category="单位证件号码">17</sub>
//			<sub category="单位证件类型">18</sub>
//			<sub category="单位证件地址">19</sub>
//			<sub category="单位通讯地址">20</sub>
//			<sub category="单位装机地址">21</sub>
//		</item>
//		<item category="电话卡信息">
//			<sub category="MSISDN号码">22</sub>
//			<sub category="登记激活时间">23</sub>
//			<sub category="号码状态">24</sub>
//			<sub category="用户业务类型">25</sub>
//		</item>
//		<item category="营业网点信息">
//			<sub category="网点编号">26</sub>
//			<sub category="网点名称">27</sub>
//			<sub category="网点地址">28</sub>
//			<sub category="网点所在区县">29</sub>
//			<sub category="网点类型">30</sub>
//			<sub category="开通商编号">31</sub>
//		</item>
//		<item category="支付信息">
//			<sub category="交易流水账单号">32</sub>
//			<sub category="交易平台用户账号">33</sub>
//			<sub category="用户交易的银行卡卡号或第三方支付账号名称">34</sub>
//			<sub category="支付时间">35</sub>
//			<sub category="机主证件电子复印件图片名称">36</sub>
//			<sub category="代办人证件电子复印件图片名称">37</sub>
//		</item>
//		<item category="用户类型">
//			<sub category="用户类型">38</sub>
//		</item>
//		<item category="渠道类型">
//			<sub category="渠道类型">39</sub>
//		</item>
//		<item category="使用状态">
//			<sub category="使用状态">40</sub>
//		</item>
//		<item category="预留字段">
//			<sub category="预留字段">41</sub>
//		</item>
//	</items>

//	<!-- 字段间的分隔符，协议规定为双竖线 -->
//	<delimiter category="字段间分隔符">||</delimiter>

//	<!-- 企业数据中的实际字段个数 -->
//	<itemnum category="字段个数">42</itemnum>

//	<!-- y:年 M:月 d:日 H:时 m:分 s:秒 -->
//	<!-- 示例: 1)yyyyMMddHHmmss代表20130901000000 -->
//	<!-- 示例: 2)yyyyMMddHH:mm:ss代表20130901 00:00:00 -->
//	<!-- 示例: 3)yyyy年MM月dd日代表2013年09月01日 -->
//	<!--<dateformat category="时间格式">yyyyMMddHH:mm:ss</dateformat> -->
//	<dateformat category="时间格式">yyyyMMdd</dateformat>

//</autoid-config>


//<?xml version="1.0" encoding="GB2312"?>//config-businesstype.xml
//<businesstype-config>
//	<types>

//		<type category="移动">
//			<sub>-</sub>
//		</type>

//		<!-- 注意：仅把企业数据中“固定”电话的类型枚举全即可，“移动”电话不必枚举 -->
//		<type category="固定">
//			<sub>固话业务</sub>
//			<sub>固话</sub>
//			<sub>PSTN业务</sub>
//			<sub>NGN业务</sub>
//			<sub>SCDMA业务</sub>
//			<sub>普通电话</sub>
//			<sub>固定电话</sub>
//			<sub>FIX</sub>
//		</type>

//	</types>


//	<status category="业务状态">

//		<!-- 注意：仅枚举企业因未实名主动停机的业务状态 -->
//		<no-realname-stop category="非实名停机">
//			<sub>未实名停机</sub>
//			<sub>非实名制停机</sub>
//			<sub>非实名停机</sub>
//			<sub>未实名全停</sub>
//			<sub>实名审核停机</sub>
//				<sub>实名审核停机2</sub>
//					<sub>实名审核停机3</sub>

//			<sub>未实名违章停机</sub>
//			<sub>局方非实名停机</sub>
//			<sub>非实名违章双停</sub>
//		</no-realname-stop>

//		<!-- 注意：枚举不在网用户的业务状态 -->
//		<no-in-net category="不在网">
//			<sub>拆机</sub>
//		</no-in-net>

//	</status>

//	<!-- 实体店现场拍照时间节点，格式为yyyyMMdd -->
//	<photo-date category="现场拍照时间节点">20170101</photo-date>

//</businesstype-config>

//<?xml version="1.0" encoding="GB2312"?>//config-cardtype.xml
//<cardtype-config>

//	<!-- 以下为《工信部25号令》规定的个人办理电话用户真实身份信息登记时需出示有效证件 -->
//	<person-cardtypes category="个人证件">

//			<cardtype category="居民身份证">
//				<sub>01</sub>
//				<sub>0</sub>
//				<sub>身份证</sub>
//				<sub>身份证迁移</sub>
//				<sub>国内身份证</sub>
//				<sub>IDCARD</sub>
//				<sub>身份证-18位</sub>
//				<sub>身份证(18位)</sub>
//				<sub>身份证18位</sub>
//				<sub>身份证15位</sub>
//				<sub>公众证件-居民身份证</sub>
//				<sub>公众证件―居民身份证</sub>
//				<sub>居民身份证</sub>
//				<sub>居民身份证(18位)</sub>
//				<sub>居民身份证(15位)</sub>
//				<sub>身份证</sub>
//				<sub>0-本地身份证</sub>
//				<sub>1-外地身份证</sub>
//				<sub>IdCard</sub>
//				<sub>IdTypeJSX</sub>
//				<sub>101</sub>
//				<sub>1</sub>
//				<sub>2</sub>
//			</cardtype>

//			<cardtype category="临时居民身份证">
//				<sub>临时身份证</sub>
//				<sub>临时居民身份证</sub>
//				<sub>41</sub>
//				<sub>TempId</sub>
//			</cardtype>

//			<cardtype category="户口薄">
//				<sub>户口簿</sub>
//				<sub>户口薄</sub>
//				<sub>公众证件―户口簿</sub>
//				<sub>04</sub>
//				<sub>G-户口簿</sub>
//				<sub>公众证件-户口簿</sub>
//				<sub>户口本</sub>
//				<sub>IdTypeHKB</sub>
//				<sub>HUKOUBU</sub>
//				<sub>户口本（禁止新增）</sub>
//				<sub>户口卡</sub>
//				<sub>户口本迁移</sub>
//				<sub>户口本/居住证</sub>
//			</cardtype>

//			<cardtype category="中国人民解放军军人身份证件">
//				<sub>军官证</sub>
//				<sub>02</sub>
//				<sub>士官证</sub>
//				<sub>士官证迁移</sub>
//				<sub>军官证（禁止新增）</sub>
//				<sub>军官证迁移</sub>
//				<sub>C-军官证</sub>
//				<sub>军官（士兵）证</sub>
//				<sub>军人身份证件</sub>
//				<sub>军人身份证</sub>
//				<sub>公众证件-军人身份证</sub>
//				<sub>103</sub>
//				<sub>军人证</sub>
//				<sub>海军证</sub>
//				<sub>海军证迁移</sub>
//				<sub>空军证</sub>
//				<sub>空军证迁移</sub>
//				<sub>士官证</sub>
//				<sub>士兵证</sub>
//				<sub>SoldierID</sub>
//				<sub>PLA</sub>
//			</cardtype>

//			<cardtype category="中国人民武装警察身份证件">
//				<sub>警官证</sub>
//				<sub>警官证迁移</sub>
//				<sub>09</sub>
//				<sub>104</sub>
//				<sub>警官证（禁止新增）</sub>
//				<sub>H-警官证</sub>
//				<sub>武装警察身份证件</sub>
//				<sub>武装警察身份证</sub>
//				<sub>公众证件―武装警察身份证</sub>
//				<sub>武警身份证</sub>
//				<sub>人民警察证</sub>
//				<sub>PolicePaper</sub>
//			</cardtype>

//			<cardtype category="港澳居民来往内地通行证">
//				<sub>港澳证</sub>
//				<sub>港澳身份证</sub>
//				<sub>澳门身份证</sub>
//				<sub>香港身份证</sub>
//				<sub>港澳居民内地通行证</sub>
//				<sub>17</sub>
//				<sub>港澳居民来往内地通行证</sub>
//				<sub>港澳来往内地通行证</sub>
//				<sub>港澳居民往来内地通行</sub>
//				<sub>港澳台通行证</sub>
//				<sub>公众证件―港澳居民往来内地通行</sub>
//				<sub>107</sub>
//				<sub>内地通行证（港澳）</sub>
//				<sub>港澳居民往来内地通行证</sub>
//			</cardtype>

//			<cardtype category="台湾居民来往大陆通行证">
//				<sub>台胞证</sub>
//				<sub>台胞身份证</sub>
//				<sub>台湾身份证</sub>
//				<sub>台湾居民内地通行证</sub>
//				<sub>台湾居民来往内地通行证</sub>
//				<sub>台湾居民来往大陆通行证</sub>
//				<sub>公众证件―台湾居民往来大陆通行证</sub>
//				<sub>台湾来往大陆通行证</sub>
//				<sub>台湾居民往来大陆通行证</sub>
//				<sub>42</sub>
//				<sub>108</sub>
//				<sub>大陆通行证（台湾）</sub>
//			</cardtype>

//			<cardtype category="外国公民护照">
//				<sub>105</sub>
//				<sub>护照</sub>
//				<sub>公众证件―护照</sub>
//				<sub>护照迁移</sub>
//				<sub>03</sub>
//				<sub>公众证件-护照</sub>
//				<sub>外国公民护照</sub>
//				<sub>A-护照</sub>
//				<sub>PASSPORT</sub>
//			</cardtype>

//			<cardtype category="法律、行政法规和国家规定的其他有效身份证件">
//				<sub>-</sub>
//				<sub>外交使馆照会</sub>
//				<sub>部队番号证件</sub>
//				<sub>照会</sub>
//			</cardtype>

//			<cardtype category="非法律、行政法规和国家规定的有效身份证件">
//				<sub>驾驶证</sub>
//				<sub>驾驶证迁移</sub>
//				<sub>驾驶执照</sub>
//				<sub>07</sub>
//				<sub>驾驶证（禁止新增）</sub>
//				<sub>教师证</sub>
//				<sub>学生证</sub>
//				<sub>学生证迁移</sub>
//				<sub>05</sub>
//				<sub>学生证（集客专用）</sub>
//				<sub>B-学生证</sub>
//				<sub>社保卡</sub>
//				<sub>客户卡</sub>
//				<sub>客户标识码</sub>
//				<sub>老年证</sub>
//				<sub>老人证</sub>
//				<sub>其他</sub>
//				<sub>其他证件迁移</sub>
//				<sub>其它</sub>
//				<sub>Z-其它</sub>
//				<sub>其它证件</sub>
//				<sub>部队干部离休证</sub>
//				<sub>户口本/居住证</sub>
//				<sub>士兵证迁移</sub>
//				<sub>工作证</sub>
//				<sub>工作证迁移</sub>
//				<sub>E</sub>
//				<sub>18</sub>
//				<sub>暂住证</sub>
//				<sub>11</sub>
//				<sub>回乡证</sub>
//				<sub>10</sub>
//				<sub>残疾证</sub>
//				<sub>08</sub>
//				<sub>市政府人才居住证</sub>
//				<sub>13</sub>
//				<sub>房产证</sub>
//				<sub>房产证迁移</sub>
//				<sub>15</sub>
//				<sub>记者证</sub>
//				<sub>19</sub>
//				<sub>医疗证</sub>
//				<sub>居留证</sub>
//				<sub>22</sub>
//				<sub>虚拟证件</sub>
//				<sub>文职官员证</sub>
//				<sub>文职证</sub>
//				<sub>23</sub>
//				<sub>军警单位相关证明</sub>
//				<sub>当地办事处登记证</sub>
//				<sub>预开户编号</sub>
//				<sub>测试号码证件</sub>
//				<sub>测试证</sub>
//				<sub>99</sub>
//				<sub>数固客户编码</sub>
//				<sub>华侨证明（区县级）</sub>
//				<sub>实名制待核实</sub>
//				<sub>F-代扣号</sub>
//				<sub>测试号码证件类型</sub>
//				<sub>干部证</sub>
//				<sub>干部证迁移</sub>
//				<sub>社会保险号（禁止新增）</sub>
//				<sub>其他（禁止新增）</sub>
//				<sub>199</sub>
//				<sub>20</sub>
//				<sub>PPC用户卡号</sub>
//				<sub>PPC用户卡号迁移</sub>
//				<sub>代理商号</sub>
//				<sub>银行帐户</sub>
//				<sub>证件迁移</sub>
//				<sub>银行帐户（禁止新增）</sub>
//			</cardtype>

//	</person-cardtypes>


//	<!-- 以下为《工信部25号令》规定的单位办理电话用户真实身份信息登记时需出示有效证件 -->
//	<unit-cardtypes category="单位证件">

//			<cardtype category="组织机构代码证">
//				<sub>企业组织机构代码证</sub>
//				<sub>集团证件―组织机构代码证原件或加盖公章的组织机构代码证复印件</sub>
//				<sub>企业组织机构代码</sub>
//				<sub>中华人民共和国组织机构代码证</sub>
//				<sub>14</sub>
//				<sub>组织机构代码证</sub>
//				<sub>组织机构代码证（集客专用）</sub>
//				<sub>组织机构代码</sub>
//				<sub>组织机构</sub>
//				<sub>205</sub>
//				<sub>K-组织机构代码证</sub>
//				<sub>企业机构代码证</sub>
//				<sub>民办非企业单位登记证书（集客）</sub>
//				<sub>民办非企业单位登记证书</sub>
//				<sub>民办非企业单位证书</sub>
//				<sub>统一社会信用代码证</sub>
//				<sub>统一社会信息代码证书</sub>
//				<sub>统一社会信用代码证（集客专用）</sub>
//				<sub>统一社会信用代码证书</sub>
//				<sub>统一社会信用代码</sub>
//				<sub>集团证件-组织机构代码证原件或加盖公章的组织机构代码证复印件</sub>
//				<sub>单位组织机构代码证</sub>
//				<sub>IdTypeOrgId</sub>
//				<sub>OrgaCodeLicence</sub>
//			</cardtype>

//			<cardtype category="营业执照">
//				<sub>营业执照</sub>
//				<sub>集团证件―营业执照原件</sub>
//				<sub>营业执照迁移</sub>
//				<sub>201</sub>
//				<sub>营业执照（集客专用）</sub>
//				<sub>营业执照原件</sub>
//				<sub>营业执照(组织机构代码)</sub>
//				<sub>营业执照号码</sub>
//				<sub>工商营业执照</sub>
//				<sub>工商执照</sub>
//				<sub>06</sub>
//				<sub>E-营业执照</sub>
//				<sub>集团证件-营业执照原件</sub>
//				<sub>工商注册号</sub>
//				<sub>工商登记证</sub>
//				<sub>工商登记证迁移</sub>
//				<sub>工商标识码</sub>
//				<sub>税务证</sub>
//				<sub>税务登记号</sub>
//				<sub>税务登记证</sub>
//				<sub>I</sub>
//				<sub>ICP经营许可证</sub>
//				<sub>BussLicence</sub>
//				<sub>BusinessLicence</sub>
//				<sub>IdTypeYYZZ</sub>
//				<sub>BUSINESSLICENCE</sub>
//			</cardtype>

//			<cardtype category="事业单位法人证书或者社会团体法人登记证书">
//				<sub>事业单位法人证书</sub>
//				<sub>事业单位法人证书或者社会团体法人登记证书</sub>
//				<sub>社会团体法人登记证书</sub>
//				<sub>25</sub>
//				<sub>社会团体法人登记证书（集客专用）</sub>
//				<sub>社会团体法人证书</sub>
//				<sub>社团法人登记证</sub>
//				<sub>社团登记证</sub>
//				<sub>社会团体标识</sub>
//				<sub>社会团体标识迁移</sub>
//				<sub>31</sub>
//				<sub>206</sub>
//				<sub>事业单位法人证书</sub>
//				<sub>集团证件―事业单位法人证书</sub>
//				<sub>事业单位法人证书（集客专用）</sub>
//				<sub>202</sub>
//				<sub>单位法人证书</sub>
//				<sub>法人证</sub>
//				<sub>事业单位编码</sub>
//				<sub>12</sub>
//				<sub>单位介绍信</sub>
//				<sub>加盖公章的介绍信（集客专用）</sub>
//				<sub>单位介绍信/公函+公章（仅用于党政军客户）</sub>
//				<sub>单位介绍信(加盖公章)</sub>
//				<sub>单位证明(含公章)</sub>
//				<sub>单位证明（含公章）</sub>
//				<sub>单位证明</sub>
//				<sub>事业行政单位证明</sub>
//				<sub>事业行政单位证明迁移</sub>
//				<sub>204</sub>
//				<sub>军警单位相关证明</sub>
//				<sub>介绍信</sub>
//				<sub>单位介绍信</sub>
//				<sub>党政军客户介绍信或公函(盖公章)</sub>
//				<sub>32</sub>
//				<sub>单位介绍信/公函+公章</sub>
//				<sub>单位介绍信或单位公函</sub>
//				<sub>公章</sub>
//				<sub>90</sub>
//				<sub>单位公章</sub>
//				<sub>单位公章证明（单位）</sub>
//				<sub>21</sub>
//				<sub>CorpLicence</sub>
//				<sub>OrgaCodeLicence</sub>
//				<sub>IdTypeFRZS</sub>
//				<sub>IdTypeJSX</sub>
//				<sub>OrgaLicence</sub>
//				<sub>外交使馆照会</sub>
//				<sub>照会（集客专用）</sub>
//				<sub>照会</sub>
//			</cardtype>

//			<cardtype category="法律、行政法规和国家规定的其他有效证件或者证明文件">
//				<sub>-</sub>
//			</cardtype>

//			<cardtype category="非法律、行政法规和国家规定的有效身份证件">
//				<sub>电信识别号</sub>
//				<sub>客户卡</sub>
//				<sub>客户标识码</sub>
//				<sub>集团客户标识码(JTCRMID)</sub>
//				<sub>其他</sub>
//				<sub>虚拟证件</sub>
//				<sub>物联产品</sub>
//				<sub>代理商易通卡</sub>
//				<sub>当地办事处登记证</sub>
//				<sub>集团编号</sub>
//				<sub>Q-集团编码</sub>
//				<sub>D-集团客户证件</sub>
//				<sub>其它证件</sub>
//				<sub>其他集团证件</sub>
//				<sub>集团其他证件</sub>
//				<sub>其它</sub>
//				<sub>Z-其它</sub>
//				<sub>GongZhang</sub>
//				<sub>测试号码证件类型</sub>
//				<sub>集团编号（集客专用）</sub>
//				<sub>数固客户编码（集客专用）</sub>
//				<sub>预开户编号</sub>
//				<sub>小微企业客户证件</sub>
//		             <sub>小微企业客户</sub>
//				<sub>小微企业虚拟证件</sub>
//				<sub>测试号码证件</sub>
//				<sub>代理商号</sub>
//				<sub>证件迁移</sub>
//				<sub>部队番号证件</sub>
//			</cardtype>

//	</unit-cardtypes>

//</cardtype-config>

//<?xml version="1.0" encoding="GB2312"?>//config-system.xml

//<system-config>	<!-- 工具基本配置 -->

//		<!-- Note：检查数据范围，0表示合规性检查指定的日期指定的范围检查，1表示全量数据范围检查 -->
//		<!-- Note：本次检查，虚商采用0，基础企业采用1 -->
//		<data-range category="数据范围">0</data-range>

//		<!-- Note：合规性检查指定的日期，格式为YYYYMMDD -->
//		<!-- Note：一证五号检查仍基于全量数据 -->
//		<compliant-date category="合规性检查日期">20170101</compliant-date>

//		<!-- Note：全国一证五号时间节点，用于抽取1%的证件号码(基础企业) -->
//		<onecard2five-date category="一证五号时间节点">20170401</onecard2five-date>

//		<!-- Note：2107年1月1日以后的随机一天，格式为YYYYMMDD，抽取该天的全量数据用于核验 -->
//		<random-date  category="随机日期">20170609</random-date>

//</system-config>

//<?xml version="1.0" encoding="GB2312"?>//config-usertype.xml
//<usertype-config>

//	<!-- 个人用户 -->
//	<person category="个人用户">个人用户</person>

//	<!-- 单位用户 -->
//	<unit category="单位用户">单位用户</unit>

//	<!-- 行业应用 -->
//	<industry category="行业用户">行业用户</industry>

//</usertype-config>

//<?xml version="1.0" encoding="GB2312"?>//config-workingpath
//<workingpath-config>	<!-- 工作路径（绝对路径） -->

//	<!-- Note 1：确保路径正确，否则影响系统加载配置和规则 -->
//	<workingpath category="工作路径">e:\新口径</workingpath>

//</workingpath-config>
