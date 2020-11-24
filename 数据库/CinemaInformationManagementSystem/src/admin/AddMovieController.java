package admin;

import data.MovieInfo;
import javafx.event.ActionEvent;
import javafx.fxml.FXML;
import javafx.scene.control.ChoiceBox;
import javafx.scene.control.RadioButton;
import javafx.scene.control.TextField;
import javafx.scene.control.ToggleGroup;
import util.DAO;

import javax.swing.*;

import static javax.swing.JOptionPane.showMessageDialog;

public class AddMovieController {
    @FXML
    private TextField ADD_MOVIE_NAME;
    @FXML
    private ChoiceBox<Integer> HOUR;
    @FXML
    private ChoiceBox<Integer> MINUTE;
    @FXML
    private ChoiceBox<Integer> SECOND;
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
        HOUR.getItems().addAll(1,2,3);
        HOUR.getSelectionModel().select(0);
        for (int i = 0; i < 60; i++) {
            MINUTE.getItems().add(i);
            SECOND.getItems().add(i);
        }
        MINUTE.getSelectionModel().select(0);
        SECOND.getSelectionModel().select(0);
    }

    @FXML
    private void onChooseOKButton() {
        String mname = ADD_MOVIE_NAME.getText();
        if (mname.isEmpty()) {
            showMessageDialog(null, "未输入电影名！", "提示", JOptionPane.ERROR_MESSAGE);
            return;
        }
        String mtime = String.format("%d:%d:%d",HOUR.getSelectionModel().getSelectedItem(),MINUTE.getSelectionModel().getSelectedItem(),SECOND.getSelectionModel().getSelectedItem());
        boolean screen = YES_RADIOBUTTON.isSelected();

        MovieInfo movieInfo = new MovieInfo(null, mname, mtime,screen);
        if (!DAO.getInstance().insertMovieInfo(movieInfo)) {
            showMessageDialog(null, "添加电影失败！", "提示", JOptionPane.ERROR_MESSAGE);
        }
        else {
            showMessageDialog(null,"电影添加成功！", "提示",JOptionPane.INFORMATION_MESSAGE);
            //更新完毕后重新展示电影列表
            ManagerController.getInstance().showMovieList();
            //更新完毕后刷新档期列表
            ManagerController.getInstance().initialScheduleView();
            ManagerController.getInstance().showScheduleList();
            AddMovieView.getStage().close();
        }
    }

    @FXML
    private void onChooseCloseButton(ActionEvent actionEvent) {
        AddMovieView.getStage().close();
    }
}
