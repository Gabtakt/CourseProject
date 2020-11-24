package root;

import data.AccountInfo;
import javafx.event.ActionEvent;
import javafx.fxml.FXML;
import javafx.scene.control.ComboBox;
import javafx.scene.control.TextField;
import util.DAO;

import javax.swing.*;

import java.sql.ResultSet;
import java.sql.SQLException;

import static javax.swing.JOptionPane.showMessageDialog;

public class ChangeAccountController {
    @FXML
    private TextField CHANGE_ZH;
    @FXML
    private TextField CHANGE_MM;
    @FXML
    private TextField CHANGE_XM;
    @FXML
    private TextField CHANGE_DH;
    @FXML
    private ComboBox<String> CHANGE_ZHLX;

    private boolean isAck;

    @FXML
    private void initialize() {
        CHANGE_ZH.setEditable(true);
        CHANGE_MM.setEditable(false);
        CHANGE_XM.setEditable(false);
        CHANGE_DH.setEditable(false);
        CHANGE_ZHLX.getItems().addAll("超级管理员","管理员","售票员");
        CHANGE_ZHLX.getSelectionModel().select(0);
        isAck = false;
    }

    @FXML
    private void onChooseAckButton(ActionEvent actionEvent) {
        String account = CHANGE_ZH.getText();
        //未输入账号
        if (account.isEmpty()) {
            showMessageDialog(null, "账号不能为空！", "提示", JOptionPane.ERROR_MESSAGE);
            return;
        }
        //查询账户信息
        ResultSet re = DAO.getInstance().getAccountInfo(account);
        if (re == null) {
            showMessageDialog(null, "加载数据出错！", "提示", JOptionPane.ERROR_MESSAGE);
            return;
        }
        try {
            //未查到结果
            if (!re.next()) {
                showMessageDialog(null, "账号不存在！", "提示", JOptionPane.ERROR_MESSAGE);
            }
            //呈现账号信息
            else {
                CHANGE_MM.setText(re.getString("pwd"));
                CHANGE_XM.setText(re.getString("uname"));
                CHANGE_DH.setText(re.getString("phone"));
                CHANGE_ZHLX.getSelectionModel().select(re.getInt("idtype"));
                //选定后不允许修改账号
                CHANGE_ZH.setEditable(false);
                isAck = true;
            }
        } catch (SQLException e) {
            e.printStackTrace();
        }
    }

    @FXML
    private void onChooseChangeButton1(ActionEvent actionEvent) {
        CHANGE_MM.setEditable(true);
    }

    @FXML
    private void onChooseChangeButton2(ActionEvent actionEvent) {
        CHANGE_XM.setEditable(true);
    }

    @FXML
    private void onChooseChangeButton3(ActionEvent actionEvent) {
        CHANGE_DH.setEditable(true);
    }
    @FXML
    private void onOKButton(ActionEvent actionEvent) {
        if (!isAck) {
            showMessageDialog(null, "请先点击定键获取账号信息！", "提示", JOptionPane.ERROR_MESSAGE);
            return;
        }
        String MM = CHANGE_MM.getText();
        String XM = CHANGE_XM.getText();
        String DH = CHANGE_DH.getText();
        AccountInfo accountInfo = new AccountInfo(CHANGE_ZH.getText(),MM,XM,DH,CHANGE_ZHLX.getSelectionModel().getSelectedIndex(),null);
        if (!DAO.getInstance().updateAccountInfo(accountInfo)) {
            showMessageDialog(null, "修改账号信息出错！", "提示", JOptionPane.ERROR_MESSAGE);
        }
        else {
            showMessageDialog(null, "修改成功！", "提示", JOptionPane.INFORMATION_MESSAGE);
            isAck = false;
            RootController.getInstance().showList();
            ChangeAccountView.getStage().close();
        }
    }

    @FXML
    private void onCloseButton(ActionEvent actionEvent) {
        ChangeAccountView.getStage().close();
    }
}
