package seller;

import data.MovieScheduleInfo;
import data.TicketInfo;
import data.Tuple;
import javafx.collections.FXCollections;
import javafx.collections.ObservableList;
import javafx.fxml.FXML;
import javafx.scene.control.*;
import javafx.scene.layout.AnchorPane;
import javafx.scene.layout.Background;
import javafx.scene.layout.BackgroundFill;
import javafx.scene.paint.Paint;
import util.Config;
import util.DAO;

import javax.swing.*;

import java.text.ParseException;
import java.text.SimpleDateFormat;
import java.util.ArrayList;
import java.util.Date;

import static javax.swing.JOptionPane.showMessageDialog;

public class SellerController {
    //界面组件绑定
    @FXML
    private DatePicker DATE;
    @FXML
    private ChoiceBox<String> MOVIE;
    @FXML
    private TextArea MOVIE_INFO;
    @FXML
    private ChoiceBox<String> TIME;
    @FXML
    private ChoiceBox<Integer> ROOM;
    @FXML
    private ChoiceBox<String> TYPE;
    @FXML
    private TextField PRICE;
    @FXML
    private AnchorPane SEAT_PANE;

    //辅助数据定义
    private boolean isSelectDate;
    private boolean isSelectMovie;
    private boolean isSelectTime;
    private boolean isSelectRoom;
    private boolean isSelectPreview;
    private boolean isSelectSeat;
    private boolean isAckSeat;
    private boolean isSelectType;
    private String show_date;
    private ArrayList<String> movieNameList;
    private String movieName;
    private int movieID;
    private ObservableList<MovieScheduleInfo> movieScheduleInfos;
    private StringBuilder movieMessage;
    private String show_time;
    private String end_time;
    private ArrayList<Integer> roomIDList;
    private Tuple<Integer,Integer> seatNumTuple;
    private int roomID;
    private int scheduleID;
    private ObservableList<Tuple<Integer,Integer>> seatTupleList;
    private CheckBox[][] checkBoxes;
    private ObservableList<Tuple<Integer,Integer>> selectSeatsList;
    private int ticketType;
    private double normalPrice;
    private double discountPrice;
    private ObservableList<TicketInfo> ticketInfos;
    private static SellerController instance;

    @FXML
    private void initialize() {
        //初始化辅助数据
        instance = this;
        isSelectDate = false;
        isSelectMovie = false;
        isSelectTime = false;
        isSelectRoom = false;
        isSelectPreview = false;
        isSelectSeat = false;
        isAckSeat = false;
        isSelectType = false;
        show_date = "";
        movieNameList= new ArrayList<>();
        movieName = "";
        movieID = 0;
        movieScheduleInfos = FXCollections.observableArrayList();
        movieMessage = new StringBuilder();
        show_time ="";
        end_time = "";
        roomIDList= new ArrayList<>();
        seatNumTuple = new Tuple<>(0,0);
        roomID = 0;
        scheduleID = 0;
        seatTupleList = FXCollections.observableArrayList();
        checkBoxes = new CheckBox[Config.MAX_ROW_NUM][Config.MAX_COLUMN_NUM];
        selectSeatsList = FXCollections.observableArrayList();
        ticketInfos = FXCollections.observableArrayList();
        ticketType = -1;
        normalPrice = discountPrice = 0.0;
        //清除所有组件内容
        DATE.setValue(null);
        MOVIE.getItems().clear();
        TIME.getItems().clear();
        ROOM.getItems().clear();
        TYPE.getItems().clear();
        PRICE.setText("");
        PRICE.setEditable(false);
        MOVIE_INFO.setText("");
        MOVIE_INFO.setEditable(false);
        SEAT_PANE.getChildren().clear();
        //设定票种类型信息
        TYPE.getItems().setAll("全票","学生票");
        TYPE.getSelectionModel().select(0);
    }

    @FXML
    private void onSelectDate() {
        isSelectDate = false;
        isSelectMovie = false;
        isSelectTime = false;
        isSelectRoom = false;
        isSelectPreview = false;
        isSelectSeat = false;
        isAckSeat = false;
        isSelectType = false;
        MOVIE.getItems().clear();
        MOVIE_INFO.setText("");
        TIME.getItems().clear();
        ROOM.getItems().clear();
        PRICE.setText("");
        SEAT_PANE.getChildren().clear();
        if (DATE.getValue() == null) {
            showMessageDialog(null,"未选择观影日期！","提示", JOptionPane.ERROR_MESSAGE);
            return;
        }
        show_date = DATE.getValue().toString();
        SimpleDateFormat simpleDateFormat = new SimpleDateFormat("yyyy-MM-dd");
        try {
            Date date1 = simpleDateFormat.parse(show_date);
            Date date2 = simpleDateFormat.parse(simpleDateFormat.format(new Date()));//系统档期日期
            long def = (date1.getTime() - date2.getTime());
            if (def < 0) {
                showMessageDialog(null,"观影日期选择不合理！","提示", JOptionPane.ERROR_MESSAGE);
                return;
            }
        } catch (ParseException e) {
            e.printStackTrace();
        }
        movieNameList = DAO.getInstance().getMovieNameByWatchDate(show_date);
        if (movieNameList == null) {
            showMessageDialog(null,"数据访问异常！","提示", JOptionPane.ERROR_MESSAGE);
            return;
        }
        if (movieNameList.size() == 0) {
            showMessageDialog(null,"当天没有电影安排！","提示", JOptionPane.ERROR_MESSAGE);
            return;
        }
        MOVIE.getItems().addAll(movieNameList);
        MOVIE.getSelectionModel().select(0);
        isSelectDate = true;
    }

    @FXML
    private void onSelectMovie() {
        isSelectMovie = false;
        isSelectTime = false;
        isSelectRoom = false;
        isSelectPreview = false;
        isSelectSeat = false;
        isAckSeat = false;
        isSelectType = false;
        MOVIE_INFO.setText("");
        TIME.getItems().clear();
        ROOM.getItems().clear();
        PRICE.setText("");
        SEAT_PANE.getChildren().clear();
        if (!isSelectDate) {
            showMessageDialog(null,"未选择观影日期！","提示", JOptionPane.ERROR_MESSAGE);
            return;
        }
        movieName = MOVIE.getSelectionModel().getSelectedItem();
        movieID = DAO.getInstance().getMovieIDByName(movieName);
        if (movieID == -1) {
            showMessageDialog(null,"数据访问异常！","提示", JOptionPane.ERROR_MESSAGE);
            return;
        }
        movieScheduleInfos = DAO.getInstance().getMovieScheduleInfo(movieID,show_date);
        if (movieScheduleInfos == null) {
            showMessageDialog(null,"数据访问异常！","提示", JOptionPane.ERROR_MESSAGE);
            return;
        }
        //使用前清空容器
        movieMessage.delete(0,movieMessage.length());
        for (MovieScheduleInfo movieScheduleInfo : movieScheduleInfos) {
            movieMessage.append(movieScheduleInfo.toString()).append("\n");
        }
        //显示前清空文本区内容
        MOVIE_INFO.setText(movieMessage.toString());
        boolean isEqual = false;
        SimpleDateFormat df = new SimpleDateFormat("HH:mm");//设置日期格式
        String t = df.format(new Date());
        String[] times = t.split(":");
        int localTime = Integer.parseInt(times[0]) * 60 + Integer.parseInt(times[1]);
        String localDate = new SimpleDateFormat("yyyy-MM-dd").format(new Date());
        for (MovieScheduleInfo movieScheduleInfo : movieScheduleInfos) {
            for (String time : TIME.getItems()) {
                if (time.equals(movieScheduleInfo.getTimeTuple().toString())) {
                    isEqual = true;
                    break;
                }
            }
            if (isEqual) {
                isEqual = false;
                continue;
            }
            String beginTime = movieScheduleInfo.getTimeTuple().getP1();
            String[] times2 = beginTime.split(":");
            int tt = Integer.parseInt(times2[0]) * 60 + Integer.parseInt(times2[1]);
            if (localDate.equals(show_date) && tt < localTime) {
                continue;
            }
            TIME.getItems().add(movieScheduleInfo.getTimeTuple().toString());
            isEqual = false;
        }
        TIME.getSelectionModel().select(0);
        isSelectMovie = true;
    }

    @FXML
    private void onSelectTime() {
        isSelectTime = false;
        isSelectRoom = false;
        isSelectPreview = false;
        isSelectSeat = false;
        isAckSeat = false;
        isSelectType = false;
        ROOM.getItems().clear();
        PRICE.setText("");
        SEAT_PANE.getChildren().clear();
        if (!isSelectDate) {
            showMessageDialog(null,"未选择日期！","提示", JOptionPane.ERROR_MESSAGE);
            return;
        }
        if (!isSelectMovie) {
            showMessageDialog(null,"未选择电影！","提示", JOptionPane.ERROR_MESSAGE);
            return;
        }
        String[] timeValue = TIME.getSelectionModel().getSelectedItem().split("-");
        show_time = timeValue[0];
        end_time = timeValue[1];
//        movieID = DAO.getInstance().getMovieIDByName(movieName);
//        if (movieID == -1) {
//            showMessageDialog(null,"数据访问异常！","提示", JOptionPane.ERROR_MESSAGE);
//            return;
//        }
        roomIDList = DAO.getInstance().getMovieRoomIDListBySelectInfo(movieID, show_time, end_time, show_date);
        if (roomIDList == null) {
            showMessageDialog(null,"数据访问异常！","提示", JOptionPane.ERROR_MESSAGE);
            return;
        }
        ROOM.getItems().addAll(roomIDList);
        ROOM.getSelectionModel().select(0);
        isSelectTime = true;
    }

    @FXML
    private void onSelectRoom() {
        isSelectRoom = false;
        isSelectPreview = false;
        isSelectSeat = false;
        isAckSeat = false;
        isSelectType = false;
        PRICE.setText("");
        SEAT_PANE.getChildren().clear();
        if (!isSelectDate) {
            showMessageDialog(null,"未选择日期！","提示", JOptionPane.ERROR_MESSAGE);
            return;
        }
        if (!isSelectMovie) {
            showMessageDialog(null,"未选择电影！","提示", JOptionPane.ERROR_MESSAGE);
            return;
        }
        if (!isSelectTime) {
            showMessageDialog(null,"未选择观影时间！","提示", JOptionPane.ERROR_MESSAGE);
            return;
        }
        roomID = ROOM.getSelectionModel().getSelectedItem();
        seatNumTuple = DAO.getInstance().getMovieRoomSeatTuple(roomID);
        if (seatNumTuple.getP1() == 0 && seatNumTuple.getP2() == 0) {
            showMessageDialog(null,"数据访问出错！","提示", JOptionPane.ERROR_MESSAGE);
            return;
        }
        isSelectRoom = true;
    }

    @FXML
    private void onPreviewSeat() {
        isSelectPreview = false;
        isSelectSeat = false;
        isAckSeat = false;
        isSelectType = false;
        PRICE.setText("");
        if (!isSelectDate) {
            showMessageDialog(null,"未选择日期！","提示", JOptionPane.ERROR_MESSAGE);
            return;
        }
        if (!isSelectMovie) {
            showMessageDialog(null,"未选择电影！","提示", JOptionPane.ERROR_MESSAGE);
            return;
        }
        if (!isSelectTime) {
            showMessageDialog(null,"未选择观影时间！","提示", JOptionPane.ERROR_MESSAGE);
            return;
        }
        if (!isSelectRoom) {
            showMessageDialog(null,"未选择影厅！","提示", JOptionPane.ERROR_MESSAGE);
            return;
        }
        renderSeatGraph();
        isSelectPreview = true;
    }

    public void renderSeatGraph() {
        SEAT_PANE.getChildren().clear();
        scheduleID = DAO.getInstance().getScheduleIDBySelectInfo(movieID,roomID,show_time,end_time,show_date);
        if (scheduleID == -1) {
            showMessageDialog(null,"数据访问异常！","提示", JOptionPane.ERROR_MESSAGE);
            return;
        }
        seatTupleList = DAO.getInstance().getSoldSeatInfoList(scheduleID);
        if (seatTupleList == null) {
            showMessageDialog(null,"数据访问异常！","提示", JOptionPane.ERROR_MESSAGE);
            return;
        }
        int row_num = seatNumTuple.getP1();
        int column_num =seatNumTuple.getP2();
        int width = Config.PREF_WIDTH / column_num;
        int weight = Config.PREF_WEIGHT / row_num;
        for (int i = 0;i < row_num; i++) {
            for (int j = 0; j < column_num; j++) {
                CheckBox checkBox = new CheckBox();
                checkBoxes[i][j] = checkBox;
                checkBox.setLayoutX(j * width + 20);
                checkBox.setLayoutY(i * weight);
                if (new Tuple<>(i+1,j+1).beContained(seatTupleList)) {
                    checkBox.setText("已售出");
                    checkBox.setBackground(new Background(new BackgroundFill(Paint.valueOf("#ff0000"),null,null)));
                    checkBox.setOnMouseClicked((e) -> checkBox.setSelected(!checkBox.isSelected()));
                }
                else {
                    checkBox.setText(String.format("%d排%d座",i+1,j+1));
                }
                SEAT_PANE.getChildren().add(checkBox);
            }
        }
    }

    @FXML
    private void onSelectSeat() {
        isSelectSeat = false;
        isSelectType = false;
        PRICE.setText("");
        selectSeatsList.clear();
        if (!isSelectDate) {
            showMessageDialog(null,"未选择日期！","提示", JOptionPane.ERROR_MESSAGE);
            return;
        }
        if (!isSelectMovie) {
            showMessageDialog(null,"未选择电影！","提示", JOptionPane.ERROR_MESSAGE);
            return;
        }
        if (!isSelectTime) {
            showMessageDialog(null,"未选择观影时间！","提示", JOptionPane.ERROR_MESSAGE);
            return;
        }
        if (!isSelectRoom) {
            showMessageDialog(null,"未选择影厅！","提示", JOptionPane.ERROR_MESSAGE);
            return;
        }
        if (!isSelectPreview) {
            showMessageDialog(null,"未预览坐席！","提示", JOptionPane.ERROR_MESSAGE);
            return;
        }
        for (int i = 0;i < seatNumTuple.getP1();i++) {
            for (int j = 0;j < seatNumTuple.getP2();j++) {
                if (checkBoxes[i][j].isSelected()) {
                    isSelectSeat = true;
                }
            }
        }
        if (!isSelectSeat) {
            showMessageDialog(null,"未选择座位！","提示", JOptionPane.ERROR_MESSAGE);
            return;
        }
        for (int i = 0;i < seatNumTuple.getP1();i++) {
            for (int j = 0;j < seatNumTuple.getP2();j++) {
                if (checkBoxes[i][j].isSelected()) {
                    selectSeatsList.add(new Tuple<>(i+1,j+1));
                }
            }
        }
        Alert alert = new Alert(Alert.AlertType.INFORMATION);
        alert.setHeaderText("选座信息");
        StringBuilder str = new StringBuilder();
        for (Tuple<Integer,Integer> tuple : selectSeatsList) {
            str.append(String.format("%d排%d座 ",tuple.getP1(),tuple.getP2()));
        }
        alert.setContentText(str.toString().trim());
        alert.showAndWait();
        TYPE.getSelectionModel().select(0);
        isAckSeat = true;
    }

    @FXML
    private void onSelectTicketType() {
        isSelectType = false;
        if (!isSelectDate) {
            showMessageDialog(null,"未选择日期！","提示", JOptionPane.ERROR_MESSAGE);
            return;
        }
        if (!isSelectMovie) {
            showMessageDialog(null,"未选择电影！","提示", JOptionPane.ERROR_MESSAGE);
            return;
        }
        if (!isSelectTime) {
            showMessageDialog(null,"未选择观影时间！","提示", JOptionPane.ERROR_MESSAGE);
            return;
        }
        if (!isSelectRoom) {
            showMessageDialog(null,"未选择影厅！","提示", JOptionPane.ERROR_MESSAGE);
            return;
        }
        if (!isSelectPreview) {
            showMessageDialog(null,"未预览坐席！","提示", JOptionPane.ERROR_MESSAGE);
            return;
        }
        if (!isAckSeat) {
            showMessageDialog(null,"未确认选座！","提示", JOptionPane.ERROR_MESSAGE);
            return;
        }
        ticketType = TYPE.getSelectionModel().getSelectedIndex();
        double discount = ticketType == 1 ? 0.5 : 1.0;
        normalPrice = DAO.getInstance().getNormalPrice(scheduleID);
        if (normalPrice == -1) {
            showMessageDialog(null,"数据访问异常！","提示", JOptionPane.ERROR_MESSAGE);
            return;
        }
        discountPrice = normalPrice * discount;
        PRICE.setText(String.format("%3.1f",discountPrice * selectSeatsList.size()));
        isSelectType = true;
    }

    @FXML
    private void onByTicket() {
        ticketInfos.clear();
        if (!isSelectDate) {
            showMessageDialog(null,"未选择日期！","提示", JOptionPane.ERROR_MESSAGE);
            return;
        }
        if (!isSelectMovie) {
            showMessageDialog(null,"未选择电影！","提示", JOptionPane.ERROR_MESSAGE);
            return;
        }
        if (!isSelectTime) {
            showMessageDialog(null,"未选择观影时间！","提示", JOptionPane.ERROR_MESSAGE);
            return;
        }
        if (!isSelectRoom) {
            showMessageDialog(null,"未选择影厅！","提示", JOptionPane.ERROR_MESSAGE);
            return;
        }
        if (!isSelectPreview) {
            showMessageDialog(null,"未预览坐席！","提示", JOptionPane.ERROR_MESSAGE);
            return;
        }
        if (!isAckSeat) {
            showMessageDialog(null,"未确认选座！","提示", JOptionPane.ERROR_MESSAGE);
            return;
        }
        if (!isSelectType) {
            showMessageDialog(null, "未选择票种类型！", "提示", JOptionPane.ERROR_MESSAGE);
            return;
        }
        for (Tuple<Integer,Integer> tuple : selectSeatsList) {
            //TicketInfo(Integer tid, Integer schedule_id, Integer seat_row, Integer seat_column, Integer ticket_type, boolean use_flag, Double ap)
            ticketInfos.add(new TicketInfo(null,scheduleID,tuple.getP1(),tuple.getP2(),ticketType,false,discountPrice));
        }
        if (!DAO.getInstance().insertTicketInfos(ticketInfos)) {
            showMessageDialog(null, "购票事务失败！", "提示", JOptionPane.ERROR_MESSAGE);
            renderSeatGraph();
            return;
        }
        showMessageDialog(null, "购票成功！", "提示", JOptionPane.INFORMATION_MESSAGE);
        Alert alert = new Alert(Alert.AlertType.INFORMATION);
        alert.setHeaderText("购票信息");
        StringBuilder stringBuilder = new StringBuilder();
        for (TicketInfo ticketInfo : ticketInfos) {
            ticketInfo.setTid(DAO.getInstance().getTicketID(scheduleID,ticketInfo.getSeat_row(),ticketInfo.getSeat_column()));
            ticketInfo.setMovieName(movieName);
            ticketInfo.setMovieRoomID(movieID);
            stringBuilder.append(ticketInfo.toString());
        }
        alert.setContentText(stringBuilder.toString());
        alert.showAndWait();
        renderSeatGraph();
    }

    @FXML
    private void onRefund() throws Exception {
        RefundView refundView = new RefundView();
        refundView.showWindow();
    }

    @FXML
    private void onReselect() {
        initialize();
    }

    public static SellerController getInstance() {
        return instance;
    }
}
