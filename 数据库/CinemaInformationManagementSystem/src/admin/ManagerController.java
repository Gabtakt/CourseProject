package admin;

import data.MovieInfo;
import data.MovieRoomInfo;
import data.ScheduleInfo;
import data.Tuple;
import javafx.collections.FXCollections;
import javafx.collections.ObservableList;
import javafx.fxml.FXML;
import javafx.scene.control.*;
import javafx.scene.control.cell.PropertyValueFactory;
import util.DAO;
import util.Util;

import javax.swing.*;

import java.sql.ResultSet;
import java.sql.SQLException;
import java.sql.Time;
import java.text.ParseException;
import java.text.SimpleDateFormat;
import java.util.ArrayList;
import java.util.Date;
import java.util.Optional;

import static javax.swing.JOptionPane.showMessageDialog;

public class ManagerController {
    //电影表组件绑定
    @FXML
    private TableView<MovieInfo> MOVIE_VIEW;
    @FXML
    private TableColumn<MovieInfo,Integer> MOVIE_ID;
    @FXML
    private TableColumn<MovieInfo,String> MOVIE_NAME;
    @FXML
    private TableColumn<MovieInfo,String> MOVIE_TIME;
    @FXML
    private TableColumn<MovieInfo,String> SCREEN;

    //影厅表组件绑定
    @FXML
    private TableView<MovieRoomInfo> MOVIEROOM_VIEW;
    @FXML
    private TableColumn<MovieRoomInfo,Integer> YTID;
    @FXML
    private TableColumn<MovieRoomInfo,String> YTMC;
    @FXML
    private TableColumn<MovieRoomInfo,Integer> ZXHS;
    @FXML
    private TableColumn<MovieRoomInfo,Integer> ZXLS;
    @FXML
    private TableColumn<MovieInfo,String> SFSY;

    //档期表组件绑定
    @FXML
    private TableView<ScheduleInfo> SCHEDULE_VIEW;
    @FXML
    private TableColumn<ScheduleInfo,Integer> S_DQID;
    @FXML
    private TableColumn<ScheduleInfo,Integer> S_YTID;
    @FXML
    private TableColumn<ScheduleInfo,String> S_DYMC;
    @FXML
    private TableColumn<ScheduleInfo,String> S_KSSJ;
    @FXML
    private TableColumn<ScheduleInfo,String> S_JSSJ;
    @FXML
    private TableColumn<ScheduleInfo,String> S_BFRQ;
    @FXML
    private TableColumn<ScheduleInfo,Double> S_EDPJ;
    @FXML
    private DatePicker SCHEDULE_DATE;
    @FXML
    private ChoiceBox<Integer> ADD_YTID;
    @FXML
    private ChoiceBox<String> ADD_DYMC;
    @FXML
    private ChoiceBox<Integer> ADD_HOUR;
    @FXML
    private ChoiceBox<Integer> ADD_MIN;
    @FXML
    private TextField ADD_EDPJ;
    @FXML
    private TextField DEL_DQID;
    @FXML
    private DatePicker FYRQ;

    private ObservableList<MovieInfo> movieInfos = FXCollections.observableArrayList();
    private ObservableList<MovieRoomInfo> movieRoomInfos = FXCollections.observableArrayList();
    private ObservableList<ScheduleInfo> scheduleInfos = FXCollections.observableArrayList();

    private String targetDate = null;
    private String sourseDate;

    public static String account = null;

    private static ManagerController instance = null;

    public static ManagerController getInstance() {
        return instance;
    }

    @FXML
    private void initialize() {
        //初始化实例
        instance = this;
        //显示账号信息
        showMovieList();
        showMovieRoomList();
        initialScheduleView();
    }

    public void showMovieList() {
        //每次显示先清除列表
        movieInfos.clear();
        //获取最新的账号信息列表
        movieInfos = DAO.getInstance().getMovieInfoList();
        if (movieInfos == null) {
            showMessageDialog(null,"加载电影数据出错！","提示", JOptionPane.ERROR_MESSAGE);
            return;
        }
        //将数据映射到每一列
        MOVIE_ID.setCellValueFactory(new PropertyValueFactory<>("mid"));
        MOVIE_NAME.setCellValueFactory(new PropertyValueFactory<>("mname"));
        MOVIE_TIME.setCellValueFactory(new PropertyValueFactory<>("mtime"));
        SCREEN.setCellValueFactory(new PropertyValueFactory<>("screen"));
        //将数据添加到表中
        MOVIE_VIEW.setItems(movieInfos);
    }

    public void showMovieRoomList() {
        //每次显示先清除列表
        movieRoomInfos.clear();
        //获取最新的账号信息列表
        movieRoomInfos = DAO.getInstance().getMovieRoomInfoList();
        if (movieRoomInfos == null) {
            showMessageDialog(null,"加载影厅数据出错！","提示", JOptionPane.ERROR_MESSAGE);
            return;
        }
        //将数据映射到每一列
        YTID.setCellValueFactory(new PropertyValueFactory<>("roomid"));
        YTMC.setCellValueFactory(new PropertyValueFactory<>("rname"));
        ZXHS.setCellValueFactory(new PropertyValueFactory<>("row_num"));
        ZXLS.setCellValueFactory(new PropertyValueFactory<>("column_num"));
        SFSY.setCellValueFactory(new PropertyValueFactory<>("useflag"));
        //将数据添加到表中
        MOVIEROOM_VIEW.setItems(movieRoomInfos);
    }

    @FXML
    private void onAddMovie() throws Exception {
        AddMovieView addMovieView = new AddMovieView();
        addMovieView.showWindow();
    }

    @FXML
    private void onScreen() throws Exception {
        ScreenView screenView = new ScreenView();
        screenView.showWindow();
    }

    @FXML
    private void onDeleteMovie() throws Exception {
        DeleteMovieView deleteMovieView = new DeleteMovieView();
        deleteMovieView.showWindow();
    }

    @FXML
    private void onChooseAddMovieRoomButton() throws Exception {
        AddMovieRoomView addMovieRoomView = new AddMovieRoomView();
        addMovieRoomView.showWindow();
    }

    @FXML
    private void onChooseOpenMovieRoomButton() throws Exception {
        ChangeMovieRoomView changeMovieRoomView = new ChangeMovieRoomView();
        changeMovieRoomView.showWindow();
    }

    @FXML
    private void onChooseDeleteMovieRoomButton() throws Exception {
        DeleteMovieRoomView deleteMovieRoomView = new DeleteMovieRoomView();
        deleteMovieRoomView.showWindow();
    }

    @FXML
    private void onChooseOK1Button() {
        if (SCHEDULE_DATE.getValue() == null) {
            showMessageDialog(null,"未选择日期！","提示",JOptionPane.ERROR_MESSAGE);
            return;
        }
        targetDate = SCHEDULE_DATE.getValue().toString();
        SimpleDateFormat simpleDateFormat = new SimpleDateFormat("yyyy-MM-dd");
        try {
                Date date1,date2;
                date1 = simpleDateFormat.parse(targetDate);//选取日期
                date2 = simpleDateFormat.parse(simpleDateFormat.format(new Date()));//系统日期
                long defDays = (date1.getTime() - date2.getTime()) / (24 * 60 * 60 * 1000);
                if (defDays > 7) {
                    showMessageDialog(null,"选取日期超过7天！","提示",JOptionPane.ERROR_MESSAGE);
                }
                else {
                    showScheduleList();
                }
        } catch (ParseException e) {
            e.printStackTrace();
        }
    }

    public void initialScheduleView() {
        ArrayList<Integer> movieRoomIDList = DAO.getInstance().getMovieRoomIDList();
        ArrayList<String> movieNameList = DAO.getInstance().getMovieNameList();
        if (movieRoomIDList == null || movieNameList == null) {
            showMessageDialog(null,"数据加载错误！","提示",JOptionPane.ERROR_MESSAGE);
            return;
        }
        //初始化影厅ID下拉选择框
        ADD_YTID.getItems().setAll(movieRoomIDList);
        //初始化电影名下拉选择框
        ADD_DYMC.getItems().setAll(movieNameList);
        //清除时间、分钟下拉选择框
        ADD_HOUR.getItems().clear();
        ADD_MIN.getItems().clear();
        //清除额定票价输入框
        ADD_EDPJ.setText("");
        //清除删除影厅ID输入框
        DEL_DQID.setText("");
        //清除复用日期选择
        FYRQ.setValue(null);
        //初始化开始时间的时选择框
        for (int i = 0; i < 24; i++) {
            ADD_HOUR.getItems().add(i);
        }
        //初始化开始时间的分选择框
        for (int i = 0; i < 60; i++) {
            ADD_MIN.getItems().add(i);
        }
        //初始化选项
        ADD_YTID.getSelectionModel().select(0);
        ADD_DYMC.getSelectionModel().select(0);
        ADD_HOUR.getSelectionModel().select(0);
        ADD_MIN.getSelectionModel().select(0);
    }

    public void showScheduleList() {
        if (SCHEDULE_DATE.getValue() == null) {
            return;
        }
        targetDate = SCHEDULE_DATE.getValue().toString();
        //每次显示前清除列表
        scheduleInfos.clear();
        //获取指定日期的档期信息列表
        scheduleInfos = DAO.getInstance().getScheduleInfoListByDate(targetDate);
        if (scheduleInfos == null) {
            showMessageDialog(null,"加载档期数据出错！","提示", JOptionPane.ERROR_MESSAGE);
            return;
        }
        //将数据映射到每一列
        S_DQID.setCellValueFactory(new PropertyValueFactory<>("schedule_id"));
        S_YTID.setCellValueFactory(new PropertyValueFactory<>("room_id"));
        S_DYMC.setCellValueFactory(new PropertyValueFactory<>("movie_name"));
        S_KSSJ.setCellValueFactory(new PropertyValueFactory<>("show_time"));
        S_JSSJ.setCellValueFactory(new PropertyValueFactory<>("end_time"));
        S_BFRQ.setCellValueFactory(new PropertyValueFactory<>("show_date"));
        S_EDPJ.setCellValueFactory(new PropertyValueFactory<>("normal_price"));
        //将数据添加到列表中
        SCHEDULE_VIEW.setItems(scheduleInfos);
    }

    @FXML
    private void onChooseOK2Button() {
        if (targetDate == null) {
            showMessageDialog(null,"未选择日期！","提示",JOptionPane.ERROR_MESSAGE);
            return;
        }
        SimpleDateFormat simpleDateFormat = new SimpleDateFormat("yyyy-MM-dd");
        try {
            Date date1,date2;
            date1 = simpleDateFormat.parse(targetDate);//选取日期
            date2 = simpleDateFormat.parse(simpleDateFormat.format(new Date()));//系统日期
            long defDays = (date1.getTime() - date2.getTime()) / (24 * 60 * 60 * 1000);
            if (defDays < 0) {
                showMessageDialog(null,"日期选择不合理！","提示",JOptionPane.ERROR_MESSAGE);
                return;
            }
        } catch (ParseException e) {
            e.printStackTrace();
        }
        if (ADD_EDPJ.getText().isEmpty()) {
            showMessageDialog(null,"未输入价格！","提示",JOptionPane.ERROR_MESSAGE);
            return;
        }
        if (!Util.isNumeric(ADD_EDPJ.getText())) {
            showMessageDialog(null,"输入的价格不是数字！","提示",JOptionPane.ERROR_MESSAGE);
            return;
        }
        if (Double.parseDouble(ADD_EDPJ.getText()) > 999.0) {
            showMessageDialog(null,"输入价格过大！","提示",JOptionPane.ERROR_MESSAGE);
            return;
        }
        //获取选取的开始时间
        Integer hours = ADD_HOUR.getSelectionModel().getSelectedItem();
        Integer minutes = ADD_MIN.getSelectionModel().getSelectedItem();
        //转换为分钟
        Integer beginTime = hours * 60 + minutes;
        int room_id = ADD_YTID.getSelectionModel().getSelectedItem();
        String movieName = ADD_DYMC.getSelectionModel().getSelectedItem();
        int movie_id = DAO.getInstance().getMovieIDByName(movieName);
        if (movie_id == -1) {
            showMessageDialog(null,"加载电影ID出错！","提示",JOptionPane.ERROR_MESSAGE);
            return;
        }
        Time movieTime = DAO.getInstance().getMovieTime(movieName);
        if (movieTime == null) {
            showMessageDialog(null,"加载数据出错！","提示",JOptionPane.ERROR_MESSAGE);
            return;
        }
        //计算结束时间：开始时间 + 电影时长
        Integer endTime = beginTime + Integer.parseInt(movieTime.toString().substring(0,2)) * 60 + Integer.parseInt(movieTime.toString().substring(3,5));
        if (endTime > 23 * 60 + 55) {
            showMessageDialog(null,"电影结束时间超出当天营业时间！","提示",JOptionPane.ERROR_MESSAGE);
            return;
        }
        Tuple<Integer,Integer> time = new Tuple<>(beginTime,endTime);
        ArrayList<Tuple<Integer,Integer>> timeList = DAO.getInstance().getTimeTupleFromMovieRoom(room_id, SCHEDULE_DATE.getValue().toString());
        if (!Util.timeConflictDetection(time, timeList)) {
            showMessageDialog(null,"存在时间段冲突！","提示",JOptionPane.ERROR_MESSAGE);
            return;
        }
        String show_time = String.format("%d:%d:00",ADD_HOUR.getSelectionModel().getSelectedItem(),ADD_MIN.getSelectionModel().getSelectedItem());
        String end_time = String.format("%d:%d:00",endTime / 60, endTime % 60);
        System.out.println(show_time+" "+end_time);
        ScheduleInfo scheduleInfo = new ScheduleInfo(null, movie_id, movieName, room_id, show_time, end_time, targetDate, Double.parseDouble(ADD_EDPJ.getText()));
        if (!DAO.getInstance().insertScheduleInfo(scheduleInfo)) {
            showMessageDialog(null,"添加档期出错！","提示",JOptionPane.ERROR_MESSAGE);
            return;
        }
        //添加完毕后刷新界面
        initialScheduleView();
        showScheduleList();
    }

    @FXML
    private void onChooseOK3Button() {
        String scheduleID = DEL_DQID.getText();
        if (!Util.isNumeric(scheduleID)) {
            showMessageDialog(null,"档期ID只能是数字！","提示",JOptionPane.ERROR_MESSAGE);
            return;
        }
        ResultSet re = DAO.getInstance().getScheduleInfo(Integer.parseInt(scheduleID));
        if (re == null) {
            showMessageDialog(null,"数据访问异常！","提示",JOptionPane.ERROR_MESSAGE);
            return;
        }
        try {
            if (!re.next()) {
                showMessageDialog(null,"档期不存在！","提示",JOptionPane.ERROR_MESSAGE);
                return;
            }
            Alert alert = new Alert(Alert.AlertType.CONFIRMATION);
            alert.setHeaderText("确认删除吗？");
            Optional<ButtonType> result = alert.showAndWait();
            if (result.get() == ButtonType.OK) {
                if (!DAO.getInstance().deleteScheduleInfo(Integer.parseInt(scheduleID))) {
                    showMessageDialog(null,"删除失败！","提示",JOptionPane.ERROR_MESSAGE);
                    return;
                }
                showMessageDialog(null,"删除成功！","提示",JOptionPane.INFORMATION_MESSAGE);
                //删除完毕后刷新界面
                initialScheduleView();
                showScheduleList();
            }
            else {
                alert.close();
            }
        } catch (SQLException e) {
            e.printStackTrace();
        }
    }

    @FXML
    private void onChooseOK4Button() {
        if (FYRQ.getValue() == null) {
            showMessageDialog(null,"未选择复用日期！","提示",JOptionPane.ERROR_MESSAGE);
            return;
        }
        sourseDate = FYRQ.getValue().toString();
        System.out.println(sourseDate);
        ObservableList<ScheduleInfo> list = DAO.getInstance().getScheduleInfoListByDate(sourseDate);
        if (list == null) {
            showMessageDialog(null,"数据访问异常！","提示",JOptionPane.ERROR_MESSAGE);
            return;
        }
        for (ScheduleInfo scheduleInfo : list) {
            scheduleInfo.setShow_date(targetDate);//将当前的日期修改为当前选择的档期
        }
        if (!DAO.getInstance().updateScheduleInfoByScheduleInfoList(list)) {
            showMessageDialog(null,"复用档期失败！","提示",JOptionPane.ERROR_MESSAGE);
            return;
        }
        showMessageDialog(null,"复用成功！","提示",JOptionPane.INFORMATION_MESSAGE);
        //添加完毕后刷新界面
        initialScheduleView();
        showScheduleList();
    }
}
