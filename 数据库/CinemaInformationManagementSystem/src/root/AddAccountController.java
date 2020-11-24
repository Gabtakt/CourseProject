package root;

import data.AccountInfo;
import javafx.fxml.FXML;
import javafx.scene.control.ComboBox;
import javafx.scene.control.TextField;
import util.DAO;
import util.Util;

import javax.swing.*;

import static javax.swing.JOptionPane.showMessageDialog;

public class AddAccountController {
    @FXML
    private TextField ADD_ZH;

    @FXML
    private TextField ADD_MM;

    @FXML
    private TextField ADD_XM;

    @FXML
    private TextField ADD_DH;

    @FXML
    private ComboBox<String> ADD_ZHLX;

    @FXML
    private void initialize() {
        ADD_ZHLX.getItems().addAll("超级管理员","管理员","售票员");
        ADD_ZHLX.getSelectionModel().select(0);
    }

    @FXML
    private void onOKButton() {
        String account = ADD_ZH.getText();
        String pwd = ADD_MM.getText();
        String uname = ADD_XM.getText();
        String phone = ADD_DH.getText();
        Integer idtype = ADD_ZHLX.getSelectionModel().getSelectedIndex();
        if (account.isEmpty()) {
            showMessageDialog(null,"账号不能为空！","提示",JOptionPane.ERROR_MESSAGE);
        }
        else if (pwd.isEmpty()) {
            showMessageDialog(null,"密码不能为空！","提示",JOptionPane.ERROR_MESSAGE);
        }
        else if (uname.isEmpty()) {
            showMessageDialog(null,"姓名不能为空！","提示",JOptionPane.ERROR_MESSAGE);
        }
        else if (!phone.isEmpty() && !Util.isNumeric(phone)) {
            showMessageDialog(null,"电话号码只能是数字！","提示",JOptionPane.ERROR_MESSAGE);
        }
        else if (!DAO.getInstance().insertAccountInfo(new AccountInfo(account, pwd, uname, phone, idtype, null))) {
            showMessageDialog(null, "添加账号失败！", "提示", JOptionPane.ERROR_MESSAGE);
        }
        else {
            showMessageDialog(null, "添加账号成功！", "提示", JOptionPane.INFORMATION_MESSAGE);
            //操作完毕后，重新显示账号列表
            RootController.getInstance().showList();
            AddAccountView.getStage().close();
        }
    }

    @FXML
    private void onCloseButton() {
        AddAccountView.getStage().close();
    }

}
