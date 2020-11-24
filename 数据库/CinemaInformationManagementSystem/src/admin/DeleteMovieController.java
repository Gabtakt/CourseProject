package admin;

import data.MovieInfo;
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

public class DeleteMovieController {
    @FXML
    private TextField DYID;

    @FXML
    private void initialize() {

    }

    @FXML
    private void onChooseOKButton() throws SQLException {
        String movieid = DYID.getText();
        if (movieid.isEmpty()) {
            showMessageDialog(null,"未输入电影ID！","提示", JOptionPane.ERROR_MESSAGE);
        }
        else if (!isNumeric(movieid)) {
            showMessageDialog(null,"电影ID只能是数字！","提示", JOptionPane.ERROR_MESSAGE);
        }
        else {
            ResultSet re = DAO.getInstance().getMovieInfo(Integer.parseInt(movieid));
            if (re == null) {
                showMessageDialog(null,"数据访问失败！","提示", JOptionPane.ERROR_MESSAGE);
            }
            else if (!re.next()) {
                showMessageDialog(null,"电影不存在！","提示", JOptionPane.ERROR_MESSAGE);
            }
            else {
                MovieInfo movieInfo = new MovieInfo(re.getInt("movieid"),re.getString("mname"),re.getString("mtime"),re.getBoolean("screen"));
                Alert alert = new Alert(Alert.AlertType.CONFIRMATION);
                alert.setHeaderText(String.format("确认删除电影《%s》吗？",movieInfo.getMname()));
                alert.setContentText(String.format("电影信息 ID：%d，时长：%s，是否上映：%s",movieInfo.getMid(),movieInfo.getMtime(),movieInfo.isScreen()));

                Optional<ButtonType> result = alert.showAndWait();
                if (result.get() == ButtonType.OK) {
                    if (!DAO.getInstance().deleteMovieInfo(Integer.parseInt(movieid))){
                        showMessageDialog(null,"删除电影失败！","提示", JOptionPane.ERROR_MESSAGE);
                    }
                    else {
                        showMessageDialog(null,"删除电影成功！","提示", JOptionPane.INFORMATION_MESSAGE);
                        ManagerController.getInstance().showMovieList();
                        //更新完毕后刷新档期列表
                        ManagerController.getInstance().initialScheduleView();
                        ManagerController.getInstance().showScheduleList();
                        DeleteMovieView.getStage().close();
                    }
                }
                else {
                    alert.close();
                }
            }
        }
    }

    @FXML
    private void onChooseCloseButton() {
        DeleteMovieView.getStage().close();
    }
}
