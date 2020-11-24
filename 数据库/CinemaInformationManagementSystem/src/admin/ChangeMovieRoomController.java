package admin;

import data.MovieRoomInfo;
import javafx.fxml.FXML;
import javafx.scene.control.RadioButton;
import javafx.scene.control.TextField;
import javafx.scene.control.ToggleGroup;
import util.DAO;

import javax.swing.*;
import java.awt.*;
import java.sql.ResultSet;
import java.sql.SQLException;

import static javax.swing.JOptionPane.showMessageDialog;
import static util.Util.isNumeric;

public class ChangeMovieRoomController {
    @FXML
    private TextField YTID;
    @FXML
    private RadioButton YES_RADIOBUTTON;
    @FXML
    private RadioButton NO_RADIOBUTTON;

    @FXML
    private void initialize() {
        final ToggleGroup group = new ToggleGroup();
        YES_RADIOBUTTON.setToggleGroup(group);
        YES_RADIOBUTTON.setSelected(true);
        NO_RADIOBUTTON.setToggleGroup(group);
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
            showMessageDialog(null,"查询数据出错！","提示", JOptionPane.ERROR_MESSAGE);
            return;
        }
        if (!re.next()) {
            showMessageDialog(null,"影厅不存在！","提示", JOptionPane.ERROR_MESSAGE);
            return;
        }
        if (!DAO.getInstance().useMovieRoom(Integer.parseInt(roomid), YES_RADIOBUTTON.isSelected())) {
            showMessageDialog(null,"更新影厅使用信息失败！","提示", JOptionPane.ERROR_MESSAGE);
            return;
        }
        showMessageDialog(null,"更新影厅使用信息成功！","提示", JOptionPane.INFORMATION_MESSAGE);
        ChangeMovieRoomView.getStage().close();
        //更新完毕后重新显示影厅信息
        ManagerController.getInstance().showMovieRoomList();
        //更新完毕后刷新档期列表
        ManagerController.getInstance().initialScheduleView();
        ManagerController.getInstance().showScheduleList();
    }

    @FXML
    private void onChooseCloseButton() {
        ChangeMovieRoomView.getStage().close();
    }
}
