package util;

import java.net.PortUnreachableException;

/**
 * 项目配置信息类，所有静态成员均为全局配置信息
 * 修改时在此处修改即可
 */
public class Config {
    /**
     * 数据库实例url
     */
    public static final String DATABASE_URL = "jdbc:mysql://localhost:3306/L714707";
    /**
     * mysql数据库驱动完全限定类名，版本为mysql-8.0.20
     */
    public static final String DRIVER_CLASSNAME = "com.mysql.cj.jdbc.Driver";
    /**
     * 电影院每个影厅的清洁退场时间定义，用于时间冲突检测
     */
    public static final int CLEAR_TIME = 5;
    /**
     * 影厅最大行数
     */
    public static final int MAX_ROW_NUM = 12;
    /**
     * 影厅最大列数
     */
    public static final int MAX_COLUMN_NUM = 14;
    /**
     * 坐席预览图的布局配置信息，用于渲染座位图表
     */
    public static final int PREF_WIDTH = 1000;
    /**
     * 坐席预览图的不急配置信息，用于渲染座位图表
     */
    public static final int PREF_WEIGHT = 450;
}
