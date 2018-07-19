#ifndef STATISTICRESULT_H
#define STATISTICRESULT_H


class StatisticResult
{
public:
    StatisticResult();
    // ----基本
    int sr_total_rc = 0; 	// 记录总数
    int sr_abnor_rc = 0;	// 异常记录
    int sr_abnor_m_rc = 0;	// 异常记录(用户类型、业务类型)
    int sr_norealname_rc = 0;	// 非实名停机用户数据
    int sr_noinet_rc = 0;	// 非实名停机用户数据

    int sr_all_nreg_rc = 0;	// 全量未登记记录数
    int sr_all_nck_rc = 0;	// 全量校验失败记录数
    int sr_all_ok_rc = 0;

    //20170612工信部检查，抽取个人移动用户1%的、
    int sr_p_m_one_percent_rc = 0;

    int sr_p_m_total_rc = 0;	// 个人移动记录总数
    int sr_p_f_total_rc = 0;	// 个人固定记录总数
    int sr_u_m_total_rc = 0;	// 单位移动记录总数
    int sr_u_f_total_rc = 0;	// 单位固话记录总数
    int sr_i_m_total_rc = 0;	// 行业移动记录总数
    int sr_i_f_total_rc = 0;	// 行业固定记录总数

    int sr_p_m_ok_rc = 0;	// 个人移动合规记录数
    int sr_p_f_ok_rc = 0;	// 个人固定合规记录数
    int sr_u_m_ok_rc = 0;	// 单位固定合规记录数
    int sr_u_f_ok_rc = 0;	// 单位固定合规记录数
    int sr_i_m_ok_rc = 0;	// 单位固定合规记录数
    int sr_i_f_ok_rc = 0;	// 单位固定合规记录数

    int sr_p_m_nreg_rc = 0;
    int sr_p_m_1000_rc = 0;	// 个人移动用户姓名未登记记录数
    int sr_p_m_100_rc = 0;	// 个人移动用户姓名未登记记录数
    int sr_p_m_010_rc = 0;	// 个人移动用户证件号码未登记记录数
    int sr_p_m_001_rc = 0;	// 个人移动用户证件地址未登记记录数
    int sr_p_m_110_rc = 0;	// 个人移动用户姓名、证件号码未登记记录数
    int sr_p_m_101_rc = 0;	// 个人移动用户姓名、证件地址未登记记录数
    int sr_p_m_011_rc = 0;	// 个人移动用户证件号码、证件地址未登记记录数
    int sr_p_m_111_rc = 0;	// 个人移动用户姓名、证件号码、证件地址未登记记录数

    int sr_p_f_nreg_rc = 0;
    int sr_p_f_1000_rc = 0;	// 个人固定用户姓名未登记记录数
    int sr_p_f_100_rc = 0;	// 个人固定用户姓名未登记记录数
    int sr_p_f_010_rc = 0;	// 个人固定用户证件号码未登记记录数
    int sr_p_f_001_rc = 0;	// 个人固定用户证件地址未登记记录数
    int sr_p_f_110_rc = 0;	// 个人固定用户姓名、证件号码未登记记录数
    int sr_p_f_101_rc = 0;	// 个人固定用户姓名、证件地址未登记记录数
    int sr_p_f_011_rc = 0;	// 个人固定用户证件号码、证件地址未登记记录数
    int sr_p_f_111_rc = 0;	// 个人固定用户姓名、证件号码、证件地址未登记记录数

    int sr_p_m_nck_rc = 0;
    int sr_p_m_2000_rc = 0;	// 个人移动用户姓名校验失败记录数
    int sr_p_m_200_rc = 0;	// 个人移动用户姓名校验失败记录数
    int sr_p_m_020_rc = 0;	// 个人移动用户证件号码校验失败记录数
    int sr_p_m_002_rc = 0;	// 个人移动用户证件地址校验失败记录数
    int sr_p_m_220_rc = 0;	// 个人移动用户姓名、证件号码校验失败记录数
    int sr_p_m_202_rc = 0;	// 个人移动用户姓名、证件地址校验失败记录数
    int sr_p_m_022_rc = 0;	// 个人移动证件号码、证件地址校验失败记录数
    int sr_p_m_222_rc = 0;	// 个人移动用户姓名、证件号码、证件地址校验失败记录数
    int sr_p_m_200_1_rc = 0;	// 个人移动用户姓名校验失败记录数
    int sr_p_m_200_2_rc = 0;	// 个人移动用户姓名校验失败记录数
    int sr_p_m_200_3_rc = 0;	// 个人移动用户姓名校验失败记录数
    int sr_p_m_200_4_rc = 0;	// 个人移动用户姓名校验失败记录数

    int sr_p_f_nck_rc = 0;
    int sr_p_f_2000_rc = 0;	// 个人固定用户姓名校验失败记录数
    int sr_p_f_200_rc = 0;	// 个人固定用户姓名校验失败记录数
    int sr_p_f_020_rc = 0;	// 个人固定用户证件号码校验失败记录数
    int sr_p_f_002_rc = 0;	// 个人固定用户证件地址校验失败记录数
    int sr_p_f_220_rc = 0;	// 个人固定用户姓名、证件号码校验失败记录数
    int sr_p_f_202_rc = 0;	// 个人固定用户姓名、证件地址校验失败记录数
    int sr_p_f_022_rc = 0;	// 个人固定证件号码、证件地址校验失败记录数
    int sr_p_f_222_rc = 0;	// 个人固定用户姓名、证件号码、证件地址校验失败记录数
    int sr_p_f_200_1_rc = 0;	// 个人固定用户姓名校验失败记录数
    int sr_p_f_200_2_rc = 0;	// 个人固定用户姓名校验失败记录数
    int sr_p_f_200_3_rc = 0;	// 个人固定用户姓名校验失败记录数
    int sr_p_f_200_4_rc = 0;	// 个人固定用户姓名校验失败记录数

    int sr_u_m_nreg_rc = 0;
    int sr_u_m_100_rc = 0;	// 单位移动用户姓名未登记记录数
    int sr_u_m_010_rc = 0;	// 单位移动用户证件号码未登记记录数
    int sr_u_m_001_rc = 0;	// 单位移动用户证件地址未登记记录数
    int sr_u_m_110_rc = 0;	// 单位移动用户姓名、证件号码未登记记录数
    int sr_u_m_101_rc = 0;	// 单位移动用户姓名、证件地址未登记记录数
    int sr_u_m_011_rc = 0;	// 单位移动用户证件号码、证件地址未登记记录数
    int sr_u_m_111_rc = 0;	// 单位移动用户姓名、证件号码、证件地址未登记记录数

    int sr_i_m_nreg_rc = 0;
    int sr_i_m_010_rc = 0;	// 行业移动用户经办人未登记记录数
    int sr_i_m_001_rc = 0;	// 行业移动用户责任单位未登记记录数
    int sr_i_m_011_rc = 0;	// 行业移动用户经办人、责任单位未登记记录数
    int sr_i_m_100_rc = 0;
    int sr_i_m_110_rc = 0;
    int sr_i_m_10i_rc = 0;
    int sr_i_m_11i_rc = 0;
    int sr_i_m_01i_rc = 0;
    int sr_i_m_00i_rc = 0;

    int sr_i_m_nck_rc = 0;
    int sr_i_m_020_rc = 0;	// 行业移动用户经办人未登记记录数
    int sr_i_m_002_rc = 0;	// 行业移动用户责任单位未登记记录数
    int sr_i_m_022_rc = 0;	// 行业移动用户经办人、责任单位未登记记录数
    int sr_i_m_200_rc = 0;
    int sr_i_m_220_rc = 0;
    int sr_i_m_20j_rc = 0;
    int sr_i_m_22j_rc = 0;
    int sr_i_m_02j_rc = 0;
    int sr_i_m_00j_rc = 0;

    int sr_i_f_nreg_rc = 0;
    int sr_i_f_010_rc = 0;	// 行业固定用户经办人未登记记录数
    int sr_i_f_001_rc = 0;	// 行业固定用户责任单位未登记记录数
    int sr_i_f_011_rc = 0;	// 行业固定用户经办人、责任单位未登记记录数
    int sr_i_f_01i_rc = 0;
    int sr_i_f_00i_rc = 0;

    int sr_i_f_nck_rc = 0;
    int sr_i_f_020_rc = 0;	// 行业固定用户经办人未登记记录数
    int sr_i_f_002_rc = 0;	// 行业固定用户责任单位未登记记录数
    int sr_i_f_022_rc = 0;	// 行业固定用户经办人、责任单位未登记记录数
    int sr_i_f_02j_rc = 0;
    int sr_i_f_00j_rc = 0;


    int sr_u_f_nreg_rc = 0;
    int sr_u_f_100_rc = 0;	// 单位固定用户姓名未登记记录数
    int sr_u_f_010_rc = 0;	// 单位固定用户证件号码未登记记录数
    int sr_u_f_001_rc = 0;	// 单位固定用户证件地址未登记记录数
    int sr_u_f_110_rc = 0;	// 单位固定用户姓名、证件号码未登记记录数
    int sr_u_f_101_rc = 0;	// 单位固定用户姓名、证件地址未登记记录数
    int sr_u_f_011_rc = 0;	// 单位固定用户证件号码、证件地址未登记记录数
    int sr_u_f_111_rc = 0;	// 单位固定用户姓名、证件号码、证件地址未登记记录数

    int sr_u_m_nck_rc = 0;
    int sr_u_m_200_rc = 0;	// 单位移动用户姓名校验失败记录数
    int sr_u_m_020_rc = 0;	// 单位移动用户证件号码校验失败记录数
    int sr_u_m_002_rc = 0;	// 单位移动用户证件地址校验失败记录数
    int sr_u_m_220_rc = 0;	// 单位移动用户姓名、证件号码校验失败记录数
    int sr_u_m_202_rc = 0;	// 单位移动用户姓名、证件地址校验失败记录数
    int sr_u_m_022_rc = 0;	// 单位移动用户证件号码、证件地址校验失败记录数
    int sr_u_m_222_rc = 0;	// 单位移动用户姓名、证件号码、证件地址校验失败记录数
    int sr_u_m_200_1_rc = 0;	// 单位移动用户姓名校验失败记录数
    int sr_u_m_200_2_rc = 0;	// 单位移动用户姓名校验失败记录数
    int sr_u_m_200_3_rc = 0;	// 单位移动用户姓名校验失败记录数
    int sr_u_m_200_4_rc = 0;	// 单位移动用户姓名校验失败记录数


    int sr_u_f_nck_rc = 0;
    int sr_u_f_200_rc = 0;	// 单位固定用户姓名校验失败记录数
    int sr_u_f_020_rc = 0;	// 单位固定证件号码校验失败记录数
    int sr_u_f_002_rc = 0;	// 单位固定证件地址校验失败记录数
    int sr_u_f_220_rc = 0;	// 单位固定用户姓名、证件号码校验失败记录数
    int sr_u_f_202_rc = 0;	// 单位固定用户姓名、证件地址校验失败记录数
    int sr_u_f_022_rc = 0;	// 单位固定用户证件号码、证件地址校验失败记录数
    int sr_u_f_222_rc = 0;	// 单位固定用户姓名、证件号码、证件地址校验失败记录数
    int sr_u_f_200_1_rc = 0;	// 单位固定用户姓名校验失败记录数
    int sr_u_f_200_2_rc = 0;	// 单位固定用户姓名校验失败记录数
    int sr_u_f_200_3_rc = 0;	// 单位固定用户姓名校验失败记录数
    int sr_u_f_200_4_rc = 0;	// 单位固定用户姓名校验失败记录数

    int sr_p_m_a_total_rc = 0;
    int sr_p_f_a_total_rc = 0;
    int sr_p_m_a_1_rc = 0;	// 个人代办未登记
    int sr_p_f_a_1_rc = 0;	// 个人代办未登记
    int sr_p_m_a_2_rc = 0;	// 个人代办校验失败
    int sr_p_f_a_2_rc = 0;	// 个人代办校验失败

    int sr_1tonname_rc = 0;
    int sr_p_m_1tonname_rc = 0;
    int sr_p_f_1tonname_rc = 0;
    int sr_u_m_1tonname_rc = 0;
    int sr_u_f_1tonname_rc = 0;

    int sr_beyond5_rc = 0;
    int sr_p_m_beyond5_rc = 0;
    int sr_p_f_beyond5_rc = 0;
    int sr_u_m_beyond5_rc = 0;
    int sr_u_f_beyond5_rc = 0;


    int sr_u_m_owner_agent_eq_rc = 0;
    int sr_u_m_owner_sa_rc = 0;

    int sr_army_total_rc = 0;
    int sr_army_130901_rc = 0;

    int sr_police_total_rc = 0;
    int sr_police_130901_rc = 0;

    int sr_id_overdue_rc = 0;

};

#endif // STATISTICRESULT_H
