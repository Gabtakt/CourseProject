package admin;

import javafx.fxml.FXML;
import javafx.scene.control.*;
import util.DAO;

import javax.swing.*;
import java.sql.ResultSet;
import java.sql.SQLException;

import static javax.swing.JOptionPane.showMessageDialog;
import static util.Util.isNumeric;

public class ScreenController {
    @FXML
    private RadioButton SCREEN_RADIOBUTTON;
    @FXML
    private RadioButton UNLOAD_RADIOBUTTON;
    @FXML
    private TextField DYID;

    @FXML
    private void initialize() {
        final ToggleGroup group = new ToggleGroup();
        SCREEN_RADIOBUTTON.setToggleGroup(group);
        SCREEN_RADIOBUTTON.setSelected(true);
        UNLOAD_RADIOBUTTON.setToggleGroup(group);
    }

    @FXML
    private void onChooseOKButton() throws SQLException {
        String movieid = DYID.getText();
        boolean screen = SCREEN_RADIOBUTTON.isSelected();
        if (movieid.isEmpty()) {
            showMessageDialog(null,"未输入电影ID！","提示", JOptionPane.ERROR_MESSAGE);
        }
        else if (!isNumeric(movieid)) {
            showMessageDialog(null,"电影ID只能是数字！","提示", JOptionPane.ERROR_MESSAGE);
        }
        else {
            //查询目标电影是否存在
            ResultSet re = DAO.getInstance().getMovieInfo(Integer.parseInt(movieid));
            if (re == null) {
                showMessageDialog(null,"访问数据异常！","提示", JOptionPane.ERROR_MESSAGE);
            }
            else if (!re.next()) {
                showMessageDialog(null,"电影不存在！","提示", JOptionPane.ERROR_MESSAGE);
            }
            //若存在则进行更新
            else if (!DAO.getInstance().screenMovie(Integer.parseInt(movieid), screen)) {
                    showMessageDialog(null,"更新数据失败！","提示", JOptionPane.ERROR_MESSAGE);
                }
                else {
                    showMessageDialog(null,"操作成功！","提示", JOptionPane.INFORMATION_MESSAGE);
                    ManagerController.getInstance().showMovieList();
                    //更新完毕后刷新档期列表
                    ManagerController.getInstance().initialScheduleView();
                    ManagerController.getInstance().showScheduleList();
                    ScreenView.getStage().close();
                }
        }
    }

    @FXML
    private void onChooseCloseButton() {
        ScreenView.getStage().close();
    }
}
