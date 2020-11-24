package util;

import data.*;
import javafx.collections.FXCollections;
import javafx.collections.ObservableList;

import java.sql.*;
import java.text.SimpleDateFormat;
import java.util.ArrayList;

/**
 * DAO(Data Access Object)
 * 对数据库中数据一系列访问的方法类，将程序中需要进行数据库交互操作的方法汇聚到该类中，
 * 使Controller专注于业务逻辑
 */
public class DAO {

    /**
     * DAO实例
     */
    private static DAO instance = null;
    /**
     * 数据库连接对象
     */
    private Connection connection = null;

    /**
     * 构造函数，由getInstance调用，连接数据库
     * @throws Exception 未找到Class
     */
    private DAO() throws Exception {
        try {
            Class.forName(util.Config.DRIVER_CLASSNAME);
            System.out.println("正在连接数据库...");
            connection = DriverManager.getConnection(util.Config.DATABASE_URL, "root", "root");
            if(connection != null) {
                System.out.println("成功连接到数据库");
            }
        } catch (ClassNotFoundException e) {
            e.printStackTrace();
        }
    }

    /**
     * 返回数据库控制器实例
     * @return 数据库控制器实例
     */
    public static DAO getInstance() {
        if(instance == null){
            try {
                instance = new DAO();
            } catch (Exception e) {
                e.printStackTrace();
            }
        }
        return instance;
    }

    /**
     * 获取账号信息，根据账号查询账户信息表，返回查询结果集
     * 由于账号是主码，故结果集最多只有一个元组
     * @param account 账户字符串
     * @return 账户信息的结果集
     */
    public ResultSet getAccountInfo(String account) {
        try {
            Statement statement = connection.createStatement();
            String sql = String.format("select * from tb_account where account = \"%s\"", account);
            return statement.executeQuery(sql);
        } catch (SQLException e) {
            return null;//返回null，到上层Controller处理该异常
        }
    }

    /**
     * 更新账户的最后登录时间，抛出异常由上层处理
     * @param account 账号
     * @param time 时间字符串，格式yyyy-mm-dd hh:mm:ss
     */
    public void updateLoginTime(String account, String time) {
        try {
            Statement statement = connection.createStatement();
            String sql = String.format("update tb_account set last_login_datetime = \"%s\" where account = '%s'", time, account);
            statement.executeUpdate(sql);
        } catch (SQLException e) {
            e.printStackTrace();
        }
    }

    /**
     * 获取账号信息列表，抛出异常由上层处理
     * @return 账号对象的列表
     */
    public ObservableList<AccountInfo> getAccountInfoList() {
        ObservableList<AccountInfo> list = FXCollections.observableArrayList();
        try {
            Statement statement = connection.createStatement();
            String sql = "select * from tb_account";
            ResultSet re = statement.executeQuery(sql);
            while (re.next()) {
                String account = re.getString("account");
                String pwd = re.getString("pwd");
                String uname = re.getString("uname");
                String phone = re.getString("phone");
                Integer idtype = re.getInt("idtype");
                Timestamp last_login_datetime = re.getTimestamp("last_login_datetime");
                String datetime = null;
                if (last_login_datetime != null) {
                    datetime = new SimpleDateFormat("yyyy-MM-dd HH:mm:ss").format(last_login_datetime);
                }
                list.add(new AccountInfo(account, pwd, uname, phone, idtype, datetime));
            }
        } catch (SQLException e) {
            e.printStackTrace();
            return null;//返回null，到上层Controller处理该异常
        }
        return list;
    }

    public boolean insertAccountInfo(AccountInfo accountInfo) {
        if (accountInfo == null) {
            return false;
        }
        try {
            Statement statement = connection.createStatement();
            String sql = String.format("insert into tb_account(account,pwd,uname,phone,idtype,last_login_datetime) VALUES('%s','%s','%s','%s',%d,null)", accountInfo.getAccount(),accountInfo.getPwd(),accountInfo.getName(),accountInfo.getPhone(),accountInfo.getUserType());
            statement.executeUpdate(sql);
            return true;
        } catch (SQLException e) {
            return false;//返回false，到上层Controller处理该异常
        }
    }

    /**
     * 删除账号信息表中指定账号信息，其他的修改由触发器自动完成
     * @param account 要删除的账号
     * @return 成功删除则返回true，否则返回false，由上层处理
     */
    public boolean deleteAccountInfo(String account) {
        try {
            Statement statement = connection.createStatement();
            String sql = String.format("delete from tb_account where account = '%s'",account);
            statement.executeUpdate(sql);
            return true;
        } catch (SQLException e) {
            e.printStackTrace();
            return false;//返回false，到上层Controller处理该异常
        }
    }

    /**
     * 修改账号信息表中指定账户的信息，其他的修改由触发器自动完成
     * @param accountInfo 要修改的账号数据对象
     * @return 修改成功返回true，否则返回false，由上层处理
     */
    public boolean updateAccountInfo(AccountInfo accountInfo) {
        if (accountInfo == null) {
            return false;
        }
        try {
            Statement statement = connection.createStatement();
            String sql = String.format("update tb_account set pwd = '%s',uname = '%s',phone='%s',idtype = '%s'where account = '%s'",accountInfo.getPwd(),accountInfo.getName(),accountInfo.getPhone(),accountInfo.getUserType(),accountInfo.getAccount());
            statement.executeUpdate(sql);
            return true;
        } catch (SQLException e) {
            return false;//返回false，由上层Contoller处理异常
        }
    }

    public ResultSet getMovieInfo(Integer movieid) {
        try {
            Statement statement = connection.createStatement();
            String sql = String.format("select * from tb_movie where movieid = %d",movieid);
            return statement.executeQuery(sql);
        } catch (SQLException e) {
            return null;//返回null，到上层Controller处理该异常
        }
    }

    /**
     * 获取电影信息列表，异常由上层处理
     * @return 电影信息列表
     */
    public ObservableList<MovieInfo> getMovieInfoList() {
        ObservableList<MovieInfo> list = FXCollections.observableArrayList();
        try {
            Statement statement = connection.createStatement();
            String sql = "select * from tb_movie";
            ResultSet re = statement.executeQuery(sql);
            while (re.next()) {
                Integer mid = re.getInt("movieid");
                String mname = re.getString("mname");
                String mtime = re.getTime("mtime").toString();
                boolean screen = re.getBoolean("screen");
                list.add(new MovieInfo(mid, mname, mtime, screen));
            }
        } catch (SQLException e) {
            return null;//返回null，到上层Controller处理该异常
        }
        return list;
    }

    /**
     * 获取电影的数量，用来产生下一个插入的电影ID
     * @return 电影数量
     */
    public Integer getSumOfMovie() {
        try {
            Statement statement = connection.createStatement();
            String sql = "select count(*) as sum_of_movie from tb_movie";
            ResultSet re = statement.executeQuery(sql);
            if (re.next()) {
                return re.getInt("sum_of_movie");
            }
        } catch (SQLException e) {
            e.printStackTrace();
        }
        return -1;//返回false，到上层Controller处理该异常
    }

    /**
     * 向电影表中添加电影信息，成功返回true，失败返回false
     * @param movieInfo 电影信息数据对象
     * @return 成功返回true，失败返回false
     */
    public boolean insertMovieInfo(MovieInfo movieInfo) {
        if (movieInfo == null) {
            return false;
        }
        try {
            Statement statement = connection.createStatement();
            String sql = String.format("insert into tb_movie VALUES(null,'%s',\"%s\",%d)", movieInfo.getMname(),movieInfo.getMtime(),movieInfo.isScreen()?1:0);
            statement.executeUpdate(sql);
            return true;
        } catch (SQLException e) {
            e.printStackTrace();
            return false;//返回false，到上层Controller处理该异常
        }
    }

    /**
     * 删除指定ID的电影，删除成功返回true，失败返回false
     * @param movieid 电影ID
     * @return 删除成功返回true，失败返回false
     */
    public boolean deleteMovieInfo(Integer movieid) {
        try{
            Statement statement = connection.createStatement();
            String sql = String.format("delete from tb_movie where movieid = %d",movieid);
            statement.executeUpdate(sql);
            return true;
        } catch (SQLException e) {
            return false;//返回false，到上层Controller处理该异常
        }
    }

    /**
     * 对指定电影ID进行上映/下架
     * @param  movieid 电影ID
     * @param screen true表示上映，false表示下架
     * @return 成功返回true，失败返回false
     */
    public boolean screenMovie(Integer movieid, boolean screen) {
        try{
            Statement statement = connection.createStatement();
            String sql = String.format("update tb_movie set screen = %d where movieid = %d",screen?1:0, movieid);
            statement.executeUpdate(sql);
            return true;
        } catch (SQLException e) {
            return false;//返回false，到上层Controller处理该异常
        }
    }

    /**
     * 获取指定影厅的信息
     * @param roomid 影厅ID
     * @return 指定影厅的查询结果
     */
    public ResultSet getMovieRoomInfo(Integer roomid) {
        try{
            Statement statement = connection.createStatement();
            String sql = String.format("select * from tb_movie_room where roomid = %d", roomid);
            return statement.executeQuery(sql);
        } catch (SQLException e){
            e.printStackTrace();
            return null;//返回null，到上层Controller处理该异常
        }
    }

    /**
     * 获取影厅信息列表
     * @return 影厅信息列表
     */
    public ObservableList<MovieRoomInfo> getMovieRoomInfoList() {
        ObservableList<MovieRoomInfo> list = FXCollections.observableArrayList();
        try {
            Statement statement = connection.createStatement();
            String sql = "select * from tb_movie_room";
            ResultSet re = statement.executeQuery(sql);
            while (re.next()) {
                Integer roomid = re.getInt("roomid");
                String rname = re.getString("rname");
                Integer row_num = re.getInt("row_num");
                Integer column_num = re.getInt("column_num");
                boolean useflag = re.getBoolean("useflag");
                list.add(new MovieRoomInfo(roomid, rname, row_num, column_num, useflag));
            }
        } catch (SQLException e) {
            return null;//返回null，到上层Controller处理该异常
        }
        return list;
    }

    /**
     * 获取电影的数量，用来产生下一个插入的电影ID
     * @return 电影数量
     */
    public Integer getSumOfMovieRoom() {
        try {
            Statement statement = connection.createStatement();
            String sql = "select count(*) as sum_of_movie_room from tb_movie_room";
            ResultSet re = statement.executeQuery(sql);
            if (re.next()) {
                return re.getInt("sum_of_movie_room");
            }
        } catch (SQLException e) {
            e.printStackTrace();
        }
        return -1;//返回false，到上层Controller处理该异常
    }

    /**
     * 添加影厅信息，添加成功返回true，失败返回false
     * @param movieRoomInfo 影厅信息对象
     * @return 成功返回true，失败返回false
     */
    public boolean insertMovieRoomInfo(MovieRoomInfo movieRoomInfo) {
        if (movieRoomInfo == null) {
            return false;
        }
        try {
            Statement statement = connection.createStatement();
            String sql = String.format("insert into tb_movie_room VALUES(null,'%s',%d,%d,%d)", movieRoomInfo.getRname(),movieRoomInfo.getRow_num(),movieRoomInfo.getColumn_num(),movieRoomInfo.isUseflag()?1:0);
            statement.executeUpdate(sql);
            return true;
        } catch (SQLException e) {
            e.printStackTrace();
            return false;//返回false，到上层Controller处理该异常
        }
    }

    /**
     * 根据useflag更新影厅的使用情况
     * @param roomid 影厅id
     * @param useflag 使用情况，true表示使用，false表示停用
     * @return 修改成功返回true，失败返回false
     */
    public boolean useMovieRoom(Integer roomid, boolean useflag) {
        if (roomid == null) {
            return false;
        }
        try {
            Statement statement = connection.createStatement();
            String sql = String.format("update tb_movie_room set useflag = %d where roomid = %d",useflag?1:0, roomid);
            statement.executeUpdate(sql);
            return true;
        } catch (SQLException e) {
            e.printStackTrace();
            return false;//返回false，由上层Contoller处理异常
        }
    }

    /**
     * 删除指定的影厅信息
     * @param roomid 影厅id
     * @return 删除成功返回true，失败返回false
     */
    public boolean deleteMovieRoomInfo(int roomid) {
        try{
            Statement statement = connection.createStatement();
            String sql = String.format("delete from tb_movie_room where roomid = %d",roomid);
            statement.executeUpdate(sql);
            return true;
        } catch (SQLException e) {
            return false;//返回false，到上层Controller处理该异常
        }
    }

    /**
     * 根据指定日期，获取当日档期表的list，注意档期表中存放的是电影ID
     * 需转查电影表换为电影名称
     * @param date 指定日期字符串
     * @return 指定日期的档期表list，异常返回null
     */
    public ObservableList<ScheduleInfo> getScheduleInfoListByDate(String date) {
        ObservableList<ScheduleInfo> list = FXCollections.observableArrayList();
        try {
            Statement statement = connection.createStatement();
            String sql = String.format("select * from tb_schedule where show_date = '%s'", date);
            ResultSet re = statement.executeQuery(sql);
            while (re.next()) {
                Integer schedule_id = re.getInt("schedule_id");
                ResultSet resultSetOfMovie = getMovieInfo(re.getInt("movie_id"));
                String movie_name = null;
                if (resultSetOfMovie.next()) {
                    movie_name = resultSetOfMovie.getString("mname");
                }
                Integer movie_id = re.getInt("movie_id");
                Integer room_id = re.getInt("room_id");
                String show_time = re.getTime("show_time").toString();
                String end_time =re.getTime("end_time").toString();
                String show_date = re.getDate("show_date").toString();
                Double normal_price = re.getDouble("normal_price");
                list.add(new ScheduleInfo(schedule_id, movie_id, movie_name, room_id, show_time, end_time, show_date, normal_price));
            }
        } catch (SQLException e) {
            e.printStackTrace();
            return null;//返回null，到上层Controller处理该异常
        }
        return list;
    }

    /**
     * 获取影厅ID列表，排挡管理界面中初始化添加档期的影厅选项使用
     * 注意这里是选取的使用中的影厅
     * @return 影厅ID列表
     */
    public ArrayList<Integer> getMovieRoomIDList() {
        ArrayList<Integer> list = new ArrayList<>();
        try {
            Statement statement = connection.createStatement();
            String sql = "select roomid from tb_movie_room where useflag = 1";
            ResultSet re = statement.executeQuery(sql);
            while (re.next()) {
                list.add(re.getInt(1));
            }
        } catch (SQLException e) {
            e.printStackTrace();
            return null;//返回null，到上层controller处理该异常
        }
        return list;
    }

    /**
     * 获取电影名称列表，排挡管理界面中初始化添加档期的电影选项使用
     * 注意这里是选取的上映中的电影
     * @return 电影名称列表
     */
    public ArrayList<String> getMovieNameList() {
        ArrayList<String> list = new ArrayList<>();
        try {
            Statement statement = connection.createStatement();
            String sql = "select mname from tb_movie where screen = 1";
            ResultSet re = statement.executeQuery(sql);
            while (re.next()) {
                list.add(re.getString(1));
            }
        } catch (SQLException e) {
            e.printStackTrace();
            return null;//返回null，到上层controller处理该异常
        }
        return list;
    }

    /**
     * 获取指定电影名称的电影时长
     * @param movieName 电影名称
     * @return 该电影时长的Time对象
     */
    public Time getMovieTime(String movieName) {
        try {
            Statement statement = connection.createStatement();
            String sql = "select mtime from tb_movie where mname = " +"'" + movieName + "'";
            ResultSet re = statement.executeQuery(sql);
            if (re.next()) {
                return re.getTime(1);
            }
        } catch (SQLException e) {
            e.printStackTrace();
            return null;//返回null，到上层controller处理该异常
        }
        return null;
    }

    /**
     * 获取指定日期下指定影厅的时间序列二元组，用于时间冲突检测
     * @param room_id 影厅ID
     * @param show_date 选定的播放日期
     * @return 时间序列二元组
     */
    public ArrayList<Tuple<Integer,Integer>> getTimeTupleFromMovieRoom(int room_id,String show_date) {
        ArrayList<Tuple<Integer,Integer>> timeList = new ArrayList<>();
        try {
            Statement statement =connection.createStatement();
            String sql = String.format("select show_time,end_time from tb_schedule where room_id = %d and show_date = '%s'",room_id,show_date);
            ResultSet re = statement.executeQuery(sql);
            while (re.next()) {
                Integer beginTime = Integer.parseInt(re.getTime(1).toString().substring(0,2)) * 60 + Integer.parseInt(re.getTime(1).toString().substring(3,5));
                Integer endTime = Integer.parseInt(re.getTime(2).toString().substring(0,2)) * 60 + Integer.parseInt(re.getTime(2).toString().substring(3,5));
                timeList.add(new Tuple<>(beginTime,endTime));
            }
        } catch (SQLException e) {
            e.printStackTrace();
            return null;//返回null，到上层controller处理该异常
        }
        return timeList;
    }

    /**
     * 插入档期信息，注意插入的档期一定是不存在时间冲突的合法信息
     * 在Controller中已经通过冲突检测，此处直接插入表即可
     * @param scheduleInfo 档期信息对象
     * @return 插入成功返回true，失败返回false
     */
    public boolean insertScheduleInfo(ScheduleInfo scheduleInfo) {
        if (scheduleInfo == null) {
            return false;
        }
        try {
            Statement statement = connection.createStatement();
            String sql = String.format("insert into tb_schedule VALUES(null,%d,%d,'%s','%s','%s',%3.1f)",scheduleInfo.getMovie_id(),scheduleInfo.getRoom_id(),scheduleInfo.getShow_time(),scheduleInfo.getEnd_time(),scheduleInfo.getShow_date(),scheduleInfo.getNormal_price());
            statement.executeUpdate(sql);
            return true;
        } catch (SQLException e) {
            e.printStackTrace();
            return false;//返回false，到上层Controller处理该异常
        }
    }

    /**
     * 根据电影名称获取电影ID
     * @param mname 电影名称
     * @return 若存在则返回电影ID，若不存在则返回-1
     */
    public Integer getMovieIDByName(String mname) {
        try {
            Statement statement = connection.createStatement();
            String sql = "select movieid from tb_movie where mname = '" + mname + "'";
            ResultSet re = statement.executeQuery(sql);
            if (re.next()) {
                return re.getInt(1);
            }
        } catch (SQLException e) {
            e.printStackTrace();
            return -1;
        }
        return -1;
    }

    /**
     * 根据档期ID获取档期信息
     * @param scheduleID 档期ID
     * @return 成功返回结果集，失败返回null
     */
    public ResultSet getScheduleInfo(int scheduleID) {
        try {
            Statement statement = connection.createStatement();
            String sql = "select * from  tb_schedule where schedule_id = " + scheduleID;
            return statement.executeQuery(sql);
        } catch (SQLException e) {
            e.printStackTrace();
            return null;
        }
    }

    /**
     * 根据档期ID删除档期信息，注意此处档期ID一定存在，
     * Controoler层删除前已经判断过
     * @param scheduleID 档期ID
     * @return 删除成功返回true，失败返回false
     */
    public boolean deleteScheduleInfo(int scheduleID) {
        try {
            Statement statement = connection.createStatement();
            String sql = "delete  from  tb_schedule where schedule_id = " + scheduleID;
            statement.executeUpdate(sql);
            return true;
        } catch (SQLException e) {
            e.printStackTrace();
            return false;
        }
    }

    /**
     * 通过ScheduleList对Schedule表进行更新，
     * 用于复用档期功能
     * @param list scheduleList，里面是相同日期的所有档期
     * @return 更新成功返回true，失败返回false
     */
    public boolean updateScheduleInfoByScheduleInfoList(ObservableList<ScheduleInfo> list) {
        try {
            Statement statement = connection.createStatement();
            String sql = "select schedule_id from tb_schedule where show_date = '" + list.get(0).getShow_date() +"'";
            ResultSet re = statement.executeQuery(sql);
            //先删除当前日期的档期安排
            while (re.next()) {
                if (!deleteScheduleInfo(re.getInt(1))) {//若删除失败则返回false
                    return false;
                }
            }
            for (ScheduleInfo scheduleInfo : list) {//插入每一条档期记录
                sql = String.format("insert into tb_schedule VALUES(null,%d,%d,'%s','%s','%s','%3.1f')",
                                    scheduleInfo.getMovie_id(),
                                    scheduleInfo.getRoom_id(),
                                    scheduleInfo.getShow_time(),
                                    scheduleInfo.getEnd_time(),
                                    scheduleInfo.getShow_date(),
                                    scheduleInfo.getNormal_price());
                statement.executeUpdate(sql);
            }
            return true;
        } catch (SQLException e) {
            e.printStackTrace();
            return false;
        }
    }

    public ArrayList<String> getMovieNameByWatchDate(String date) {
        try {
            ArrayList<String> list = new ArrayList<>();
            Statement statement = connection.createStatement();
            String sql = "select distinct mname from tb_movie,tb_schedule where tb_movie.movieid = tb_schedule.movie_id and tb_schedule.show_date = '" + date +"'";
            ResultSet re = statement.executeQuery(sql);
            while (re.next()) {
                list.add(re.getString(1));
            }
            return list;
        } catch (SQLException e) {
            e.printStackTrace();
            return null;
        }
    }

    public ObservableList<MovieScheduleInfo> getMovieScheduleInfo(int movie_id,String show_date) {
        ObservableList<MovieScheduleInfo> list = FXCollections.observableArrayList();
        try {
            Statement statement = connection.createStatement();
            String sql = "select room_id,show_time,end_time from tb_schedule where movie_id = " + movie_id + " and show_date = '" + show_date +"'";
            ResultSet re = statement.executeQuery(sql);
            while (re.next()) {
                list.add(new MovieScheduleInfo(re.getInt(1),new Tuple<>(re.getString(2),re.getString(3))));
            }
            return list;
        } catch (SQLException e) {
            e.printStackTrace();
            return null;
        }
    }

    public ArrayList<Integer> getMovieRoomIDListBySelectInfo(int movie_id,String show_time,String end_time,String show_date) {
        ArrayList<Integer> list = new ArrayList<>();
        try {
            Statement statement = connection.createStatement();
            String sql = "select distinct room_id from tb_schedule where movie_id = " + movie_id + " and show_time = '" + show_time + "' and end_time = '" + end_time +  "' and show_date = '" + show_date +"'";
            ResultSet re = statement.executeQuery(sql);
            while (re.next()) {
                list.add(re.getInt(1));
            }
            return list;
        } catch (SQLException e){
            e.printStackTrace();
            return null;
        }
    }

    public Tuple<Integer,Integer> getMovieRoomSeatTuple(int room_id) {
        Tuple<Integer,Integer> seatTuple = new Tuple<>(0,0);
        try {
            Statement statement = connection.createStatement();
            String sql = "select row_num,column_num from tb_movie_room where roomid = " + room_id;
            ResultSet re = statement.executeQuery(sql);
            if (re.next()) {
                seatTuple.setP1(re.getInt(1));
                seatTuple.setP2(re.getInt(2));
            }
            return seatTuple;
        } catch (SQLException e) {
            e.printStackTrace();
            return null;
        }
    }

    public int getScheduleIDBySelectInfo(int movie_id,int room_id,String show_time,String end_time,String show_date) {
        try {
            Statement statement = connection.createStatement();
            String sql = "select schedule_id from tb_schedule where movie_id = " + movie_id +
                        " and room_id = " + room_id +
                        " and show_time = '" + show_time + "'" +
                        " and end_time = '" + end_time + "'" +
                        " and show_date = '" + show_date + "'";
            ResultSet re = statement.executeQuery(sql);
            if (re.next()) {
                return re.getInt(1);
            }
            return -1;
        } catch (SQLException e) {
            e.printStackTrace();
            return -1;
        }
    }

    public ObservableList<Tuple<Integer,Integer>> getSoldSeatInfoList(int schedule_id) {
        ObservableList<Tuple<Integer,Integer>> list = FXCollections.observableArrayList();
        try {
            Statement statement = connection.createStatement();
            String sql ="select seat_row,seat_column from tb_ticket where schedule_id = " + schedule_id;
            ResultSet re = statement.executeQuery(sql);
            while (re.next()) {
                list.add(new Tuple<>(re.getInt(1),re.getInt(2)));
            }
            return list;
        } catch (SQLException e) {
            e.printStackTrace();
            return null;
        }
    }

    public double getNormalPrice(int schedule_id) {
        try {
            Statement statement = connection.createStatement();
            String sql ="select normal_price from tb_schedule where schedule_id = " + schedule_id;
            ResultSet re = statement.executeQuery(sql);
            if (re.next()) {
                return  re.getDouble(1);
            }
            return -1;
        } catch (SQLException e) {
            e.printStackTrace();
            return -1;
        }
    }

    public boolean insertTicketInfos(ObservableList<TicketInfo> ticketInfos) {
        if (ticketInfos == null) {
            return false;
        }
        try {
            //关闭自动提交，进行事务处理
            connection.setAutoCommit(false);
            Statement statement = connection.createStatement();
            //插入每一张购票信息，出错则回滚
            for (TicketInfo ticketInfo : ticketInfos) {
                String sql = String.format("insert into tb_ticket values(null,%d,%d,%d,%d,%d,%3.1f)",
                                            ticketInfo.getSchedule_id(),
                                            ticketInfo.getSeat_row(),
                                            ticketInfo.getSeat_column(),
                                            ticketInfo.getTicket_type(),
                                            ticketInfo.isUse_flag()?1:0,
                                            ticketInfo.getAp());
                statement.addBatch(sql);//将本条sql语句加入执行器
            }
            statement.executeBatch();//执行所有sql语句
            connection.commit();//提交事务
            connection.setAutoCommit(true);//开启自动提交
            return true;
        } catch (SQLException e) {//sql语句执行异常捕获
            e.printStackTrace();
            try {
                connection.rollback();//回滚事务
                connection.setAutoCommit(true);//开启自动提交
                return false;
            } catch (SQLException ex) {
                ex.printStackTrace();
                return false;
            }
        }
    }

    public int getTicketID(int schedule_id,int row_num,int column_num) {
        try {
            Statement statement = connection.createStatement();
            String sql = "select tid from tb_ticket where schedule_id = " + schedule_id +
                        " and seat_row = " + row_num +
                        " and seat_column = " + column_num;
            ResultSet re = statement.executeQuery(sql);
            if (re.next()) {
                return re.getInt(1);
            }
            return -1;
        } catch (SQLException e) {
            e.printStackTrace();
            return -1;
        }
    }

    public boolean isTicket(int ticket_id) {
        try {
            Statement statement = connection.createStatement();
            String sql = "select use_flag from tb_ticket where tid = " + ticket_id;
            ResultSet re = statement.executeQuery(sql);
            if (re.next()) {
                return true;
            }
        } catch (SQLException e) {
            e.printStackTrace();
            return false;
        }
        return false;
    }

    public boolean isUsedTicket(int ticket_id) {
        try {
            Statement statement = connection.createStatement();
            String sql = "select use_flag from tb_ticket where tid = " + ticket_id;
            ResultSet re = statement.executeQuery(sql);
            if (re.next()) {
                return re.getBoolean(1);
            }
        } catch (SQLException e) {
            e.printStackTrace();
            return false;
        }
        return false;
    }

    public boolean deleteTicketInfo(int ticket_id) {
        try {
            Statement statement = connection.createStatement();
            String sql = "delete from tb_ticket where tid = " + ticket_id;
            statement.executeUpdate(sql);
            return true;
        } catch (SQLException e) {
            e.printStackTrace();
            return false;
        }
    }
}
