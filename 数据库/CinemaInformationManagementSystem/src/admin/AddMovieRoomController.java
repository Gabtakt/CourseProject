package admin;

import data.MovieRoomInfo;
import javafx.fxml.FXML;
import javafx.scene.control.ChoiceBox;
import javafx.scene.control.RadioButton;
import javafx.scene.control.TextField;
import javafx.scene.control.ToggleGroup;
import util.Config;
import util.DAO;

import javax.swing.*;

import static javax.swing.JOptionPane.showMessageDialog;

public class AddMovieRoomController {
    @FXML
    private TextField YTMC;
    @FXML
    private ChoiceBox<Integer> ZXHS;
    @FXML
    private ChoiceBox<Integer> ZXLS;
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
        for (int i = 1; i <= Config.MAX_ROW_NUM; i++) {
            ZXHS.getItems().add(i);
        }
        for (int i = 1;i <= Config.MAX_COLUMN_NUM; i++){

            ZXLS.getItems().add(i);
        }
            ZXHS.getSelectionModel().select(5);
            ZXLS.getSelectionModel().select(7);
    }

    @FXML
    private void onChooseOKButton() {
        String rname = YTMC.getText();
        Integer row_num = ZXHS.getSelectionModel().getSelectedItem();
        Integer column_num = ZXLS.getSelectionModel().getSelectedItem();
        boolean useflag = YES_RADIOBUTTON.isSelected();
        if (rname.isEmpty()) {
            showMessageDialog(null, "未输入影厅名！", "提示", JOptionPane.ERROR_MESSAGE);
            return;
        }
        MovieRoomInfo movieRoomInfo = new MovieRoomInfo(null, rname, row_num, column_num,useflag);
        if (!DAO.getInstance().insertMovieRoomInfo(movieRoomInfo)) {
            showMessageDialog(null, "添加影厅失败！", "提示", JOptionPane.ERROR_MESSAGE);
        }
        else {
            showMessageDialog(null,"影厅添加成功！", "提示",JOptionPane.INFORMATION_MESSAGE);
            //更新完毕后重新展示电影列表
            ManagerController.getInstance().showMovieRoomList();
            //更新完毕后刷新档期列表
            ManagerController.getInstance().initialScheduleView();
            ManagerController.getInstance().showScheduleList();
            AddMovieRoomView.getStage().close();
        }
    }

    @FXML
    private void onChooseCloseButton() {
        AddMovieRoomView.getStage().close();
    }
}
