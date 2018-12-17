
#include <QFile>


//void StatisticResult::test()
//{
//    SimpleDateFormat df = new SimpleDateFormat("yyyyMMddHHmmss");//设置日期格式
//    String strcurtime = df.format(new Date());// new Date()为获取当前系统时间

//    System.out.println("主线程开始时间：" + strcurtime);

//    //
//    String str_mining_path = "E:\\检查结果\\20150605084035-tjlt4G用户统计结果\\1tonname";//String.format("e:\\检查结果\\%s\\tmp\\%d-%d", this.time_stamp, this.name_index, dir_loop_index);

//    File root_mining_dir = new File(str_mining_path);

//    if (root_mining_dir.exists() && root_mining_dir.isDirectory()) {
//        QFile fs_list[];
//        fs_list = root_mining_dir.listFiles();
//        System.out.println("一个证件号码对应多个姓名证件数：" + fs_list.length);
//        int t_rd = 0;
//        for(int i=0; i<fs_list.length; i++) {
//            if(!fs_list[i].isDirectory()){
//                //System.out.println(fs_list[i].getAbsolutePath());
//                t_rd += TextOper.getFileLineNumber(fs_list[i].getAbsolutePath());
//            }
//        }
//        System.out.println("一个证件号码对应多个姓名记录数：" + t_rd);
//    }

//    String endtime = df.format(new Date());// new Date()为获取当前系统时间
//    System.out.println("主线程结束时间：" + endtime);
//}
