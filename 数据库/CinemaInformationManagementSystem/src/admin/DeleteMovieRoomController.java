package admin;

import data.MovieRoomInfo;
import javafx.fxml.FXML;
import javafx.scene.control.Alert;
import javafx.scene.control.ButtonType;
import javafx.scene.control.TextField;
import util.DAO;

import javax.swing.*;
import java.awt.*;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.util.Optional;

import static javax.swing.JOptionPane.showMessageDialog;
import static util.Util.isNumeric;

public class DeleteMovieRoomController {
    @FXML
    private TextField YTID;

    @FXML
    private void initialize() {

    }
    @FXML
    private void onChooseOKButton() throws SQLException {
        String roomid = YTID.getText();
        if (roomid.isEmpty()) {
            showMessageDialog(null,"未输入影厅ID！","提示", JOptionPane.ERROR_MESSAGE);
            return;
        }
        if (!isNumeric(roomid)) {
            showMessageDialog(null,"影厅ID只能是数字！","提示", JOptionPane.ERROR_MESSAGE);
            return;
        }
        ResultSet re = DAO.getInstance().getMovieRoomInfo(Integer.parseInt(roomid));
        if (re == null) {
            showMessageDialog(null,"数据访问失败！","提示", JOptionPane.ERROR_MESSAGE);
            return;
        }
        if (!re.next()) {
            showMessageDialog(null,"影厅不存在！","提示", JOptionPane.ERROR_MESSAGE);
            return;
        }
        MovieRoomInfo movieRoomInfo = new MovieRoomInfo(re.getInt("roomid"),re.getString("rname"),re.getInt("row_num"),re.getInt("column_num"),re.getBoolean("useflag"));
        Alert alert = new Alert(Alert.AlertType.CONFIRMATION);
        alert.setHeaderText(String.format("确认删除影厅%s吗？",movieRoomInfo.getRname()));
        alert.setContentText(String.format("影厅信息 ID：%d\n行数：%d，列数：%d，是否使用：%s",movieRoomInfo.getRoomid(),movieRoomInfo.getRow_num(),movieRoomInfo.getColumn_num(),movieRoomInfo.isUseflag()));

        Optional<ButtonType> result = alert.showAndWait();
        if (result.get() == ButtonType.OK) {
            if (!DAO.getInstance().deleteMovieRoomInfo(Integer.parseInt(roomid))){
                showMessageDialog(null,"删除失败！","提示", JOptionPane.ERROR_MESSAGE);
            }
            else {
                showMessageDialog(null,"删除成功！","提示", JOptionPane.INFORMATION_MESSAGE);
                ManagerController.getInstance().showMovieRoomList();
                //更新完毕后刷新档期列表
                ManagerController.getInstance().initialScheduleView();
                ManagerController.getInstance().showScheduleList();
                DeleteMovieRoomView.getStage().close();
            }
        }
        else {
            alert.close();
        }
    }

    @FXML
    private void onChooseCloseButton() {
        DeleteMovieRoomView.getStage().close();
    }
}
